/******************************************************************************
 * @file duts.h
 * @brief 
 * @author 
 * @version 
 ******************************************************************************/


#ifndef __DUTS_H
#define __DUTS_H

#include "em_usart.h"

void DUTS_initIRQs(USART_TypeDef* uart, IRQn_Type rxIRQn);
uint8_t DUTS_getChar(USART_TypeDef*);
void DUTS_PutChar(uint8_t, USART_TypeDef*);


#endif /* DUTS_H_ */
