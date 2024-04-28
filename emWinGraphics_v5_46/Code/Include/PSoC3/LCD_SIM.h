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
File        : LCD_SIM.h
Purpose     : Declares LCD interface functions
----------------------------------------------------------------------
*/

#ifndef LCDSIM_H
#define LCDSIM_H


/************************************************************
*
*       defines
*
*************************************************************
*/
#define LCDSIM_MAX_DISPLAYS 6

#define LCDSIM_SUB_PIXEL_ORDER_RGB 0
#define LCDSIM_SUB_PIXEL_ORDER_RBG 1
#define LCDSIM_SUB_PIXEL_ORDER_GBR 2
#define LCDSIM_SUB_PIXEL_ORDER_GRB 3
#define LCDSIM_SUB_PIXEL_ORDER_BGR 4
#define LCDSIM_SUB_PIXEL_ORDER_BRG 5

/************************************************************
*
*       LCDSIM_      General declarations
*
*************************************************************
*/

char* LCDSIM_Init(void);
void  LCDSIM_Exit(void);
int   LCDSIM_GetMouseState(LCD_tMouseState *pState);
void  LCDSIM_SetMouseState(int x, int y, int KeyStat, int LayerIndex);
void  LCDSIM_CheckMouseState(int LayerIndex);
int   LCDSIM_SaveBMP   (const char * sFileName);
int   LCDSIM_SaveBMPEx (const char * sFileName, int x0, int y0, int xSize, int ySize);
int   LCDSIM_SaveSBMP  (const char * sFileName);
int   LCDSIM_SaveSBMPEx(const char * sFileName, int x0, int y0, int xSize, int ySize);
void  LCDSIM_SetRGBOrder(unsigned RGBOrder);

/************************************************************
*
*       LCDSIM_     Functions for each display
*
*************************************************************
*/

void  LCDSIM_FillRect(int x0, int y0, int x1, int y1, int Index, int LayerIndex);
int   LCDSIM_GetModifyCnt(int LayerIndex);
int   LCDSIM_GetModifyCntInfo(int LayerIndex);
int   LCDSIM_GetPixelColor(int x, int y, int LayerIndex);
int   LCDSIM_GetPixelIndex(int x, int y, int LayerIndex);
int   LCDSIM_Index2Color(int Index, int LayerIndex);
int   LCDSIM_RLUT_GetPixelIndex(int x, int y, int LayerIndex);
void  LCDSIM_RLUT_SetPixelIndex(int x, int y, int Index, int LayerIndex);
void  LCDSIM_SetLUTEntry(U8 Pos, LCD_COLOR color, int LayerIndex);
void  LCDSIM_SetPixelIndex(int x, int y, int Index, int LayerIndex);
void  LCDSIM_SetPixelColor(int x, int y, LCD_COLOR PixelColor, int LayerIndex);
void  LCDSIM_SetSubPixel(int x, int y, U8 Value, int LayerIndex);
void  LCDSIM_SetSubPixelPhys(int xPhys, int yPhys, int Index, int LayerIndex);
void  LCDSIM_SetPixelPhys(int x, int y, int Index, int LayerIndex);
int   LCDSIM_GetPixelPhys(int xPhys, int yPhys, int LayerIndex);
void  LCDSIM_FillRectPhys(int x0Phys, int y0Phys, int x1Phys, int y1Phys, int Index, int LayerIndex);
void  LCDSIM_SetOrg(int x, int y, int LayerIndex);
void  LCDSIM_SetAlpha(int Alpha, int LayerIndex);

/************************************************************
*
*  LCDSIM_      Declarations for painting in windows program
*
*************************************************************
*/

#if defined(_WINDOWS_) | defined(_WINDOWS_H)  /* if windows.h has already been included */
  void LCDSIM_Paint  (HWND hWnd);
#endif


#endif /* LCD_H */




