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

uint8 * pBuffer = &(VDAC_Buffer[0]);  //correct  

uint8_t DMA_Chan;
uint8_t DMA_TD[2]; 

uint8 aInitialized = 0; // initialized
uint8 aEnabled = 0;     // started (enabled)?

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
    //uint8_t DMA_Chan;
    //uint8_t DMA_TD[2];
    
    #define TRANSFER_COUNT1 (BUF_NumRefHigh)
    #define TRANSFER_COUNT2 (BUF_NumSamples - BUF_NumRefHigh)
    
    #define DMA_BYTES_PER_BURST     (1u)
    #define DMA_REQUEST_PER_BURST   (1u)
    //#define DMA_SRC_BASE (&Buffer[0]) - correct 
    //#define DMA_SRC_BASE (&Buffer[200])
    #define DMA_SRC_BASE_ (pBuffer) // todo
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

void Music_Init() 
{
    Music_DMAConfig();
    VDAC8_Start();
    
    pFile = FS_FOpen("test1.wav", "r");
    unsigned char wavInfoBuffer[80]; // holds the info in the wav header file. 
    int bytes_read;
    
    if (pFile == NULL) {
        return;
    }
    if (pFile != 0) {
        do {
            bytes_read = FS_FRead(wavInfoBuffer,1,80,pFile);
        } 
        while (bytes_read<44);
    }
   
    data_bytes = ((int)wavInfoBuffer[7]<<24) | ((int)wavInfoBuffer[6]<<16)| ((int)wavInfoBuffer[5]<<8) | (int)wavInfoBuffer[4]; // store the amount of data bytes in the file.
}

//==============================================================================
// Enable DMA transfer
//==============================================================================
void Music_Enable() 
{
    CyDmaChSetInitialTd(DMA_Chan, DMA_TD[0]);
        
    CyDmaChEnable(DMA_Chan, 1);// Enable DMA channel
}

void Music_Disable() {
    CyDmaChDisable(DMA_Chan);
}

void Music_Fill() {

//    if (bytes_played < data_bytes) {
//        int bytes_read;
//        
//        bytes_read = FS_Read(pFile,WriteBufferIndex,BUF_NumRefHigh);
//        
//        WriteBufferIndex += BUF_NumRefHigh;
//        if (WriteBufferIndex >= pBuffer + BUF_NumSamples) WriteBufferIndex = pBuffer;  // reset pointer
//        
//        bytes_played += bytes_read;
//    }
    
    FS_Read(pFile, WriteBufferIndex, BUF_NumRefHigh);
    WriteBufferIndex += BUF_NumRefHigh;
    if (WriteBufferIndex >= pBuffer + BUF_NumSamples) WriteBufferIndex = pBuffer;  // reset pointer
}

/* [] END OF FILE */
