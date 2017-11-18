/******************************************************************************
 * @file duts.h
 * @brief 
 * @author 
 * @version 
 ******************************************************************************/


#ifndef __DUTS_H
#define __DUTS_H

#include "em_usart.h"
#include "em_leuart.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define DUTS_initIRQs(_1, _2) 	_Generic((_1),									\
										 USART_TypeDef*:  DUTS_initIRQs_USART,	\
										 LEUART_TypeDef*: DUTS_initIRQs_LEUART	\
										 )(_1, _2)

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

typedef enum
{
  DUT_A		=	0,
  DUT_B		=	1,
  DUT_C		=	2,
  DUT_D		=	3
} DUTNUM_TypeDef;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/


void DUTS_initIRQs_USART(USART_TypeDef* usart, IRQn_Type rxIRQn);
void DUTS_initIRQs_LEUART(LEUART_TypeDef* leuart, IRQn_Type rxIRQn);
uint8_t DUTS_getChar(DUTNUM_TypeDef dutNum);
void DUTS_PutChar(uint8_t, DUTNUM_TypeDef dutNum);


#endif /* DUTS_H_ */
