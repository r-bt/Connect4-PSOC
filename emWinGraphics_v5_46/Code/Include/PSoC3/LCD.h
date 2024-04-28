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
File        : LCD.h
Purpose     : Declares LCD interface functions
----------------------------------------------------------------------
*/

#ifndef LCD_H
#define LCD_H

#include "GUI_ConfDefaults.h" /* Used for GUI_UNI_PTR */
#include "Global.h"

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       Basic type defines
*
* The follwing are defines for types used in the LCD-driver and the
* GUI layers on top of that. Since "C" does not provide data types of
* fixed length which are identical on all platforms, this is done here.
* For most 16/32 controllers, the settings will work fine. However, if
* you have similar defines in other sections of your program, you might
* want to change or relocate these defines, e.g. in a TYPE.h file.
*/
#define I16P I16              /*   signed 16 bits OR MORE ! */
#define U16P U16              /* unsigned 16 bits OR MORE ! */

/*********************************************************************
*
*       Settings for windows simulation
*
* Some settings in the configuration may conflict with the values required
* in the Simulation. This is why we ignore the target settings for data
* types and use the correct settings for the simulation.
* (U32 could be defined as long, which would yield a 64 bit type on
* the PC)
*/
#ifdef WIN32
  #pragma warning( disable : 4244 )  // Disable warning messages in simulation
  #pragma warning( disable : 4761 )  // Disable warning "integral size mismatch in argument; conversion supplied"
#endif                                      

/*********************************************************************
*
*       Constants
*/
#define LCD_ERR0 (0x10)
#define LCD_ERR_CONTROLLER_NOT_FOUND (LCD_ERR0+1)
#define LCD_ERR_MEMORY               (LCD_ERR0+2)

/*********************************************************************
*
*       Drawing modes
*/
#define LCD_DRAWMODE_NORMAL (0)
#define LCD_DRAWMODE_XOR    (1<<0)
#define LCD_DRAWMODE_TRANS  (1<<1)
#define LCD_DRAWMODE_REV    (1<<2)

/*********************************************************************
*
*       Typedefs
*/
typedef int LCD_DRAWMODE;
typedef U32 LCD_COLOR;
 
/*********************************************************************
*
*       Data structures
*/
typedef struct { I16P x,y; } GUI_POINT;
typedef struct { I16 x0,y0,x1,y1; } LCD_RECT;

typedef struct {
  int              NumEntries; 
  char             HasTrans;         
  const LCD_COLOR GUI_UNI_PTR * pPalEntries; 
} LCD_LOGPALETTE; 

/* This is used for the simulation only ! */
typedef struct {
  int x,y;
  unsigned char KeyStat;
} LCD_tMouseState;

/*********************************************************************
*
*       LCD_L0_... color conversion
*/
typedef LCD_COLOR      tLCDDEV_Index2Color  (int Index);
typedef unsigned int   tLCDDEV_Color2Index  (LCD_COLOR Color);
typedef unsigned int   tLCDDEV_GetIndexMask (void);

#define DECLARE_L0_COLOR_CONVERSION(x) \
unsigned  LCD_L0##x##Color2Index (LCD_COLOR Color); \
LCD_COLOR LCD_L0##x##Index2Color (int Index);       \
unsigned  LCD_L0##x##GetIndexMask(void)

DECLARE_L0_COLOR_CONVERSION(_);
DECLARE_L0_COLOR_CONVERSION(_1_);
DECLARE_L0_COLOR_CONVERSION(_2_);
DECLARE_L0_COLOR_CONVERSION(_3_);
DECLARE_L0_COLOR_CONVERSION(_4_);
DECLARE_L0_COLOR_CONVERSION(_5_);

typedef void tLCDDEV_DrawBitmap   (int x0, int y0, int xsize, int ysize,
                       int BitsPerPixel, int BytesPerLine,
                       const U8 GUI_UNI_PTR * pData, int Diff,
                       const void* pTrans);   /* Really LCD_PIXELINDEX, but is void to avoid compiler warnings*/

/*********************************************************************
*
*       Defines for device capabilities
*
* The following is the list of device capabilities which can, but do
* not have to be implemented in the driver. This way the driver can be
* enhanced in the future without affecting the driver interface,
* keeping older drivers compatible.
* More DevCaps can always be added in the future, as older drivers
* are guaranteed to return 0 for all unimplemented features or queries.
*
* The values below define the legal parameters to the LCD_GetDeviceCaps
* and the LCD_GetpCapFunc routines.
*/

#define LCD_DEVCAP_NUMCOLORS         0x0     /* Quest number of colors
                                                which LCD can display */
