/*******************************************************************************
* File Name: RESET.h  
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

#if !defined(CY_PINS_RESET_H) /* Pins RESET_H */
#define CY_PINS_RESET_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RESET_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RESET__PORT == 15 && ((RESET__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RESET_Write(uint8 value);
void    RESET_SetDriveMode(uint8 mode);
uint8   RESET_ReadDataReg(void);
uint8   RESET_Read(void);
void    RESET_SetInterruptMode(uint16 position, uint16 mode);
uint8   RESET_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RESET_SetDriveMode() function.
     *  @{
     */
        #define RESET_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RESET_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RESET_DM_RES_UP          PIN_DM_RES_UP
        #define RESET_DM_RES_DWN         PIN_DM_RES_DWN
        #define RESET_DM_OD_LO           PIN_DM_OD_LO
        #define RESET_DM_OD_HI           PIN_DM_OD_HI
        #define RESET_DM_STRONG          PIN_DM_STRONG
        #define RESET_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RESET_MASK               RESET__MASK
#define RESET_SHIFT              RESET__SHIFT
#define RESET_WIDTH              1u

/* Interrupt constants */
#if defined(RESET__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RESET_SetInterruptMode() function.
     *  @{
     */
        #define RESET_INTR_NONE      (uint16)(0x0000u)
        #define RESET_INTR_RISING    (uint16)(0x0001u)
        #define RESET_INTR_FALLING   (uint16)(0x0002u)
        #define RESET_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RESET_INTR_MASK      (0x01u) 
#endif /* (RESET__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RESET_PS                     (* (reg8 *) RESET__PS)
/* Data Register */
#define RESET_DR                     (* (reg8 *) RESET__DR)
/* Port Number */
#define RESET_PRT_NUM                (* (reg8 *) RESET__PRT) 
/* Connect to Analog Globals */                                                  
#define RESET_AG                     (* (reg8 *) RESET__AG)                       
/* Analog MUX bux enable */
#define RESET_AMUX                   (* (reg8 *) RESET__AMUX) 
/* Bidirectional Enable */                                                        
#define RESET_BIE                    (* (reg8 *) RESET__BIE)
/* Bit-mask for Aliased Register Access */
#define RESET_BIT_MASK               (* (reg8 *) RESET__BIT_MASK)
/* Bypass Enable */
#define RESET_BYP                    (* (reg8 *) RESET__BYP)
/* Port wide control signals */                                                   
#define RESET_CTL                    (* (reg8 *) RESET__CTL)
/* Drive Modes */
#define RESET_DM0                    (* (reg8 *) RESET__DM0) 
#define RESET_DM1                    (* (reg8 *) RESET__DM1)
#define RESET_DM2                    (* (reg8 *) RESET__DM2) 
/* Input Buffer Disable Override */
#define RESET_INP_DIS                (* (reg8 *) RESET__INP_DIS)
/* LCD Common or Segment Drive */
#define RESET_LCD_COM_SEG            (* (reg8 *) RESET__LCD_COM_SEG)
/* Enable Segment LCD */
#define RESET_LCD_EN                 (* (reg8 *) RESET__LCD_EN)
/* Slew Rate Control */
#define RESET_SLW                    (* (reg8 *) RESET__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RESET_PRTDSI__CAPS_SEL       (* (reg8 *) RESET__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RESET_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RESET__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RESET_PRTDSI__OE_SEL0        (* (reg8 *) RESET__PRTDSI__OE_SEL0) 
#define RESET_PRTDSI__OE_SEL1        (* (reg8 *) RESET__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RESET_PRTDSI__OUT_SEL0       (* (reg8 *) RESET__PRTDSI__OUT_SEL0) 
#define RESET_PRTDSI__OUT_SEL1       (* (reg8 *) RESET__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RESET_PRTDSI__SYNC_OUT       (* (reg8 *) RESET__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RESET__SIO_CFG)
    #define RESET_SIO_HYST_EN        (* (reg8 *) RESET__SIO_HYST_EN)
    #define RESET_SIO_REG_HIFREQ     (* (reg8 *) RESET__SIO_REG_HIFREQ)
    #define RESET_SIO_CFG            (* (reg8 *) RESET__SIO_CFG)
    #define RESET_SIO_DIFF           (* (reg8 *) RESET__SIO_DIFF)
#endif /* (RESET__SIO_CFG) */

/* Interrupt Registers */
#if defined(RESET__INTSTAT)
    #define RESET_INTSTAT            (* (reg8 *) RESET__INTSTAT)
    #define RESET_SNAP               (* (reg8 *) RESET__SNAP)
    
	#define RESET_0_INTTYPE_REG 		(* (reg8 *) RESET__0__INTTYPE)
#endif /* (RESET__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RESET_H */


/* [] END OF FILE */
