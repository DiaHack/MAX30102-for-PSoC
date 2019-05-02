/*******************************************************************************
* File Name: MaxINT.h  
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

#if !defined(CY_PINS_MaxINT_H) /* Pins MaxINT_H */
#define CY_PINS_MaxINT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MaxINT_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MaxINT__PORT == 15 && ((MaxINT__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MaxINT_Write(uint8 value);
void    MaxINT_SetDriveMode(uint8 mode);
uint8   MaxINT_ReadDataReg(void);
uint8   MaxINT_Read(void);
void    MaxINT_SetInterruptMode(uint16 position, uint16 mode);
uint8   MaxINT_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MaxINT_SetDriveMode() function.
     *  @{
     */
        #define MaxINT_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MaxINT_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MaxINT_DM_RES_UP          PIN_DM_RES_UP
        #define MaxINT_DM_RES_DWN         PIN_DM_RES_DWN
        #define MaxINT_DM_OD_LO           PIN_DM_OD_LO
        #define MaxINT_DM_OD_HI           PIN_DM_OD_HI
        #define MaxINT_DM_STRONG          PIN_DM_STRONG
        #define MaxINT_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MaxINT_MASK               MaxINT__MASK
#define MaxINT_SHIFT              MaxINT__SHIFT
#define MaxINT_WIDTH              1u

/* Interrupt constants */
#if defined(MaxINT__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MaxINT_SetInterruptMode() function.
     *  @{
     */
        #define MaxINT_INTR_NONE      (uint16)(0x0000u)
        #define MaxINT_INTR_RISING    (uint16)(0x0001u)
        #define MaxINT_INTR_FALLING   (uint16)(0x0002u)
        #define MaxINT_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MaxINT_INTR_MASK      (0x01u) 
#endif /* (MaxINT__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MaxINT_PS                     (* (reg8 *) MaxINT__PS)
/* Data Register */
#define MaxINT_DR                     (* (reg8 *) MaxINT__DR)
/* Port Number */
#define MaxINT_PRT_NUM                (* (reg8 *) MaxINT__PRT) 
/* Connect to Analog Globals */                                                  
#define MaxINT_AG                     (* (reg8 *) MaxINT__AG)                       
/* Analog MUX bux enable */
#define MaxINT_AMUX                   (* (reg8 *) MaxINT__AMUX) 
/* Bidirectional Enable */                                                        
#define MaxINT_BIE                    (* (reg8 *) MaxINT__BIE)
/* Bit-mask for Aliased Register Access */
#define MaxINT_BIT_MASK               (* (reg8 *) MaxINT__BIT_MASK)
/* Bypass Enable */
#define MaxINT_BYP                    (* (reg8 *) MaxINT__BYP)
/* Port wide control signals */                                                   
#define MaxINT_CTL                    (* (reg8 *) MaxINT__CTL)
/* Drive Modes */
#define MaxINT_DM0                    (* (reg8 *) MaxINT__DM0) 
#define MaxINT_DM1                    (* (reg8 *) MaxINT__DM1)
#define MaxINT_DM2                    (* (reg8 *) MaxINT__DM2) 
/* Input Buffer Disable Override */
#define MaxINT_INP_DIS                (* (reg8 *) MaxINT__INP_DIS)
/* LCD Common or Segment Drive */
#define MaxINT_LCD_COM_SEG            (* (reg8 *) MaxINT__LCD_COM_SEG)
/* Enable Segment LCD */
#define MaxINT_LCD_EN                 (* (reg8 *) MaxINT__LCD_EN)
/* Slew Rate Control */
#define MaxINT_SLW                    (* (reg8 *) MaxINT__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MaxINT_PRTDSI__CAPS_SEL       (* (reg8 *) MaxINT__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MaxINT_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MaxINT__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MaxINT_PRTDSI__OE_SEL0        (* (reg8 *) MaxINT__PRTDSI__OE_SEL0) 
#define MaxINT_PRTDSI__OE_SEL1        (* (reg8 *) MaxINT__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MaxINT_PRTDSI__OUT_SEL0       (* (reg8 *) MaxINT__PRTDSI__OUT_SEL0) 
#define MaxINT_PRTDSI__OUT_SEL1       (* (reg8 *) MaxINT__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MaxINT_PRTDSI__SYNC_OUT       (* (reg8 *) MaxINT__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MaxINT__SIO_CFG)
    #define MaxINT_SIO_HYST_EN        (* (reg8 *) MaxINT__SIO_HYST_EN)
    #define MaxINT_SIO_REG_HIFREQ     (* (reg8 *) MaxINT__SIO_REG_HIFREQ)
    #define MaxINT_SIO_CFG            (* (reg8 *) MaxINT__SIO_CFG)
    #define MaxINT_SIO_DIFF           (* (reg8 *) MaxINT__SIO_DIFF)
#endif /* (MaxINT__SIO_CFG) */

/* Interrupt Registers */
#if defined(MaxINT__INTSTAT)
    #define MaxINT_INTSTAT            (* (reg8 *) MaxINT__INTSTAT)
    #define MaxINT_SNAP               (* (reg8 *) MaxINT__SNAP)
    
	#define MaxINT_0_INTTYPE_REG 		(* (reg8 *) MaxINT__0__INTTYPE)
#endif /* (MaxINT__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MaxINT_H */


/* [] END OF FILE */
