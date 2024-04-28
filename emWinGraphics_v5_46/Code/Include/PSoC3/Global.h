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
File    : GLOBAL.h
Purpose : Global types etc.
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GLOBAL_H            // Guard against multiple inclusion
#define GLOBAL_H

#include <string.h>

/*********************************************************************
*
*       Macros
*
**********************************************************************
*/
#define COUNTOF(a)          (sizeof(a)/sizeof(a[0]))
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#define ZEROFILL(p, Size)   (memset(p, 0, Size))

#define U8    unsigned char
#define U16   unsigned short
#define U32   unsigned long
#define I8    signed char
#define I16   signed short
#define I32   signed long

#endif                      // Avoid multiple inclusion

/*************************** End of file ****************************/
