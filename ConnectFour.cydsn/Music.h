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
#ifndef Music_H
#define Music_H

#include <project.h>

#define BUF_NumSamples   256            // buffer legth
#define BUF_NumRefHigh   128            // first 1/2 buffer length

uint8_t VDAC_Buffer[BUF_NumSamples];
uint8 * pBuffer;  // pointer to VDAC_Buffer

#define VDAC_Data_PTR    VDAC_1_Data_PTR

static const uint8_t sine8[256] = {
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


#define DDS_RESOLUTION (double) 4294967296.0 // 4294967296 = 2^32
#define TUNE_WORD_MAX  (uint32) 2147483647   // 2147483647 = 2^32 - 1 = DDS_RESOLUTION/2 - 1

uint32 dds_acc; // DDS accumulator
uint32 dds_inc; // DDS tune word inctrement 

double Clock_Sampling_Freq;      // sampling clock frequency

void  Music_Init();            
void  Music_DMAConfig(void);          
void  Music_Enable();          
void  Music_Disable();
void Music_SetSampleFrequency(double freq);
uint8_t Music_SetFreq(double freq);
void Music_FillHalfBuffer();
void Music_Update();
void Music_Play(int song[], int size);

#endif

/* [] END OF FILE */
