/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2009  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V4.00 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUI_TOUCH_X.C
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include "device.h"
#include "GUI.h"
#include "GUI_X.h"

/*********************************************************************
*
*       GUI_TOUCH_X_ActivateX
*/
void GUI_TOUCH_X_ActivateX(void) 
{
    /* Prepare the measurement in Y by switching on the measurement 
    *  voltage in X.
    */
    CYTOUCH_ACTIVATE_X();	
}


/*********************************************************************
*
*       GUI_TOUCH_X_ActivateY
*/
void GUI_TOUCH_X_ActivateY(void)
{
    /* Prepare the measurement in X by switching on the measurement 
    *  voltage in Y.
    */
    CYTOUCH_ACTIVATE_Y();		
}


/*********************************************************************
*
*       GUI_TOUCH_X_MeasureX
*/
int  GUI_TOUCH_X_MeasureX (void) 
{    
    /* GUI_TOUCH_X_MeasureX is called from GUI_TOUCH_Exec() to return 
    *  the measurement values from the A/D converter for the X-axes.
    */
    int16 sampleX;
    sampleX = CYTOUCH_MEASURE();    
    /* Determine if the screen is pressed */
    if (CYTOUCH_TOUCHED() == 0) {   
      sampleX = -1;
    }
    return sampleX;    
}


/*********************************************************************
*
*       GUI_TOUCH_X_MeasureY
*/
int  GUI_TOUCH_X_MeasureY (void) 
{    
    /* GUI_TOUCH_X_MeasureY is called from GUI_TOUCH_Exec() to return 
    *  the measurement values from the A/D converter for the Y-axes.
    */
    int16 sampleY;
    sampleY = CYTOUCH_MEASURE();    
    /* Determine if the screen is pressed */
    if (CYTOUCH_TOUCHED() == 0) {   
      sampleY = -1;
    }
    return sampleY; 
}
