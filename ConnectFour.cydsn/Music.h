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

#include <project.h>

#define BUF_NumSamples   1024            // buffer legth
#define BUF_NumRefHigh   512            // first 1/2 buffer length

uint8_t VDAC_Buffer[BUF_NumSamples];
uint8 * pBuffer;  // pointer to VDAC_Buffer

/***************************************
*              Registers        
***************************************/    

#define VDAC_Data_PTR    VDAC_1_Data_PTR


/***************************************
*        Function Prototypes
***************************************/

void  Music_Init();                 // start
void  Music_DMAConfig(void);           // 
void  Music_Enable();           // 
void  Music_Disable();
void  Music_Fill();

/* [] END OF FILE */
