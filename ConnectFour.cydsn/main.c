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
//#include "tft.h"
//#include "GUI.h"
//#include "Connect4Board.h"
//#include "XPT2046.h"
//#include <stdlib.h>
//#include "defs.h"
//#include "Connect4.h"
//#include "Robot.h"
//#include "Tick.h"
//#include "FS.h"
//#include "stdio.h"

/* UBSFS device constants. */
#define USBFS_AUDIO_DEVICE  (0u)
#define AUDIO_INTERFACE     (1u)
#define OUT_EP_NUM          (2u)

/* Audio buffer constants. */
#define TRANSFER_SIZE   (32u)
#define NUM_OF_BUFFERS  (10u)
#define BUFFER_SIZE     (TRANSFER_SIZE * NUM_OF_BUFFERS)

/* Circular buffer for audio stream. */
uint8 soundBuffer[BUFFER_SIZE];
volatile uint16 outIndex = 0u;
volatile uint16 inIndex  = 0u;

/* Variables used to manage DMA. */
volatile uint8 syncDma = 0u;
volatile uint8 syncDmaCounter = 0u;

/* Variable declarations for VDACoutDMA. */
uint8 VdacOutDmaCh;
uint8 VdacOutDmaTd[NUM_OF_BUFFERS];

/* DMA Configuration for VDACoutDMA (Memory to VDAC) */
#define VDAC_DMA_BYTES_PER_BURST    (1u)
#define VDAC_DMA_REQUEST_PER_BURST  (1u)
#define VDAC_DMA_TD_TERMOUT_EN      (VDAC_DMA__TD_TERMOUT_EN)
#define VDAC_DMA_DST_BASE           (CYDEV_PERIPH_BASE)
#define VDAC_DMA_SRC_BASE           (CY_PSOC5LP) ? ((uint32) soundBuffer) : (CYDEV_SRAM_BASE)
#define VDAC_DMA_ENABLE_PRESERVE_TD (1u)

CY_ISR_PROTO(VdacDmaDone);

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*
*  The main function performs the following actions:
*   1. Initializes LCD and VDAC components.
*   2. Configures the DMA channel and transfers the descriptors.
*      The source is souundBuffer (SRAM) and the destination is the VDAC data register.
*   3. Starts the USBFS component and waits until the device is got enumerated
*      by the host.
*   4. When the PC starts streaming, the DMA starts copying data into the VDAC with
*      the 32-kHz frequency. None of the synchronization methods is implemented:
*      If the PC (source) transfers data faster than the device (sink), transfers it  ????
*      to VDAC the extra samples are dropped.
*      If the PC (source) transfers data slower than the device (sink), transfers it  ????
*      to VDAC the transfer is stopped and starts after the buffer is half-full.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
int main()
{
    uint8 i;
    uint8 skipNextOut = 0u;

    /* Start VDAC8 to generate output wave. */
    VDAC8_Start();

    /* Initialize DMA channel. */
    VdacOutDmaCh = VDAC_DMA_DmaInitialize(VDAC_DMA_BYTES_PER_BURST, VDAC_DMA_REQUEST_PER_BURST,
                                            HI16(VDAC_DMA_SRC_BASE), HI16(VDAC_DMA_DST_BASE));

    /* Allocate transfer descriptors for each buffer chunk. */
    for (i = 0u; i < NUM_OF_BUFFERS; ++i)
    {
        VdacOutDmaTd[i] = CyDmaTdAllocate();
    }

    /* Configure DMA transfer descriptors. */
    for (i = 0u; i < (NUM_OF_BUFFERS - 1u); ++i)
    {
        /* Chain current and next DMA transfer descriptors to be in row. */
        CyDmaTdSetConfiguration(VdacOutDmaTd[i], TRANSFER_SIZE, VdacOutDmaTd[i + 1u],
                                (TD_INC_SRC_ADR | VDAC_DMA_TD_TERMOUT_EN));
    }
    /* Chain last and 1st DMA transfer descriptors to make cyclic buffer. */
    CyDmaTdSetConfiguration(VdacOutDmaTd[NUM_OF_BUFFERS - 1u], TRANSFER_SIZE, VdacOutDmaTd[0u],
                                (TD_INC_SRC_ADR | VDAC_DMA_TD_TERMOUT_EN));


    for (i = 0u; i < NUM_OF_BUFFERS; i++)
    {
        /* Set source and destination addresses. */
        CyDmaTdSetAddress(VdacOutDmaTd[i], LO16((uint32) &soundBuffer[i * TRANSFER_SIZE]),
                                           LO16((uint32) VDAC8_Data_PTR));
    }

    /* Set 1st transfer descriptor to execute. */
    CyDmaChSetInitialTd(VdacOutDmaCh, VdacOutDmaTd[0u]);

    /* Start DMA completion interrupt. */
    DmaDone_StartEx(&VdacDmaDone);

    CyGlobalIntEnable;

    /* Start USBFS Operation with 5V operation. */
    USBFS_Start(USBFS_AUDIO_DEVICE, USBFS_5V_OPERATION);

    /* Wait for device enumeration. */
    while (0u == USBFS_GetConfiguration())
    {
    }

    for(;;)
    {
        /* Check if configuration or interface settings are changed. */
        if (0u != USBFS_IsConfigurationChanged())
        {
            /* Check active alternate setting. */
            if ((0u != USBFS_GetConfiguration()) &&
                (0u != USBFS_GetInterfaceSetting(AUDIO_INTERFACE)))
            {
                /* Alternate settings 1: Audio is streaming. */

                /* Reset variables. */
                inIndex  = 0u;
                outIndex = 0u;
                syncDma  = 0u;
                skipNextOut = 0u;
                syncDmaCounter = 0u;

                /* Enable OUT endpoint to receive audio stream. */
                USBFS_EnableOutEP(OUT_EP_NUM);

            }
            else
            {
                /* Alternate settings 0: Audio is not streaming (mute). */
            }
        }

        if (USBFS_OUT_BUFFER_FULL == USBFS_GetEPState(OUT_EP_NUM))
        {
            if (0u == skipNextOut)
            {
                /* Trigger DMA to copy data from OUT endpoint buffer. */
                USBFS_ReadOutEP(OUT_EP_NUM, &soundBuffer[inIndex * TRANSFER_SIZE],
                                            TRANSFER_SIZE);

                /* Wait until DMA completes copying data from OUT endpoint buffer. */
                while (USBFS_OUT_BUFFER_FULL == USBFS_GetEPState(OUT_EP_NUM))
                {
                }

                /* Move to the next buffer location and adjust to be within
                * buffer size. Lock from DmaDone interruption.
                */
                DmaDone_Disable();
                ++inIndex;
                inIndex = (inIndex >= NUM_OF_BUFFERS) ? 0u : inIndex;
                DmaDone_Enable();
                ++syncDmaCounter;

                /* Enable OUT endpoint to receive data from host. */
                USBFS_EnableOutEP(OUT_EP_NUM);
            }
            else
            {
                /* Ignore received data from host and arm OUT endpoint
                * without reading if overflow is detected.
                */
                USBFS_EnableOutEP(OUT_EP_NUM);
                skipNextOut = 0u;
            }

            /* When internal 32-kHz clock is slower, compare to PC traffic
            * then skip next transfer from PC.
            */
            if (outIndex == inIndex)
            {
                skipNextOut = 1u;
            }
        }

        /* Enable DMA transfers when sound buffer is half-full. */
        if ((0u == syncDma) && (syncDmaCounter == (NUM_OF_BUFFERS / 2u)))
        {
            /* Start DMA operation. */
            CyDmaChEnable(VdacOutDmaCh, VDAC_DMA_ENABLE_PRESERVE_TD);

            /* Disable underflow delayed start. */
            syncDma = 1u;
        }
    }
}


