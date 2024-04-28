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
File        : GUI_Private.h
Purpose     : GUI internal declarations
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUI_PRIVATE_H
#define GUI_PRIVATE_H

#include "GUI.h"
#include "LCD_Protected.h"
#include "GUI_Debug.h"

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       Defaults for config switches
*
**********************************************************************

  The config switches below do not affect the interface in GUI.h and
  are therefor not required to be in GUI.h.
*/

/* Short address area.
   For  most compilers, this is "near" or "__near"
   We do not use this except for some CPUs which we know to always have some
   near memory, because the GUI_Context ans some other data will be declared
   to be in this short address (near) memory area as it has a major effect
   on performance.
   Please define in GUIConf.h (if you want to use it)
*/
#ifndef GUI_SADDR
  #define GUI_SADDR
#endif

#ifndef GUI_DEFAULT_FONT
  #define GUI_DEFAULT_FONT    &GUI_Font6x8
#endif

#ifndef GUI_DEFAULT_CURSOR
  #define GUI_DEFAULT_CURSOR  &GUI_CursorArrowM
#endif

#ifndef GUI_DEFAULT_BKCOLOR
  #define GUI_DEFAULT_BKCOLOR GUI_BLACK
#endif

#ifndef GUI_DEFAULT_COLOR
  #define GUI_DEFAULT_COLOR   GUI_WHITE
#endif

#ifndef GUI_X_SIGNAL_EVENT
  #define GUI_X_SIGNAL_EVENT()
#endif

#ifndef GUI_X_WAIT_EVENT
  #define GUI_X_WAIT_EVENT() GUI_X_ExecIdle()
#endif


/*********************************************************************
*
*       Angles
*
**********************************************************************
*/
#define GUI_45DEG  512
#define GUI_90DEG  (2*GUI_45DEG)
#define GUI_180DEG (4*GUI_45DEG)
#define GUI_360DEG (8*GUI_45DEG)


/*********************************************************************
*
*       Locking checks
*
**********************************************************************
*/
#if defined (WIN32) && defined (_DEBUG) && GUI_OS
  #define GUI_ASSERT_LOCK()    GUITASK_AssertLock()
  #define GUI_ASSERT_NO_LOCK() GUITASK_AssertNoLock()
  void GUITASK_AssertLock(void);
  void GUITASK_AssertNoLock(void);
#else
  #define GUI_ASSERT_LOCK()
  #define GUI_ASSERT_NO_LOCK()
#endif

/*********************************************************************
*
*       LCD_HL_ level defines
*
**********************************************************************
*/
#define LCD_HL_DrawHLine             LCD_DrawHLine
#define LCD_HL_DrawPixel             LCD_DrawPixel

/*********************************************************************
*
*       Helper functions
*
**********************************************************************
*/
#define GUI_ZEROINIT(Obj) GUI_MEMSET(Obj, 0, sizeof(Obj))
int  GUI_cos(int angle);
int  GUI_sin(int angle);
extern const U32 GUI_Pow10[10];

/* GUIAALib.c --- direct anti-aliased drawing */
int  GUI_AA_Init(int x0, int x1);
int  GUI_AA_Init_HiRes(int x0, int x1);
void GUI_AA_Exit(void);
I16 GUI_AA_HiRes2Pixel(int HiRes);

void GL_FillCircleAA_HiRes(int x0, int y0, int r);

void GUI_AA__DrawCharAA2NoTrans(int x0, int y0, int XSize, int YSize, int BytesPerLine, const U8*pData);
void GUI_AA__DrawCharAA2Trans  (int x0, int y0, int XSize, int YSize, int BytesPerLine, const U8*pData);
void GUI_AA__DrawCharAA2Xor    (int x0, int y0, int XSize, int YSize, int BytesPerLine, const U8*pData);
void GUI_AA__DrawCharAA4       (int x0, int y0, int XSize, int YSize, int BytesPerLine, const U8*pData);

