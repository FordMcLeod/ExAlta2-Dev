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
#include "clock.h"

/* Function prototypes*/
void PRINT_Stringln(USART_TypeDef* uart, char* data);
void PRINT_Char(USART_TypeDef* uart, char data);
void PRINT_time(USART_TypeDef* uart, time_t currentTime);
void PRINT_open(void);
void PRINT_close(void);
void PRINT_getBusy(void);
void PRINT_releaseBusy(void);

#endif
