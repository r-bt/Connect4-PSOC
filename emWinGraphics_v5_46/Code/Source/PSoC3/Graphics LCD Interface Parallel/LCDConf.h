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
File        : LCDConf.h
Purpose     : LCD configuration file for GraphicLCDIntf component.
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

#include <device.h>

/*********************************************************************
*       General configuration of LCD
*********************************************************************/
 
/* LCD Controller to use by emWin */
#define LCD_CONTROLLER      66702 

/* LCD orientation settings */ 
#define LCD_MIRROR_X            0
#define LCD_MIRROR_Y            0
#define LCD_SWAP_XY             1

/* Color depths - bits per pixel and bit order */
#define LCD_BITSPERPIXEL        16
#define LCD_SWAP_RB             1

/* 16 bit parallel interface is used */
#define LCD_USE_PARALLEL_16     1

/* Physical display size */
#define XSIZE_PHYS              240
#define YSIZE_PHYS              320

/* Set palette mode */
#define LCD_FIXEDPALETTE        565


/*********************************************************************
*       Configuration checking
*********************************************************************/

#if LCD_SWAP_XY
    #define LCD_XSIZE  YSIZE_PHYS
    #define LCD_YSIZE  XSIZE_PHYS
#else
    #define LCD_XSIZE XSIZE_PHYS
    #define LCD_YSIZE YSIZE_PHYS
#endif


/*********************************************************************
*
*                   Simple bus configuration
*
**********************************************************************
*/
  
#define LCD_WRITE_A0(Data)         CYGRAPHICS_WRITE(0, Data)    
#define LCD_WRITE_A1(Data)         CYGRAPHICS_WRITE(1, Data)
#define LCD_WRITEM_A0(p, NumItems) CYGRAPHICS_WRITEM(0, p, NumItems)
#define LCD_WRITEM_A1(p, NumItems) CYGRAPHICS_WRITEM(1, p, NumItems)    
#define LCD_READ_A0                CYGRAPHICS_READ(0)
#define LCD_READ_A1                CYGRAPHICS_READ(1)
#define LCD_READM_A1(p, NumItems)  CYGRAPHICS_READM(1, p, NumItems)

#endif /* LCDCONF_H */

/*************************** End of file ****************************/