/* Conversion routines */
void GUI_AddHex     (U32 v, U8 Len, char**ps);
void GUI_AddBin     (U32 v, U8 Len, char**ps);
void GUI_AddDecMin  (I32 v, char**ps);
void GUI_AddDec     (I32 v, U8 Len, char**ps);
void GUI_AddDecShift(I32 v, U8 Len, U8 Shift, char**ps);
long GUI_AddSign    (long v, char**ps);
int  GUI_Long2Len   (I32 v);

#define GUI_UC__GetCharSize(sText)  GUI_UC_GetCharSize(sText)
#define GUI_UC__GetCharCode(sText)  GUI_UC_GetCharCode(sText)

int   GUI_UC__CalcSizeOfChar   (U16 Char);
U16   GUI_UC__GetCharCodeInc   (const char GUI_UNI_PTR ** ps);
int   GUI_UC__NumChars2NumBytes(const char GUI_UNI_PTR * s, int NumChars);
int   GUI_UC__NumBytes2NumChars(const char GUI_UNI_PTR * s, int NumBytes);

int  GUI__GetLineNumChars  (const char GUI_UNI_PTR *s, int MaxNumChars);
int  GUI__GetNumChars      (const char GUI_UNI_PTR *s);
int  GUI__GetOverlap       (U16 Char);
int  GUI__GetLineDistX     (const char GUI_UNI_PTR *s, int Len);
int  GUI__GetFontSizeY     (void);
int  GUI__HandleEOLine     (const char GUI_UNI_PTR **ps);
void GUI__DispLine         (const char GUI_UNI_PTR *s, int Len, const GUI_RECT* pr);
void GUI__AddSpaceHex      (U32 v, U8 Len, char**ps);
void GUI__CalcTextRect     (const char GUI_UNI_PTR* pText, const GUI_RECT* pTextRectIn, GUI_RECT* pTextRectOut, int TextAlign);

int  GUI__WrapGetNumCharsDisp       (const char GUI_UNI_PTR * pText, int xSize, GUI_WRAPMODE WrapMode);
int  GUI__WrapGetNumCharsToNextLine (const char GUI_UNI_PTR * pText, int xSize, GUI_WRAPMODE WrapMode);
int  GUI__WrapGetNumBytesToNextLine (const char GUI_UNI_PTR * pText, int xSize, GUI_WRAPMODE WrapMode);
void GUI__memset    (U8 * p, U8 Fill, int NumBytes);
void GUI__memset16  (U16* p, U16 Fill, int NumWords);
int  GUI__strlen    (const char GUI_UNI_PTR * s);
int  GUI__strcmp    (const char GUI_UNI_PTR * s0, const char GUI_UNI_PTR * s1);
int  GUI__strcmp_hp (GUI_HMEM hs0, const char GUI_UNI_PTR * s1);

/* Get cursor position */
int  GUI__GetCursorPosX     (const char GUI_UNI_PTR * s, int Index, int MaxNumChars);
int  GUI__GetCursorPosChar  (const char GUI_UNI_PTR * s, int x, int NumCharsToNextLine);
U16  GUI__GetCursorCharacter(const char GUI_UNI_PTR * s, int Index, int MaxNumChars, int * pIsRTL);

/* Arabic support (tbd) */
U16  GUI__GetPresentationForm     (U16 Char, U16 Next, U16 Prev, int * pIgnoreNext, const char GUI_UNI_PTR * s);
int  GUI__IsArabicCharacter       (U16 c);

/* BiDi support */
int  GUI__BIDI_Log2Vis         (const char GUI_UNI_PTR * s, int NumChars, char * pBuffer, int BufferSize);
int  GUI__BIDI_GetCursorPosX   (const char GUI_UNI_PTR * s, int NumChars, int Index);
int  GUI__BIDI_GetCursorPosChar(const char GUI_UNI_PTR * s, int NumChars, int x);
U16  GUI__BIDI_GetLogChar      (const char GUI_UNI_PTR * s, int NumChars, int Index);
int  GUI__BIDI_GetCharDir      (const char GUI_UNI_PTR * s, int NumChars, int Index);
int  GUI__BIDI_IsNSM           (U16 Char);

