/***************************************************************************//**
 * @file print.h
 * @brief 
 * @author Stefan Damkjar
 * @version 
 ******************************************************************************/

#ifndef __PRINT_H
#define __PRINT_H

#define FILENAME "logfile.txt"

#define PRINT_Stringln(_1, _2) 	_Generic((_1),									\
										 USART_TypeDef*:  PRINT_Stringln_USART,	\
										 LEUART_TypeDef*: PRINT_Stringln_LEUART	\
										 )(_1, _2)

#define PRINT_Char(_1, _2) 		_Generic((_1),									\
										USART_TypeDef*:  PRINT_Char_USART,		\
										LEUART_TypeDef*: PRINT_Char_LEUART		\
										)(_1, _2)

#define PRINT_Time(_1, _2) 		_Generic((_1),									\
										USART_TypeDef*:  PRINT_Time_USART,		\
										LEUART_TypeDef*: PRINT_Time_LEUART		\
										)(_1, _2)

#define PRINT_Current(_1, _2) 	_Generic((_1),									\
										USART_TypeDef*:  PRINT_Current_USART,	\
										LEUART_TypeDef*: PRINT_Current_LEUART	\
										)(_1, _2)

/* Include libraries */
#include "em_usart.h"
#include "clock.h"
#include "ff.h"


/* Function prototypes*/
void PRINT_Stringln_USART(USART_TypeDef* uart, char* data);
void PRINT_Stringln_LEUART(LEUART_TypeDef* leuart, char* data);
void PRINT_Char_USART(USART_TypeDef* uart, char data);
void PRINT_Char_LEUART(LEUART_TypeDef* uart, char data);
void PRINT_Time_USART(USART_TypeDef* uart, time_t currentTime);
void PRINT_Time_LEUART(LEUART_TypeDef* uart, time_t currentTime);
void PRINT_Current_USART(USART_TypeDef* uart, int curr);
void PRINT_Current_LEUART(LEUART_TypeDef* uart, int curr);


FRESULT PRINT_open(void);
FRESULT PRINT_close(void);
void PRINT_getBusy(void);
void PRINT_releaseBusy(void);

#endif
