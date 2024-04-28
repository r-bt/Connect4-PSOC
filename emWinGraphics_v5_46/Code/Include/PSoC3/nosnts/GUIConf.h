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
File        : GUIConf.h
Purpose     : Configures emWins abilities, fonts etc.
----------------------------------------------------------------------
*/


#ifndef GUICONF_H
#define GUICONF_H

/* Keil 8051 specific define to put constant into FLASH */
#define GUI_CONST_STORAGE		 code const

#define GUI_OS                    0  /* Compile without multitasking support */
#define GUI_SUPPORT_TOUCH         0  /* Support a touch screen */

#define GUI_DEFAULT_FONT          &GUI_Font6x8


/*********************************************************************
*
*         Configuration of available packages
*/
#define GUI_ALLOC_SIZE                0    /* Enable runtime memory configuration */
#define GUI_COMPILER_SUPPORTS_FP      0    /* Disable the use of complex function pointers */
#define GUI_WINSUPPORT                0    /* Window manager not available */
#define GUI_SUPPORT_ROTATION          0    /* Disable support for text rotation */
#define GUI_SUPPORT_MEMDEV            0    /* Memory device package not available */
#define GUI_SUPPORT_AA                0    /* Antialiasing package not available */
#define GUI_SUPPORT_CURSOR            0    /* Cursors not available */ 
#endif  /* Avoid multiple inclusion */
