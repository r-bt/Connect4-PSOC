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
File        : GUI_Type.h
Purpose     : Include file define the types used for GUI
---------------------------END-OF-HEADER------------------------------

Attention : Do not modify this file ! If you do, you will not
            be able do update to a later GUI version !

*/

#ifndef  GUITYPE_H_INCLUDED
#define  GUITYPE_H_INCLUDED

#include "LCD.h"
#include "GUIConf.h"

/*********************************************************************
*
*       Common types
*/
typedef const char *  GUI_ConstString;

typedef LCD_COLOR       GUI_COLOR;
typedef LCD_LOGPALETTE  GUI_LOGPALETTE;
typedef LCD_DRAWMODE    GUI_DRAWMODE;
typedef LCD_RECT        GUI_RECT;

typedef struct {
  U16P XSize;
  U16P YSize;
  U16P BytesPerLine;
  U16P BitsPerPixel;
  const U8 GUI_UNI_PTR * pData;
  const GUI_LOGPALETTE GUI_UNI_PTR * pPal;
} GUI_BITMAP;


/* This structure may not be changed because the data that it
   expects is read in binary form (via any kind of interface,
   at runtime).
   This structure should therefor not be changed.
*/
typedef struct {
  U16 ID;           /* Version 1.00 => 100*/
  U16 Version;
  U16 XSize;
  U16 YSize;
  U16 BytesPerLine;
  U16 BitsPerPixel;
  U16 NumColors;
  U16 HasTrans;
} GUI_BITMAP_STREAM;

typedef struct {
  int x,y;
  U8  Pressed;
  U8  Layer;
} GUI_PID_STATE;

typedef struct {
  int xPos;
  int yPos;
  int xSize;
  int ySize;
  int Delay;
} GUI_GIF_IMAGE_INFO;

typedef struct {
  int xSize;
  int ySize;
  int NumImages;
} GUI_GIF_INFO;

/*********************************************************************
*
*       FONT structures
*/
typedef struct {
  U8 XSize;
  U8 XDist;
  U8 BytesPerLine;
  const unsigned char GUI_UNI_PTR * pData;
} GUI_CHARINFO;

typedef struct {
  U8 XSize;
  U8 YSize;
  I8 XPos;
  I8 YPos;
  U8 XDist;
  const unsigned char GUI_UNI_PTR * pData;
} GUI_CHARINFO_EXT;

typedef struct GUI_FONT_PROP {
  U16P First;                                              /* First character               */
  U16P Last;                                               /* Last character                */
  const GUI_CHARINFO         GUI_UNI_PTR * paCharInfo;     /* Address of first character    */
  const struct GUI_FONT_PROP GUI_UNI_PTR * pNext;          /* Pointer to next               */
} GUI_FONT_PROP;

/*********************************************************************
*
*       FONT structures
*
* This structure is used when retrieving information about a font.
* It is designed for future expansion without incompatibilities.
*/
typedef struct {
  U16 Flags;
  U8 Baseline;
  U8 LHeight;     /* height of a small lower case character (a,x) */
  U8 CHeight;     /* height of a small upper case character (A,X) */
} GUI_FONTINFO;

#define GUI_FONTINFO_FLAG_PROP (1<<0)    /* Is proportional */
#define GUI_FONTINFO_FLAG_MONO (1<<1)    /* Is monospaced */
#define GUI_FONTINFO_FLAG_AA   (1<<2)    /* Is an antialiased font */
#define GUI_FONTINFO_FLAG_AA2  (1<<3)    /* Is an antialiased font, 2bpp */
#define GUI_FONTINFO_FLAG_AA4  (1<<4)    /* Is an antialiased font, 4bpp */

/*********************************************************************
*
*       FONT methods
*/
typedef struct GUI_FONT GUI_FONT;

#define DECLARE_FONT(Type)                                     \
void GUI##Type##_DispChar    (U16P c);                         \
int  GUI##Type##_GetCharDistX(U16P c);                         \
void GUI##Type##_GetFontInfo (const GUI_FONT GUI_UNI_PTR * pFont, GUI_FONTINFO * pfi); \
char GUI##Type##_IsInFont    (const GUI_FONT GUI_UNI_PTR * pFont, U16 c); \
int  GUI##Type##_GetCharInfo (U16P c, GUI_CHARINFO_EXT * pInfo)

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/* PROP: Proportional fonts */
DECLARE_FONT(PROP);

#define GUI_FONTTYPE_PROP       \
  (void *)0,\
  (void *)0,\
  (void *)0,\
  (void *)0,\
  (void *)0,\
  (void *)0

#if defined(__cplusplus)
  }
#endif

struct GUI_FONT {
  void * pDummy_0;
  void * pDummy_1;
  void * pDummy_2;
  void * pDummy_3;
  void * pDummy_4;
  void * pDummy_5;
  U8 YSize;
  U8 YDist;
  U8 XMag;
  U8 YMag;
  union {
    const GUI_FONT_PROP GUI_UNI_PTR * pProp;
  } p;
  U8 Baseline;
  U8 LHeight;     /* Height of a small lower case character (a,x) */
  U8 CHeight;     /* Height of a small upper case character (A,X) */
};

/*********************************************************************
*
*       Memory management
*/
#ifndef     GUI_HMEM
  #if GUI_MAXBLOCKS < 32768
    #define     GUI_HMEM        I16P
  #else
    #define     GUI_HMEM        I32
  #endif
#endif
#define     GUI_HMEM_NULL     (0)
typedef     GUI_HMEM      GUI_HWIN;
typedef     GUI_HMEM      GUI_HSPRITE;


#endif  /* GUITYPE_H_INCLUDED */

/*************************** End of file ****************************/
