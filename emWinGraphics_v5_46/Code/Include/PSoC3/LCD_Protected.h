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
File        : LCD_Protected.h
Purpose     : LCD level - To be used only internally by the GUI
----------------------------------------------------------------------
*/

#ifndef LCD_PROTECTED_H
#define LCD_PROTECTED_H

#include "LCD.h"

/*********************************************************************
*
*       Data types
*/
typedef struct {
  int              NumEntries; 
  const LCD_COLOR* pPalEntries; 
} LCD_PHYSPALETTE; 

typedef struct {
  LCD_COLOR * paColor;
  I16         NumEntries;
} LCD_LUT_INFO;

/*********************************************************************
*
*       External data
*/
extern GUI_CONST_STORAGE U8 LCD_aMirror[256];
extern LCD_PIXELINDEX LCD__aConvTable[LCD_MAX_LOG_COLORS];

/*********************************************************************
*
*       Misc functions
*/
void                 LCD_UpdateColorIndices   (void);
int                  LCD_PassingBitmapsAllowed(void);
void                 LCD_EnableCursor         (int OnOff);
void                 LCD_SelectLCD            (void);

void LCD_DrawBitmap(int x0, int y0,
                    int xsize, int ysize,
                    int xMul, int yMul,
                    int BitsPerPixel,
                    int BytesPerLine,
                    const U8 GUI_UNI_PTR * pPixel,
                    const LCD_PIXELINDEX * pTrans);

/*********************************************************************
*
*       Internal used color conversion routines
*/
#define DECLARE_COLOR_CONVERSION(x) \
unsigned  LCD_Color2Index_##x (LCD_COLOR Color); \
LCD_COLOR LCD_Index2Color_##x (int Index);       \
unsigned  LCD_GetIndexMask_##x(void)

DECLARE_COLOR_CONVERSION(1);
DECLARE_COLOR_CONVERSION(M1);
DECLARE_COLOR_CONVERSION(2);
DECLARE_COLOR_CONVERSION(M2);
DECLARE_COLOR_CONVERSION(4);
DECLARE_COLOR_CONVERSION(M4);
DECLARE_COLOR_CONVERSION(5);
DECLARE_COLOR_CONVERSION(111);
DECLARE_COLOR_CONVERSION(222);
DECLARE_COLOR_CONVERSION(233);
DECLARE_COLOR_CONVERSION(323);
DECLARE_COLOR_CONVERSION(332);
DECLARE_COLOR_CONVERSION(444_12);
DECLARE_COLOR_CONVERSION(444_12_1);
DECLARE_COLOR_CONVERSION(444_16);
DECLARE_COLOR_CONVERSION(555);
DECLARE_COLOR_CONVERSION(565);
DECLARE_COLOR_CONVERSION(556);
DECLARE_COLOR_CONVERSION(655);
DECLARE_COLOR_CONVERSION(666);
DECLARE_COLOR_CONVERSION(822216);
DECLARE_COLOR_CONVERSION(84444);
DECLARE_COLOR_CONVERSION(8666);
DECLARE_COLOR_CONVERSION(8666_1);
DECLARE_COLOR_CONVERSION(888);
DECLARE_COLOR_CONVERSION(8888);
DECLARE_COLOR_CONVERSION(M111);
DECLARE_COLOR_CONVERSION(M222);
DECLARE_COLOR_CONVERSION(M233);
DECLARE_COLOR_CONVERSION(M323);
DECLARE_COLOR_CONVERSION(M332);
DECLARE_COLOR_CONVERSION(M444_12);
DECLARE_COLOR_CONVERSION(M444_16);
DECLARE_COLOR_CONVERSION(M555);
DECLARE_COLOR_CONVERSION(M565);
DECLARE_COLOR_CONVERSION(M556);
DECLARE_COLOR_CONVERSION(M655);
DECLARE_COLOR_CONVERSION(M666);
DECLARE_COLOR_CONVERSION(M8565);
DECLARE_COLOR_CONVERSION(M888);
DECLARE_COLOR_CONVERSION(M8888);
DECLARE_COLOR_CONVERSION(User);
DECLARE_COLOR_CONVERSION(User_0);
DECLARE_COLOR_CONVERSION(User_1);
DECLARE_COLOR_CONVERSION(User_2);
DECLARE_COLOR_CONVERSION(User_3);
DECLARE_COLOR_CONVERSION(User_4);
DECLARE_COLOR_CONVERSION(User_5);

unsigned  LCD_Color2Index_0 (LCD_COLOR Color, const LCD_PHYSPALETTE* pPhysPal);
LCD_COLOR LCD_Index2Color_0 (int Index, const LCD_PHYSPALETTE* pPhysPal);
unsigned  LCD_GetIndexMask_0(void);