/* Reading data routines */
U16 GUI__Read16(const U8 ** ppData);
U32 GUI__Read32(const U8 ** ppData);

/* Virtual screen support */
void GUI__GetOrg(int * px, int * py);

/* Timer support */
int            GUI_TIMER__IsActive (void);
GUI_TIMER_TIME GUI_TIMER__GetPeriod(void);

LCD_PIXELINDEX*  LCD_GetpPalConvTable        (const LCD_LOGPALETTE GUI_UNI_PTR *  pLogPal);
LCD_PIXELINDEX*  LCD_GetpPalConvTableUncached(const LCD_LOGPALETTE GUI_UNI_PTR *  pLogPal);


/*********************************************************************
*
*       2d - GL
*
**********************************************************************
*/
void GL_DispChar         (U16 c);
void GL_DrawArc          (int x0, int y0, int rx, int ry, int a0, int a1);
void GL_DrawBitmap       (const GUI_BITMAP GUI_UNI_PTR * pBM, int x0, int y0);
void GL_DrawCircle       (int x0, int y0, int r);
void GL_DrawEllipse      (int x0, int y0, int rx, int ry);
void GL_DrawHLine        (int y0, int x0, int x1);
void GL_DrawPolygon      (const GUI_POINT* pPoints, int NumPoints, int x0, int y0);
void GL_DrawPoint        (int x, int y);
void GL_DrawLine1        (int x0, int y0, int x1, int y1);
void GL_DrawLine1Ex      (int x0, int y0, int x1, int y1, unsigned * pPixelCnt);
void GL_DrawLineRel      (int dx, int dy);
void GL_DrawLineTo       (int x, int y);
void GL_DrawLineToEx     (int x, int y, unsigned * pPixelCnt);
void GL_DrawLine         (int x0, int y0, int x1, int y1);
void GL_DrawLineEx       (int x0, int y0, int x1, int y1, unsigned * pPixelCnt);
void GL_MoveTo           (int x, int y);
void GL_FillCircle       (int x0, int y0, int r);
void GL_FillCircleAA     (int x0, int y0, int r);
void GL_FillEllipse      (int x0, int y0, int rx, int ry);
void GL_FillPolygon      (const GUI_POINT* pPoints, int NumPoints, int x0, int y0);
void GL_SetDefault       (void);


/*********************************************************************
*
*       Callback pointers for dynamic linkage
*
**********************************************************************
Dynamic linkage pointers reduces configuration hassles.
*/
typedef int  GUI_tfTimer(void);
typedef char GUI_CURSOR_tfTempHide  (const GUI_RECT* pRect, int LayerIndex);
typedef void GUI_CURSOR_tfTempUnhide(int LayerIndex);
typedef int  WM_tfHandlePID(void);


/*********************************************************************
*
*       Cursors
*
**********************************************************************
*/
extern GUI_CONST_STORAGE unsigned char  GUI_Pixels_ArrowS[45];
extern GUI_CONST_STORAGE unsigned char  GUI_Pixels_ArrowM[60];
extern GUI_CONST_STORAGE unsigned char  GUI_Pixels_ArrowL[150];
extern GUI_CONST_STORAGE unsigned char  GUI_Pixels_CrossS[33];
extern GUI_CONST_STORAGE unsigned char  GUI_Pixels_CrossM[126];
extern GUI_CONST_STORAGE unsigned char  GUI_Pixels_CrossL[248];
extern GUI_CONST_STORAGE unsigned char  GUI_PixelsHeaderM[5 * 17];

