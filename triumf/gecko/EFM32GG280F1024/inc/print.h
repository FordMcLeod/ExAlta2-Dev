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
void printStringln(USART_TypeDef* uart, char* data);
void printString(USART_TypeDef* uart, char* data);
void printChar(USART_TypeDef* uart, char data);
void println(USART_TypeDef* uart, char* data,  uint8_t len);
void print(USART_TypeDef* uart, char* data, uint8_t len);

#endif
