/***************************************************************************//**
 * @file print.c
 * @brief 
 * @author Stefan Damkjar
 * @version 
 ******************************************************************************/

#include "print.h"
#include "em_usart.h"
#include "clockApp_stk.h"
#include "clock_config.h"
#include "fatfs.h"
#include "microsd.h"
#include "ff.h"

FIL fsrc; /* File object */
uint8_t busy = 0;

/* Calendar struct */
static struct tm calendar;
/* Declare variables for LCD output*/
static char  displayStringBuf[13];
static char* displayString = displayStringBuf;

/***************************************************************************//**
 * @brief Must be null terminated.
 ******************************************************************************/
void PRINT_Stringln(USART_TypeDef* uart, char* data)
{
  // avoid taking over other print calls
  while(busy) __WFI();
  busy = 1;

  int i = 0;

  /* Open or create a log file and ready to append */
  FATFS_append(&fsrc, FILENAME);

  f_printf(&fsrc,"%s%c%c", data,'\n','\r');
  for(i = 0;data[i]!='\0';i++){
    USART_Tx(uart,data[i]);
  }
  USART_Tx(uart,'\n');
  USART_Tx(uart,'\r');
  
  /* Close the file */
  f_close(&fsrc);

  busy = 0;
}


/***************************************************************************//**
 * @brief Must be null terminated.
 ******************************************************************************/
void PRINT_String(USART_TypeDef* uart, char* data)
{
  // avoid taking over other print calls
  while(busy) ;
  busy = 1;

  int i = 0;

  /* Open or create a log file and ready to append */
  FATFS_append(&fsrc, FILENAME);

  f_printf(&fsrc,"%s", data);
  for(i = 0;data[i]!='\0';i++){
    USART_Tx(uart,data[i]);
  }
  
  /* Close the file */
  f_close(&fsrc);

  busy = 0;
}


/***************************************************************************//**
 * @brief
 ******************************************************************************/
void PRINT_Char(USART_TypeDef* uart, char data)
{
  USART_Tx(uart,data);
  f_printf(&fsrc,"%c", data);
}


/***************************************************************************//**
 * @brief
 ******************************************************************************/
void PRINT_arrayln(USART_TypeDef* uart, char* data,  uint8_t len)
{
  // avoid taking over other print calls
  while(busy) __WFI();
  busy = 1;

  int i = 0;

  /* Open or create a log file and ready to append */
  FATFS_append(&fsrc, FILENAME);

  for(i = 0;i < len;i++){
    USART_Tx(uart,data[i]);
    f_printf(&fsrc,"%c", data[i]);
  }
  USART_Tx(uart,'\n');
  USART_Tx(uart,'\r');
  f_printf(&fsrc,"%c%c",'\n','\r');
  
  /* Close the file */
  f_close(&fsrc);

  busy = 0;
}


/***************************************************************************//**
 * @brief
 ******************************************************************************/
void PRINT_array(USART_TypeDef* uart, char* data, uint8_t len)
{
  // avoid taking over other print calls
  while(busy) __WFI();
  busy = 1;

  int i = 0;

  

  for(i = 0;i < len;i++){
    USART_Tx(uart,data[i]);
    f_printf(&fsrc,"%c", data[i]);
  }
  
  /* Close the file */
  f_close(&fsrc);

  busy = 0;
}

void PRINT_time(USART_TypeDef* uart, time_t currentTime)
{
  uint32_t msecs = 1000 - (BURTC->COMP0 - BURTC->CNT)*1000/COUNTS_PER_SEC;

  /* Make string from calendar */
  calendar = * localtime( &currentTime );

  displayStringBuf[0] = 0x30 + (calendar.tm_hour / 10);
  displayStringBuf[1] = 0x30 + (calendar.tm_hour % 10);
  displayStringBuf[2] = ':';
  displayStringBuf[3] = 0x30 + (calendar.tm_min / 10);
  displayStringBuf[4] = 0x30 + (calendar.tm_min % 10);
  displayStringBuf[5] = ':';
  displayStringBuf[6] = 0x30 + (calendar.tm_sec / 10);
  displayStringBuf[7] = 0x30 + (calendar.tm_sec % 10);
  displayStringBuf[8] = '.';
  displayStringBuf[9] = 0x30 + (msecs / 100);
  displayStringBuf[10] = 0x30 + ((msecs / 10) % 10);
  displayStringBuf[11] = 0x30 + (msecs % 10);
  displayStringBuf[12] = '\0';

  PRINT_String(uart,displayString);
}

void PRINT_timeFast(USART_TypeDef* uart, time_t currentTime)
{
  uint32_t msecs = 1000 - (BURTC->COMP0 - BURTC->CNT)*1000/COUNTS_PER_SEC;
  uint8_t i = 0;

  /* Make string from calendar */
  calendar = * localtime( &currentTime );

  displayStringBuf[0] = 0x30 + (calendar.tm_hour / 10);
  displayStringBuf[1] = 0x30 + (calendar.tm_hour % 10);
  displayStringBuf[2] = ':';
  displayStringBuf[3] = 0x30 + (calendar.tm_min / 10);
  displayStringBuf[4] = 0x30 + (calendar.tm_min % 10);
  displayStringBuf[5] = ':';
  displayStringBuf[6] = 0x30 + (calendar.tm_sec / 10);
  displayStringBuf[7] = 0x30 + (calendar.tm_sec % 10);
  displayStringBuf[8] = '.';
  displayStringBuf[9] = 0x30 + (msecs / 100);
  displayStringBuf[10] = 0x30 + ((msecs / 10) % 10);
  displayStringBuf[11] = 0x30 + (msecs % 10);

  f_printf(&fsrc,"%s", displayStringBuf);
  for(i = 0;i<12;i++){
    USART_Tx(uart,displayStringBuf[i]);
  }
}

/***************************************************************************//**
 * @brief Must be null terminated.
 ******************************************************************************/
void PRINT_Debug(USART_TypeDef* uart, char* data)
{
 #ifdef DEBUG

  int i = 0;

  for(i = 0;data[i]!='\0';i++){
    USART_Tx(uart,data[i]);
  }
  USART_Tx(uart,'\n');
  USART_Tx(uart,'\r');
#endif
}


void PRINT_open(void)
{
  while(busy) __WFI();
  busy = 1;
  /* Open or create a log file and ready to append */
  FATFS_append(&fsrc, FILENAME);
}

void PRINT_close(void)
{
  /* Close the file */
  f_close(&fsrc);
  busy = 0;
}