/*******************************************************************************
* Function Name: VdacDmaDone
********************************************************************************
*
* Summary:
*  The Interrupt Service Routine for a DMA transfer completion event. The DMA is
*  stopped when there is no data to send.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(VdacDmaDone)
{
    /* Move to next buffer location and adjust to be within buffer size. */
    ++outIndex;
    outIndex = (outIndex >= NUM_OF_BUFFERS) ? 0u : outIndex;

    /* When there is no data to transfer to VDAC stop DMA and wait until
	* buffer is half-full to continue operation.
    */
    if (outIndex == inIndex)
    {
        /* Stop DMA operation. */
        CyDmaChDisable(VdacOutDmaCh);

        /* Enable underflow delayed start. */
        syncDma = 0u;
        syncDmaCounter = 0u;
    }
}

//#include "Music.h"
//#include "dds.h"
//
//#define COLUMNS 7 
//#define ROWS 6
//
////==============================================================================
//// 1/2 Buffer passed, data request issued
////==============================================================================
//volatile CYBIT flag_VDAC_DMA_Ready = 0; 
//CY_ISR(VDAC_DMA_Done)                
//{   
//    flag_VDAC_DMA_Ready = 1;
//}
//
//int main(void)
//{
//    CyGlobalIntEnable;
//    
//    USBUART_Start(0, USBUART_5V_OPERATION); // Use USB Serial for debugging     
//    
//    FS_Init();
//    
//    CyDelay(1000);
//    
//    USBUART_PutString("Testing\r\n");
//    
//    Music_Init();
//    Music_Enable();
//    
//    DDS_Clock_Freq = 32.0E+3; // set actual DDS sampling clock frequency
//    
//    DDS_Start();
//    DDS_SetFrequency( 200 );   // set output frequency
//    
//    /* Start DMA completion interrupt. */
//    DmaDone_StartEx(&VDAC_DMA_Done);
//
//    for(;;)
//    {
//        
//        if (flag_VDAC_DMA_Ready)
//        {
//            flag_VDAC_DMA_Ready=0;
//            
//            Music_Fill();
//            
//            //DDS_FillHalfBuffer();
//        }
//  
//    }
//
//}


