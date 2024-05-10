/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "Music.h"
#include <project.h>
#include <FS.h>
#include "Tick.h"

uint8 * pBuffer = &(VDAC_Buffer[0]); 

uint8_t DMA_Chan;
uint8_t DMA_TD[2]; 

uint8 isInitialized = 0; // initialized
uint8 isEnabled = 0;     // started (enabled)?

uint8 *WriteBufferIndex = &(VDAC_Buffer[0]);

FS_FILE *pFile;
uint32 data_bytes = 0;
uint32 bytes_played = 0;

//==============================================================================
// DMA Configuration
//==============================================================================

void Music_DMAConfig(void)
{
    
    // Variable declarations for DMA2
    
    #define TRANSFER_COUNT1 (BUF_NumRefHigh)
    #define TRANSFER_COUNT2 (BUF_NumSamples - BUF_NumRefHigh)
    
    #define DMA_BYTES_PER_BURST     (1u)
    #define DMA_REQUEST_PER_BURST   (1u)
    #define DMA_SRC_BASE_ (pBuffer)
    #define DMA_DST_BASE (CYDEV_PERIPH_BASE)
    
    DMA_Chan = VDAC_DMA_DmaInitialize(DMA_BYTES_PER_BURST, DMA_REQUEST_PER_BURST, HI16(DMA_SRC_BASE_), HI16(DMA_DST_BASE));
    DMA_TD[0] = CyDmaTdAllocate();
	DMA_TD[1] = CyDmaTdAllocate();
     
    CyDmaTdSetConfiguration(DMA_TD[0], TRANSFER_COUNT1, DMA_TD[1], TD_INC_SRC_ADR | VDAC_DMA__TD_TERMOUT_EN);
    CyDmaTdSetConfiguration(DMA_TD[1], TRANSFER_COUNT2, DMA_TD[0], TD_INC_SRC_ADR | VDAC_DMA__TD_TERMOUT_EN);
    
    // either ControlReg or VDAC8
    CyDmaTdSetAddress(DMA_TD[0], LO16((uint32)&VDAC_Buffer[0])              , LO16((uint32)VDAC8_Data_PTR));
	CyDmaTdSetAddress(DMA_TD[1], LO16((uint32)&VDAC_Buffer[TRANSFER_COUNT1]), LO16((uint32)VDAC8_Data_PTR));
}

//==============================================================================
// Initialize component
//==============================================================================

//==============================================================================
// 1/2 Buffer passed, data request issued
//==============================================================================
volatile CYBIT flag_DrqReady = 0; 
CY_ISR(myDrqInt)                
{   
    flag_DrqReady = 1;
}

int music_flag;
int music_tick_index;
#define MUSIC_TICK_COUNT 25 // 1/24Mhz * 12000 * 25 = 0.0125seconds

void Music_Init() 
{
    if (isInitialized) return;
    
    Music_DMAConfig();
    VDAC8_Start();
    
    music_tick_index = Tick_AddFlag(&music_flag, MUSIC_TICK_COUNT);
    
    isInitialized = 1;
    
    DmaDone_StartEx(myDrqInt);   // start isrDrq interrupt
}

//==============================================================================
// Enable DMA transfer
//==============================================================================
void Music_Enable() 
{
    if (isEnabled) return;
    
    CyDmaChSetInitialTd(DMA_Chan, DMA_TD[0]);    
    CyDmaChEnable(DMA_Chan, 1);// Enable DMA channel
    
    isEnabled = 1;
}

//==============================================================================
// Disable DMA transfer
//==============================================================================
void Music_Disable() {
    if (!isEnabled) return;
    
    isEnabled = 0;
    
    CyDmaChDisable(DMA_Chan);
}

//==============================================================================
// Sets sampling frequency
//==============================================================================
void Music_SetSampleFrequency(double freq) {
    Clock_Sampling_Freq = freq;
}

//==============================================================================
// Sets frequency of tone to be generated
//==============================================================================
uint8_t Music_SetFreq(double freq) {
    const double Tdiv = (double) (DDS_RESOLUTION / Clock_Sampling_Freq); // time period per bit increment	
        
    uint32 tmp = (uint32) (freq * Tdiv + 0.5);           // calculate tune word
    if ( (tmp < 1) || (tmp > TUNE_WORD_MAX) )  return 0; // fail -> exit if outside of the valid raange 
          
    //tune_word = tmp;
    dds_inc = tmp; // set tune word
    
    dds_acc = 0;
    
    return 1;
}

//==============================================================================
// Fill half of the DMA buffer with output data
//==============================================================================
void Music_FillHalfBuffer()
{     
    uint8  adr = 0;     // sine table address
    uint8  val = 0;     // sine value
    
    uint16 i;
    for (i=0; i<BUF_NumRefHigh; i++)
    {
        dds_acc += dds_inc;
        adr = (dds_acc >> 24);
        val = sine8[adr];
        //val = wave8[adr];
        * WriteBufferIndex++  = val; // populate buffer and advance position
        if (WriteBufferIndex >= pBuffer + BUF_NumSamples) WriteBufferIndex = pBuffer;  // reset pointer
    }       
}

//==============================================================================
// Plays a series of notes for a specified amount of time
//==============================================================================

#define MAX_TONES 4000

int stored_song[MAX_TONES];
uint8_t stored_length;

uint8_t timer_count;
uint8_t tone_count;

void Music_Play(int song[], int size) {
    if (size > MAX_TONES) return;
    
    for (int i = 0; i < size; i++) {
        stored_song[i] = song[i];
    }
    
    stored_length = size / 2;
    
    Music_SetFreq(stored_song[0]);
    timer_count = stored_song[1];
    tone_count = 0;
    
    Music_Enable();
}


//==============================================================================
// Plays a series of notes for a specified amount of time
//==============================================================================

void Music_Update() {
    
    if (flag_DrqReady){
        flag_DrqReady=0;
            
        Music_FillHalfBuffer();   // fill just completed half-buffer with data
    }
    
    if (tone_count >= stored_length) {
        return;
    }

    if (music_flag) {
        music_flag = 0;
        
        timer_count--;
        
        if (timer_count == 0) {
            tone_count++;
            
            if (tone_count == stored_length) {
                Music_Disable(); // No more notes to play
                return;
            }
            
            if (stored_song[tone_count*2] == 0) {
                Music_Disable();
                timer_count = stored_song[(tone_count*2)+1];
            } else {
                Music_SetFreq(stored_song[tone_count*2]);
                timer_count = stored_song[(tone_count*2)+1];
                
                Music_Enable();
            }
            
        }
    }
}

/* [] END OF FILE */
