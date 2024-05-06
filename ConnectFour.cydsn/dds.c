/* ========================================
 *
 *
 * ========================================
*/

#include <dds.h>
#include <project.h>
#include <WaveGen.h>
#include <WaveTable.h>

uint8 *WriteBufferIndex = &(VDAC_Buffer[0]);

/*
// RAM only->
//http://www.daycounter.com/Calculators/Sine-Generator-Calculator2.phtml
const // (+2 ticks)  
uint8_t sine8[256] = {
128,131,134,137,140,143,146,149,    152,155,158,162,165,167,170,173,
176,179,182,185,188,190,193,196,    198,201,203,206,208,211,213,215,
218,220,222,224,226,228,230,232,    234,235,237,238,240,241,243,244,
245,246,248,249,250,250,251,252,    253,253,254,254,254,255,255,255,
255,255,255,255,254,254,254,253,    253,252,251,250,250,249,248,246,
245,244,243,241,240,238,237,235,    234,232,230,228,226,224,222,220,
218,215,213,211,208,206,203,201,    198,196,193,190,188,185,182,179,
176,173,170,167,165,162,158,155,    152,149,146,143,140,137,134,131,
    
128,124,121,118,115,112,109,106,    103,100, 97, 93, 90, 88, 85, 82,
 79, 76, 73, 70, 67, 65, 62, 59,     57, 54, 52, 49, 47, 44, 42, 40,
 37, 35, 33, 31, 29, 27, 25, 23,     21, 20, 18, 17, 15, 14, 12, 11,
 10,  9,  7,  6,  5,  5,  4,  3,      2,  2,  1,  1,  1,  0,  0,  0,
  0,  0,  0,  0,  1,  1,  1,  2,      2,  3,  4,  5,  5,  6,  7,  9,
 10, 11, 12, 14, 15, 17, 18, 20,     21, 23, 25, 27, 29, 31, 33, 35,
 37, 40, 42, 44, 47, 49, 52, 54,     57, 59, 62, 65, 67, 70, 73, 76,
 79, 82, 85, 88, 90, 93, 97,100,    103,106,109,112,115,118,121,124,
};
*/

//==============================================================================
// Initialize component
// Set input clock frequency and default values for output frequency and phase 
//==============================================================================

void DDS_Start()
{   
    // make record of the input clock frequency into period   
    //Tdiv = (double) (DDS_RESOLUTION / `$INSTANCE_NAME`_CLOCK_FREQ);	
    
    //Initialized = true;
    
    dds_acc = 0;

    DDS_SetFrequency( 1000 );
}

//==============================================================================
// Set output frequency
//==============================================================================

uint8 DDS_SetFrequency( double freq )
{     
    const double Tdiv = (double) (DDS_RESOLUTION / DDS_Clock_Freq); // time period per bit increment	

    uint8 result = 0; // success = 1, fail = 0 

 
        
    uint32 tmp = (uint32) (freq * Tdiv + 0.5);           // calculate tune word
    if ( (tmp < 1) || (tmp > TUNE_WORD_MAX) )  return 0; // fail -> exit if outside of the valid raange 
          
    //tune_word = tmp;
    dds_inc = tmp; // set tune word
        
       
    //SetFreq = freq; // backup value
    result = 1;     // success
        
    
    return result;
}


//==============================================================================
// Fill buffer with output data
//==============================================================================

void DDS_FillBuffer(uint16 start, uint16 length )
{     
    uint8  adr = 0;     // sine table address
    uint8  val = 0;     // sine value
    
    uint16 i;
    for (i=0; i<length; i++)
    {
        dds_acc += dds_inc;
        adr = (dds_acc >> 24);
        val = sine8[adr];
        //WaveGen_1_Buffer[start+i] = val;   
        VDAC_Buffer[start+i] = val;
    }    
        
}

//==============================================================================
// Fill buffer with output data
//==============================================================================

void DDS_FillHalfBuffer()
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

/* [] END OF FILE */
