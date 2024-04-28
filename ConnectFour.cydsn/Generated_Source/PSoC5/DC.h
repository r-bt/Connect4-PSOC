/*******************************************************************************
* File Name: DC.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DC_H) /* Pins DC_H */
#define CY_PINS_DC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DC_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DC__PORT == 15 && ((DC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DC_Write(uint8 value);
void    DC_SetDriveMode(uint8 mode);
uint8   DC_ReadDataReg(void);
uint8   DC_Read(void);
void    DC_SetInterruptMode(uint16 position, uint16 mode);
uint8   DC_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DC_SetDriveMode() function.
     *  @{
     */
        #define DC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DC_DM_RES_UP          PIN_DM_RES_UP
        #define DC_DM_RES_DWN         PIN_DM_RES_DWN
        #define DC_DM_OD_LO           PIN_DM_OD_LO
        #define DC_DM_OD_HI           PIN_DM_OD_HI
        #define DC_DM_STRONG          PIN_DM_STRONG
        #define DC_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DC_MASK               DC__MASK
#define DC_SHIFT              DC__SHIFT
#define DC_WIDTH              1u

/* Interrupt constants */
#if defined(DC__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DC_SetInterruptMode() function.
     *  @{
     */
        #define DC_INTR_NONE      (uint16)(0x0000u)
        #define DC_INTR_RISING    (uint16)(0x0001u)
        #define DC_INTR_FALLING   (uint16)(0x0002u)
        #define DC_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DC_INTR_MASK      (0x01u) 
#endif /* (DC__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DC_PS                     (* (reg8 *) DC__PS)
/* Data Register */
#define DC_DR                     (* (reg8 *) DC__DR)
/* Port Number */
#define DC_PRT_NUM                (* (reg8 *) DC__PRT) 
/* Connect to Analog Globals */                                                  
#define DC_AG                     (* (reg8 *) DC__AG)                       
/* Analog MUX bux enable */
#define DC_AMUX                   (* (reg8 *) DC__AMUX) 
/* Bidirectional Enable */                                                        
#define DC_BIE                    (* (reg8 *) DC__BIE)
/* Bit-mask for Aliased Register Access */
#define DC_BIT_MASK               (* (reg8 *) DC__BIT_MASK)
/* Bypass Enable */
#define DC_BYP                    (* (reg8 *) DC__BYP)
/* Port wide control signals */                                                   
#define DC_CTL                    (* (reg8 *) DC__CTL)
/* Drive Modes */
#define DC_DM0                    (* (reg8 *) DC__DM0) 
#define DC_DM1                    (* (reg8 *) DC__DM1)
#define DC_DM2                    (* (reg8 *) DC__DM2) 
/* Input Buffer Disable Override */
#define DC_INP_DIS                (* (reg8 *) DC__INP_DIS)
/* LCD Common or Segment Drive */
#define DC_LCD_COM_SEG            (* (reg8 *) DC__LCD_COM_SEG)
/* Enable Segment LCD */
#define DC_LCD_EN                 (* (reg8 *) DC__LCD_EN)
/* Slew Rate Control */
#define DC_SLW                    (* (reg8 *) DC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DC_PRTDSI__CAPS_SEL       (* (reg8 *) DC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DC_PRTDSI__OE_SEL0        (* (reg8 *) DC__PRTDSI__OE_SEL0) 
#define DC_PRTDSI__OE_SEL1        (* (reg8 *) DC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DC_PRTDSI__OUT_SEL0       (* (reg8 *) DC__PRTDSI__OUT_SEL0) 
#define DC_PRTDSI__OUT_SEL1       (* (reg8 *) DC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DC_PRTDSI__SYNC_OUT       (* (reg8 *) DC__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DC__SIO_CFG)
    #define DC_SIO_HYST_EN        (* (reg8 *) DC__SIO_HYST_EN)
    #define DC_SIO_REG_HIFREQ     (* (reg8 *) DC__SIO_REG_HIFREQ)
    #define DC_SIO_CFG            (* (reg8 *) DC__SIO_CFG)
    #define DC_SIO_DIFF           (* (reg8 *) DC__SIO_DIFF)
#endif /* (DC__SIO_CFG) */

/* Interrupt Registers */
#if defined(DC__INTSTAT)
    #define DC_INTSTAT            (* (reg8 *) DC__INTSTAT)
    #define DC_SNAP               (* (reg8 *) DC__SNAP)
    
	#define DC_0_INTTYPE_REG 		(* (reg8 *) DC__0__INTTYPE)
#endif /* (DC__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DC_H */


/* [] END OF FILE */
