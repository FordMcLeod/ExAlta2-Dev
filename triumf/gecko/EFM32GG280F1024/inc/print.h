/***************************************************************************//**
 * @file print.h
 * @brief 
 * @author Stefan Damkjar
 * @version 
 ******************************************************************************/

#ifndef __PRINT_H
#define __PRINT_H

#define FILENAME "logfile.txt"

/* Include libraries */
#include "em_usart.h"

/* Function prototypes*/
void PRINT_Stringln(USART_TypeDef* uart, char* data);
void PRINT_String(USART_TypeDef* uart, char* data);
void PRINT_Char(USART_TypeDef* uart, char data);
void PRINT_arrayln(USART_TypeDef* uart, char* data,  uint8_t len);
void PRINT_array(USART_TypeDef* uart, char* data, uint8_t len);
void PRINT_time(USART_TypeDef* uart, static time_t currentTime)

#endif