#define LCD_DEVCAP_XSIZE             0x01    /* Quest horiz. res. of display */
#define LCD_DEVCAP_YSIZE             0x02    /* Quest vert. res. of display */
#define LCD_DEVCAP_VXSIZE            0x03    /* Quest vert. res. of virtual disp.*/
#define LCD_DEVCAP_VYSIZE            0x04    /* Quest vert. res. of virtual disp.*/
#define LCD_DEVCAP_XORG              0x05    /* X-origin ... usually 0 */
#define LCD_DEVCAP_YORG              0x06    /* Y-origin ... usually 0 */
#define LCD_DEVCAP_CONTROLLER        0x07    /* LCD Controller (Numerical) */
#define LCD_DEVCAP_BITSPERPIXEL      0x08    /* Bits per pixel ... 1/2/4/8 */
#define LCD_DEVCAP_NUM_COLORS        0x09    /* Quest number of colors */
#define LCD_DEVCAP_XMAG              0x0A
#define LCD_DEVCAP_YMAG              0x0B
#define LCD_DEVCAP_FIXEDPALETTE      0x0C
#define LCD_DEVCAP_MIRROR_X          0x0D
#define LCD_DEVCAP_MIRROR_Y          0x0E
#define LCD_DEVCAP_SWAP_XY           0x0F
#define LCD_DEVCAP_SWAP_RB           0x10
#define LCD_DEVCAP_PHYSCOLORS_IN_RAM 0x11
#define LCD_DEVCAP_REVERSE_LUT       0x12

#define LCD_DEVCAP_COLOR        0x1000  /* Quest Color[0]
                                0x1001     Quest Color[1]
                                0x1002     Quest Color[2]
                                         ...                    */
 /* The next 4095 entries are reserved so up to 4096 colors
    can be queried          ...*/

int LCD_GetXSizeMax(void);
int LCD_GetYSizeMax(void);
int LCD_GetVXSizeMax(void);
int LCD_GetVYSizeMax(void);
int LCD_GetBitsPerPixelMax(void);

int LCD_GetXSize       (void);
int LCD_GetYSize       (void);
int LCD_GetVXSize      (void);
int LCD_GetVYSize      (void);
U32 LCD_GetNumColors   (void);
int LCD_GetBitsPerPixel(void);
int LCD_GetFixedPalette(void);
int LCD_GetXMag        (void);
int LCD_GetYMag        (void);

int LCD_GetXSizeEx          (int LayerIndex);
int LCD_GetYSizeEx          (int LayerIndex);
int LCD_GetVXSizeEx         (int LayerIndex);
int LCD_GetVYSizeEx         (int LayerIndex);
U32 LCD_GetNumColorsEx      (int LayerIndex);
int LCD_GetBitsPerPixelEx   (int LayerIndex);
I32 LCD_GetFixedPaletteEx   (int LayerIndex);
int LCD_GetXMagEx           (int LayerIndex);
int LCD_GetYMagEx           (int LayerIndex);
int LCD_GetMirrorXEx        (int LayerIndex);
int LCD_GetMirrorYEx        (int LayerIndex);
int LCD_GetSwapXYEx         (int LayerIndex);
int LCD_GetSwapRBEx         (int LayerIndex);
int LCD_GetDeltaModeEx      (int LayerIndex);
int LCD_GetBitsPerPixel_L0Ex(int LayerIndex);
int LCD_GetReversLUTEx      (int LayerIndex);
int LCD_GetPhysColorsInRAMEx(int LayerIndex);

int LCD_GetNumLayers(void);

#define LCD_GetNumDisplays() LCD_GetNumLayers()

#define LCD_GET_XSIZE()        LCD_GetXSize()
#define LCD_GET_YSIZE()        LCD_GetYSize()
#define LCD_GET_VXSIZE()       LCD_GetVXSize()
#define LCD_GET_VYSIZE()       LCD_GetVYSize()
#define LCD_GET_NUMCOLORS()    LCD_GetNumColors()
#define LCD_GET_BITSPERPIXEL() LCD_GetBitsPerPixel()

#define LCD_DEVFUNC_READRECT      0x01 /* Request of a function pointer for reading a rectangular display area */
#define LCD_DEVFUNC_SETALPHA      0x02 /* Request of a function pointer for setting the alpha blending factor */
#define LCD_DEVFUNC_SETPOS        0x03 /* Request of a function pointer for setting the layer position */
#define LCD_DEVFUNC_SETSIZE       0x04 /* Request of a function pointer for setting the layer size */
#define LCD_DEVFUNC_SETVIS        0x05 /* Request of a function pointer for setting the visibility of a layer */
#define LCD_DEVFUNC_ISHW          0x06 /* Request if the current selected device is a display driver */
#define LCD_DEVFUNC_24BPP         0x07 /* Request if the driver is able to draw a 24bpp bitmap */
#define LCD_DEVFUNC_NEXT_PIXEL    0x08 /* Request if the driver is able to draw a bitmap pixel by pixel */
#define LCD_DEVFUNC_SET_VRAM_ADDR 0x09 /* Request of a function pointer for setting the VRAM address */
#define LCD_DEVFUNC_SET_VSIZE     0x0A /* Request of a function pointer for setting the VRAM size */
#define LCD_DEVFUNC_SET_SIZE      0x0B /* Request of a function pointer for setting the display size */