//void MainTask(void);
//
//int main()
//{
//    CyGlobalIntEnable;                      // Enable global interrupt
//    
//    // Initalize the components
//    SPIM_1_Start();                         // initialize SPIM component 
//    FS_Init();
//    VDAC_Start();
//    
//    MainTask();                             // all of the emWin exmples use MainTask() as the entry point
//    for(;;) {}                              // loop
//}
//
//void MainTask()
//{
//
//    USBUART_Start(0, USBUART_5V_OPERATION); // Use USB Serial for debugging     
//    
//    CyDelay(1000);
//    
//    USBUART_PutString("Testing\r\n");
//    
//    char sdVolName[10];     /* Buffer that will hold SD card Volume name */
//    U16 step = 1u;
//    FS_FILE * pFile;
//    
//    /* Get volume name of SD card #0 */
//    if(0 != FS_GetVolumeName(0u, &sdVolName[0], 9u))
//    {
//        /* Getting volume name succeeded so prompt it on the LCD */
//        USBUART_PutString("Volume name:");
//        CyDelay(100);
//        USBUART_PutString(sdVolName);
//        CyDelay(100);
//        USBUART_PutString("\r\n");
//    }
//    else
//    {
//        /* Operation Failed - indicate this */
//        USBUART_PutString("Failed to get volume name");
//    }
//    
//    int size = FS_GetVolumeSize(sdVolName);
//    char print[100];
//    sprintf(print, "Volume size is %d\r\n", size);
//    
//    USBUART_PutString(print);
// 
//    if(0 == FS_FormatSD(sdVolName))
//    {
//        USBUART_PutString("Succeded\r\n");
//    }
//    else
//    {
//        USBUART_PutString("Failed\r\n");
//    }
//    
//     /* This will create directory "Dir" on SD card */
//    if(0 == FS_MkDir("Dir"))
//    {
//        /* Display successful directory creation message */
//        USBUART_PutString("Created directory\r\n");
//    }
//    else
//    {
//        /* Display failure message */
//        USBUART_PutString("Failed to create dir\r\n");
//    }
//    
//    for(;;) {}
//    
//    Tick_Init();
//    
//    GUI_Init();                             // initilize graphics library
//    Connect4Board_Init(COLUMNS, ROWS); // Setup the Connect 4 Board
//     
//    uint16 PosX;
//    uint16 PoxY;
//    uint16 prevXPTState = 0;
//    uint16 prev_selected_column = COLUMNS;
//    
//    Connect4_Init(); // Start the connect 4 game
//    Robot_Init();
//    Speaker_WaveDAC_Start();
//        
////    for(;;) {
////       //Robot_Update();
////       Speaker_WaveDAC_Wakeup();
////       CyDelay(100);
////       Speaker_WaveDAC_Sleep();
////       CyDelay(100);
////       Speaker_WaveDAC_Wakeup();
////       CyDelay(100);
////       Speaker_WaveDAC_Sleep();
////       CyDelay(1000);
////    }
//  
//    // Playing on TFT screen code
//    for (;;) {
//        Robot_Update();
//        
//        if (Connect4_GetCurrentPlayer() == 0) {
//            // AI turn
//            struct Move bestMove = Connect4_NegaMax(5, -INF, INF);
//            Connect4_Move(bestMove.column);
//            
//            Connect4Board_Place(bestMove.column, 0);
//            Robot_ClearInterrupter();
//            Robot_Move(bestMove.column); 
//        } else if (Robot_GetState() == Robot_Idle) {
//            
//            if (Robot_GetInterrupter() != 7) {
//                uint8 column = Robot_GetInterrupter();
//                
//                Connect4_Move(column);
//                Connect4Board_Place(column, 1);
//                
//                Robot_ClearInterrupter();
//                
//                CyDelay(1000); // Pretend robot is thinking
//            }
//            
//            continue;
//            
//            if (prevXPTState != XPT2046_IRQ) { // Stop multiple events for one touch
//                prevXPTState = XPT2046_IRQ;
//                if (XPT2046_IRQ == 0) {
//                    if (XPT2046_ReadXY(&PosX, &PosY)) {
//                       
//                        uint16 selected_column = PosX / (YSIZE_PHYS / COLUMNS);
//                        if (selected_column > COLUMNS - 1) continue;
//                        
//                        if (prev_selected_column != selected_column) {
//                            Connect4Board_HighlightColumn(selected_column);
//                            prev_selected_column = selected_column;
//                            CyDelay(250);
//                        } else {
//                            Connect4Board_ClearHighlight();
//                            Connect4_Move(selected_column);
//                            Connect4Board_Place(selected_column, 1);
//                            
//                            CyDelay(1000); // let user think the board is thinking...
//                            prev_selected_column = COLUMNS;
//                        }
//                        
//    //                    char xnum[8];
//    //                    itoa(selected_column, xnum, 10);
//    //                    USBUART_PutString(xnum);
//    //                    CyDelay(10);
//    //                    USBUART_PutString("\r\n");
//                    }
//                }
//            }
//        }
//    }
//}
//
///* [] END OF FILE */
//