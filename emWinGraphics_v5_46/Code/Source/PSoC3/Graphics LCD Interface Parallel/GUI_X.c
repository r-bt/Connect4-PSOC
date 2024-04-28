/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2009  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

emWin 8051 V4.00 - Graphical user interface for embedded applications

emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be redistri-
buted in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUI_X.C
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "GUI_X.h"
#include "LCDConf.h"
#include <device.h>

/*********************************************************************
*
*       Global data
*/
volatile int OS_TimeMS;

/*********************************************************************
*
*      Timing:
*                 GUI_X_GetTime()
*                 GUI_X_Delay(int)

  Some timing dependent routines require a GetTime
  and delay function. Default time unit (tick), normally is
  1 ms.
*/

int GUI_X_GetTime(void) { 
  return OS_TimeMS; 
}

void GUI_X_Delay(int ms) { 
  int tEnd = OS_TimeMS + ms;
  while ((tEnd - OS_TimeMS) > 0);
}


/*********************************************************************
*
*       GUI_X_Init()
*
* Note:
*     GUI_X_Init() is called from GUI_Init is a possibility to init
*     some hardware which needs to be up and running before the GUI.
*/
void GUI_X_Init(void) {
    #if (GUI_SUPPORT_TOUCH == 1)
        /* Set the logical display orientation */
        GUI_TOUCH_SetOrientation((LCD_MIRROR_X << 0) | (LCD_MIRROR_Y << 1) | (LCD_SWAP_XY << 2));  
  	    /* Calibrate x */
  	    GUI_TOUCH_Calibrate(GUI_COORD_X, 0, XSIZE_PHYS-1, 0, 0);
   	    /* Calibrate y */
    	GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, YSIZE_PHYS-1, 0, 0);
        /* Start resistive touch component */  
        CYTOUCH_START();
    #endif /* GUI_SUPPORT_TOUCH */
}


/*********************************************************************
*
*       GUI_X_ExecIdle
*
* Note:
*  Called if WM is in idle state
*/
void GUI_X_ExecIdle(void) {}


/*********************************************************************
*
*      Logging: OS dependent

Note:
  Logging is used in higher debug levels only. The typical target
  build does not use logging and does therefore not require any of
  the logging routines below. For a release build without logging
  the routines below may be eliminated to save some space.
  (If the linker is not function aware and eliminates unreferenced
  functions automatically)

*/
void GUI_X_Log     (const char *s) { GUI_USE_PARA(s); }
void GUI_X_Warn    (const char *s) { GUI_USE_PARA(s); }
void GUI_X_ErrorOut(const char *s) { GUI_USE_PARA(s); }

/*************************** End of file ****************************/