/*********************************************************************
*
*       Set display properties
*/
int LCD_SetAlphaEx   (int Alpha, int LayerIndex);
int LCD_SetVRAMAddrEx(U32 Addr, int LayerIndex);
int LCD_SetVSizeEx   (int xSize, int ySize, int LayerIndex);
int LCD_SetSizeEx    (int xSize, int ySize, int LayerIndex);

/*********************************************************************
*
*       Declarations for LCD_
*/
void LCD_DrawHLine(int x0, int y0,  int x1);
void LCD_DrawPixel(int x0, int y0);
void LCD_DrawVLine  (int x, int y0,  int y1);

void LCD_SetClipRectEx(const LCD_RECT* pRect);
void LCD_SetClipRectMax(void);

/* Get device capabilities (0 if not supported) */
I32  LCD_GetDevCap(int Index);

/* Initialize LCD using config-parameters */
int LCD_Init(void);

void LCD_SetBkColor   (LCD_COLOR Color); /* Set background color */
void LCD_SetColor     (LCD_COLOR Color); /* Set foreground color */
void LCD_SetPixelIndex(int x, int y, int ColorIndex);

/* Palette routines (Not available on all drivers) */
void LCD_InitLUT(void);
void LCD_SetLUTEntryEx(U8 Pos, LCD_COLOR Color, unsigned int LayerIndex);


LCD_DRAWMODE LCD_SetDrawMode  (LCD_DRAWMODE dm);
void LCD_SetColorIndex(unsigned PixelIndex);
void LCD_SetBkColorIndex(unsigned PixelIndex);
void LCD_FillRect(int x0, int y0, int x1, int y1);

LCD_COLOR    LCD_GetPixelColor(int x, int y);     /* Get RGB color of pixel */
unsigned int LCD_GetPixelIndex(int x, int y);
int          LCD_GetBkColorIndex (void);
int          LCD_GetColorIndex (void);

/*********************************************************************
*
*       LCD  publics not used by GUI
*/
#define LCD_On          LCD_L0_On
#define LCD_Off         LCD_L0_Off
#define LCD_ReInit      LCD_L0_ReInit
#define LCD_SetLUTEntry LCD_L0_SetLUTEntry

/*********************************************************************
*
*       Physical color access, internally used only
*/
void LCD__SetPhysColor(U8 Pos, LCD_COLOR Color);

#define LCD_CC_UNLOCK (0)    /* Default mode: Cache is transparent */
#define LCD_CC_LOCK   (1)    /* Cache is locked, no write operations */
#define LCD_CC_FLUSH  (2)    /* Flush cache, do not change mode */

#define DECLARE_LCD_L0_CONTROLCACHE(x) U8 LCD_L0##x##ControlCache(U8 mode);
DECLARE_LCD_L0_CONTROLCACHE(_)
DECLARE_LCD_L0_CONTROLCACHE(_1_)
DECLARE_LCD_L0_CONTROLCACHE(_2_)
DECLARE_LCD_L0_CONTROLCACHE(_3_)
DECLARE_LCD_L0_CONTROLCACHE(_4_)
DECLARE_LCD_L0_CONTROLCACHE(_5_)

#define DECLARE_LCD_L0_REFRESH(x) void LCD_L0##x##Refresh(void);
DECLARE_LCD_L0_REFRESH(_)
DECLARE_LCD_L0_REFRESH(_1_)
DECLARE_LCD_L0_REFRESH(_2_)
DECLARE_LCD_L0_REFRESH(_3_)
DECLARE_LCD_L0_REFRESH(_4_)
DECLARE_LCD_L0_REFRESH(_5_)

#define LCD_ControlCache LCD_L0_ControlCache

/*********************************************************************
*
*       Support for paging (obsolete)
*/
int LCD_SelPage  (int NewPage);    /* returns formerly sel. page */
int LCD_ShowPage (int NewPage);    /* sets / returns visible page */
int LCD_GetSelPage (void);         /* returns selected page */
int LCD_GetVisPage (void);         /* returns visible page */


/*********************************************************************
*
*       Color conversion
*/
unsigned         LCD_Color2Index     (LCD_COLOR Color);
LCD_COLOR        LCD_Index2Color     (int Index);
LCD_COLOR        LCD_Index2ColorEx   (int i, unsigned LayerIndex);

/*********************************************************************
*
*       LCD_X_...
*/
void LCD_X_InitController(unsigned LayerIndex); /* Callback function called from LCD_L0_Init() */

void LCD_X_Init(void);
void LCD_X_On  (void);
void LCD_X_Off (void);

char LCD_X_Read00(void);
char LCD_X_Read01(void);
void LCD_X_Write00(char c);
void LCD_X_Write01(char c);
void LCD_X_WriteM01(char * pData, int NumBytes);

#if defined(__cplusplus)
  }
#endif

#endif /* LCD_H */

/*************************** End of file ****************************/