extern GUI_CONST_STORAGE GUI_LOGPALETTE GUI_CursorPal;
extern GUI_CONST_STORAGE GUI_LOGPALETTE GUI_CursorPalI;


/*********************************************************************
*
*       Text rotation
*
**********************************************************************
*/
extern GUI_RECT  GUI_RectDispString; /* Used by LCD_Rotate...() and GUI_DispStringInRect() */

/*********************************************************************
*
*       Multitasking support
*
**********************************************************************
*/
extern int GUITASK__EntranceCnt;

/*********************************************************************
*
*       Bitmap related functions
*
**********************************************************************
*/

int       GUI_GetBitmapPixelIndex(const GUI_BITMAP GUI_UNI_PTR * pBMP, unsigned x, unsigned y);
GUI_COLOR GUI_GetBitmapPixelColor(const GUI_BITMAP GUI_UNI_PTR * pBMP, unsigned x, unsigned y);
int       GUI_GetBitmapPixelIndexEx(int BitsPerPixel, int BytesPerLine, const U8 GUI_UNI_PTR * pData, unsigned x, unsigned y);

void      GUI__DrawBitmap16bpp(int x0, int y0, int xsize, int ysize, const U8 GUI_UNI_PTR * pPixel, const LCD_LOGPALETTE GUI_UNI_PTR * pLogPal, int xMag, int yMag, tLCDDEV_Index2Color * pfIndex2Color);
void      GUI__SetPixelAlpha  (int x, int y, U8 Alpha, LCD_COLOR Color);
LCD_COLOR GUI__MixColors      (LCD_COLOR Color, LCD_COLOR BkColor, U8 Intens);

/*********************************************************************
*
*       LCDDEV_L0_xxx
*
**********************************************************************
*/
#define LCDDEV_L0_Color2Index         LCD_L0_Color2Index
#define LCDDEV_L0_DrawBitmap          LCD_L0_DrawBitmap
#define LCDDEV_L0_DrawHLine           LCD_L0_DrawHLine
#define LCDDEV_L0_DrawVLine           LCD_L0_DrawVLine
#define LCDDEV_L0_DrawPixel           LCD_L0_DrawPixel
#define LCDDEV_L0_FillRect            LCD_L0_FillRect
#define LCDDEV_L0_GetPixel            LCD_L0_GetPixel
#define LCDDEV_L0_GetRect             LCD_L0_GetRect
#define LCDDEV_L0_GetPixelIndex       LCD_L0_GetPixelIndex
#define LCDDEV_L0_Index2Color         LCD_L0_Index2Color
#define LCDDEV_L0_SetPixelIndex       LCD_L0_SetPixelIndex
#define LCDDEV_L0_XorPixel            LCD_L0_XorPixel
#define LCDDEV_L0_GetDevFunc          LCD_L0_GetDevFunc

extern LCD_PIXELINDEX * LCD_pBkColorIndex;
extern LCD_PIXELINDEX * LCD_pColorIndex;
extern LCD_PIXELINDEX * LCD_pAColorIndex;

#define LCD_BKCOLORINDEX (*LCD_pBkColorIndex)
#define LCD_COLORINDEX   (*LCD_pColorIndex)
#define LCD_ACOLORINDEX  LCD_pAColorIndex

/*********************************************************************
*
*       EXTERNs for GL_CORE
*
**********************************************************************
*/
#ifdef  GL_CORE_C
  #define GUI_EXTERN
#else
  #define GUI_EXTERN extern
#endif

GUI_EXTERN GUI_SADDR GUI_CONTEXT        GUI_Context;        /* Thread wide globals */
GUI_EXTERN GUI_SADDR char               GUI_DecChar;

GUI_EXTERN I16 GUI_OrgX, GUI_OrgY;

#undef GUI_EXTERN


#if defined(__cplusplus)
}
#endif 

#endif /* GUI_PRIVATE_H */

/*************************** End of file ****************************/
