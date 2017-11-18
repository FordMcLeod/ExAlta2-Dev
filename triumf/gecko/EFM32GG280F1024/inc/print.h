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
#include "ff.h"


/* Function prototypes*/
void PRINT_Stringln(USART_TypeDef* uart, char* data);
void PRINT_Char(USART_TypeDef* uart, char data);
void PRINT_Time(USART_TypeDef* uart, time_t currentTime);
void PRINT_Current(USART_TypeDef* uart, int curr);


FRESULT PRINT_open(void);
FRESULT PRINT_close(void);

void PRINT_fsync(void);

#endif