/*********************************************************************
*
*       Declarations for LCD_L0_
*
*  Prefixes are as follows:
*  LCD_L0_xxx       ... Driver for first  LCD
*  LCD_L0_1_xxx     ... Driver for second LCD/layer
*  LCD_L0_2_xxx     ... Driver for third  LCD/layer
*/
#define DECLARE_L0_FUNCTIONS(x) \
unsigned int          LCD_L0##x##Color2Index        (LCD_COLOR Color);                       \
void                  LCD_L0##x##DrawHLine          (int x0, int y0,  int x1);               \
void                  LCD_L0##x##DrawVLine          (int x,  int y0,  int y1);               \
void                  LCD_L0##x##FillRect           (int x0, int y0, int x1, int y1);        \
unsigned int          LCD_L0##x##GetPixelIndex      (int x,  int y);                         \
void                  LCD_L0##x##GetRect            (LCD_RECT * pRect);                      \
void                  LCD_L0##x##SetPixelIndex      (int x,  int y, int ColorIndex);         \
void                  LCD_L0##x##XorPixel           (int x,  int y);                         \
int                   LCD_L0##x##Init               (void);                                  \
void                  LCD_L0##x##On                 (void);                                  \
void                  LCD_L0##x##Off                (void);                                  \
void                  LCD_L0##x##SetLUTEntry        (U8 Pos, LCD_COLOR color);               \
void *                LCD_L0##x##GetDevFunc         (int Index);                             \
I32                   LCD_L0##x##GetDevProp         (int Index) reentrant;                             \
LCD_COLOR             LCD_L0##x##Index2Color_PhysPal(int Index);                             \
unsigned              LCD_L0##x##Color2Index_PhysPal(LCD_COLOR Color);                       \
void                  LCD_L0##x##ReInit             (void);                                  \
void                  LCD_L0##x##Refresh            (void);                                  \
void                  LCD_L0##x##SetOrg             (int x, int y);                          \
void                  LCD_L0##x##DrawBitmap         (int x0, int y0, int xsize, int ysize,   \
                                                     int BitsPerPixel, int BytesPerLine,     \
                                                     const U8 GUI_UNI_PTR * pData, int Diff, \
                                                     const LCD_PIXELINDEX * pTrans)

DECLARE_L0_FUNCTIONS(_);
DECLARE_L0_FUNCTIONS(_1_);
DECLARE_L0_FUNCTIONS(_2_);
DECLARE_L0_FUNCTIONS(_3_);
DECLARE_L0_FUNCTIONS(_4_);
DECLARE_L0_FUNCTIONS(_5_);

/*********************************************************************
*
*       Declarations for magnification routines
*/
void         LCD_L0_MAG_DrawHLine      (int x0, int y0,  int x1);
void         LCD_L0_MAG_DrawVLine      (int x,  int y0,  int y1);
void         LCD_L0_MAG_FillRect       (int x0, int y0, int x1, int y1);
unsigned int LCD_L0_MAG_GetPixelIndex  (int x,  int y);
void         LCD_L0_MAG_SetPixelIndex  (int x,  int y, int ColorIndex);
void         LCD_L0_MAG_XorPixel       (int x,  int y);
int          LCD_L0_MAG_Init           (void);
void         LCD_L0_MAG_DrawBitmap     (int x0, int y0, int xsize, int ysize, 
                                        int BitsPerPixel, int BytesPerLine, 
                                        const U8 GUI_UNI_PTR * pData, int Diff, const LCD_PIXELINDEX * pTrans);

/*********************************************************************
*
*       Declarations for delta mode routines
*/
void         LCD_L0_DELTA_DrawHLine     (int x0, int y0,  int x1);
void         LCD_L0_DELTA_DrawVLine     (int x,  int y0,  int y1);
void         LCD_L0_DELTA_FillRect      (int x0, int y0, int x1, int y1);
unsigned int LCD_L0_DELTA_GetPixelIndex (int x,  int y);
void         LCD_L0_DELTA_SetPixelIndex (int x,  int y, int ColorIndex);
void         LCD_L0_DELTA_XorPixel      (int x,  int y);
int          LCD_L0_DELTA_Init          (void);
void         LCD_L0_DELTA_DrawBitmap    (int x0, int y0, int xsize, int ysize, 
                                        int BitsPerPixel, int BytesPerLine, 
                                        const U8 GUI_UNI_PTR * pData, int Diff, const LCD_PIXELINDEX * pTrans);

#endif /* LCD_PROTECTED_H */

/*************************** End of file ****************************/

