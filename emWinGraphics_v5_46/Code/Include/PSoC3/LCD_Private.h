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
File        : LCD_Private.h
Purpose     : To be used only by the display drivers
----------------------------------------------------------------------
*/

#ifndef LCD_Private_H
#define LCD_Private_H

#include "LCD_ConfDefaults.h"            /* Configuration header file */
#include "LCD_Protected.h"
#include "GUI.h"

/*********************************************************************
*
*       Prototype of color arrays for LUT based layers
*/
#if LCD_PHYSCOLORS_IN_RAM
  #if (LCD_FIXEDPALETTE == 0)
    #if (LCD_FIXEDPALETTE == 0)
      extern LCD_COLOR LCD_PhysColors[1 << LCD_BITSPERPIXEL];
    #endif
  #endif
  #if (GUI_NUM_LAYERS > 1)
    #if (LCD_FIXEDPALETTE_1 == 0)
      extern LCD_COLOR LCD_PhysColors_1[1 << LCD_BITSPERPIXEL_1];
    #endif
  #endif
  #if (GUI_NUM_LAYERS > 2)
    #if (LCD_FIXEDPALETTE_2 == 0)
      extern LCD_COLOR LCD_PhysColors_2[1 << LCD_BITSPERPIXEL_2];
    #endif
  #endif
  #if (GUI_NUM_LAYERS > 3)
    #if (LCD_FIXEDPALETTE_3 == 0)
      extern LCD_COLOR LCD_PhysColors_3[1 << LCD_BITSPERPIXEL_3];
    #endif
  #endif
  #if (GUI_NUM_LAYERS > 4)
    #if (LCD_FIXEDPALETTE_4 == 0)
      extern LCD_COLOR LCD_PhysColors_4[1 << LCD_BITSPERPIXEL_4];
    #endif
  #endif
#endif

/*********************************************************************
*
*       API functions
*/
extern const struct tLCDDEV_APIList_struct * /* const */ LCD_aAPI[GUI_NUM_LAYERS];

/*********************************************************************
*
*       Support for Segment/COMLUTs
*/
#define LCD_TYPE_SEGTRANS U16
#define LCD_TYPE_COMTRANS U16

#ifdef LCD_LUT_COM
  extern LCD_TYPE_COMTRANS LCD__aLine2Com0[LCD_YSIZE];
#endif

#ifdef LCD_LUT_SEG
  extern LCD_TYPE_COMTRANS LCD__aCol2Seg0[LCD_XSIZE];
#endif

/*********************************************************************
*
*       Support for multiple display controllers
*/
#define DECLARE_PROTOTYPES(DISTX) \
  void     LCD_##DISTX##_SetPixelIndex(int x, int y, int PixelIndex); \
  unsigned LCD_##DISTX##_GetPixelIndex(int x, int y); \
  void     LCD_##DISTX##_XorPixel     (int x, int y); \
  void     LCD_##DISTX##_DrawHLine    (int x0, int y,  int x1); \
  void     LCD_##DISTX##_DrawVLine    (int x, int y0,  int y1); \
  void     LCD_##DISTX##_FillRect     (int x0, int y0, int x1, int y1); \
  void     LCD_##DISTX##_DrawBitmap   (int x0, int y0, int xsize, int ysize, int BitsPerPixel, int BytesPerLine,  const U8 GUI_UNI_PTR * pData, int Diff, const LCD_PIXELINDEX * pTrans); \
  void     LCD_##DISTX##_SetOrg       (int x, int y); \
  void     LCD_##DISTX##_On           (void); \
  void     LCD_##DISTX##_Off          (void); \
  int      LCD_##DISTX##_Init         (void); \
  void     LCD_##DISTX##_SetLUTEntry  (U8 Pos, LCD_COLOR Color); \
  void   * LCD_##DISTX##_GetDevFunc   (int Index); \
  void     LCD_##DISTX##_ReInit       (void)
    
DECLARE_PROTOTYPES(DIST0);
DECLARE_PROTOTYPES(DIST1);
DECLARE_PROTOTYPES(DIST2);
DECLARE_PROTOTYPES(DIST3);

#endif /* Avoid multiple inclusion */

/*************************** End of file ****************************/
