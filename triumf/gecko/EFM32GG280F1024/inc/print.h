/***************************************************************************//**
 * @file print.h
 * @brief 
 * @author Stefan Damkjar
 * @version 
 ******************************************************************************/

#ifndef __PRINT_H
#define __PRINT_H

/* Include libraries */
#include "em_usart.h"

/* Function prototypes*/
void println(USART_TypeDef* uart, char* data);
void print(USART_TypeDef* uart, char* data);

#endif