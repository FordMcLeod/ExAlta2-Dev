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
#include "FreeRTOS.h"
#include "task.h"

FIL fsrc; /* File object */
uint8_t busy = 0;
uint8_t open = 0;

/* Calendar struct */
static struct tm calendar;
/* Declare variables for LCD output*/
static char  displayStringBuf[14];


/***************************************************************************//**
 * @brief Must be null terminated.
 ******************************************************************************/
void PRINT_Stringln(USART_TypeDef* uart, char* data)
{
  int i = 0;
  for(i = 0;data[i]!='\0';i++){
    USART_Tx(uart,data[i]);
  }

  if(open) f_printf(&fsrc,"%s", data);
}


/***************************************************************************//**
 * @brief
 ******************************************************************************/
void PRINT_Char(USART_TypeDef* uart, char data)
{
  USART_Tx(uart,data);
  if(open) f_printf(&fsrc,"%c", data);
}


void PRINT_time(USART_TypeDef* uart, time_t currentTime)
{
  uint32_t msecs = 1000 - (BURTC->COMP0 - BURTC->CNT)*1000/COUNTS_PER_SEC;
  uint8_t i = 0;

  /* Make string from calendar */
  calendar = * localtime( &currentTime );

  displayStringBuf[0] = '\r';
  displayStringBuf[1] = 0x30 + (calendar.tm_hour / 10);
  displayStringBuf[2] = 0x30 + (calendar.tm_hour % 10);
  displayStringBuf[3] = ':';
  displayStringBuf[4] = 0x30 + (calendar.tm_min / 10);
  displayStringBuf[5] = 0x30 + (calendar.tm_min % 10);
  displayStringBuf[6] = ':';
  displayStringBuf[7] = 0x30 + (calendar.tm_sec / 10);
  displayStringBuf[8] = 0x30 + (calendar.tm_sec % 10);
  displayStringBuf[9] = '.';
  displayStringBuf[10] = 0x30 + (msecs / 100);
  displayStringBuf[11] = 0x30 + ((msecs / 10) % 10);
  displayStringBuf[12] = 0x30 + (msecs % 10);
  displayStringBuf[13] = '\0';

  if(open) f_printf(&fsrc,"%s", displayStringBuf);
  for(i = 0;i<13;i++){
    USART_Tx(uart,displayStringBuf[i]);
  }
}


void PRINT_open(void)
{
  /* Open or create a log file and ready to append */
  if(!open) {
    if(FATFS_append(&fsrc, FILENAME) == FR_OK) {
      busy = 0;
      open = 1;
      PRINT_Stringln(UART1,"\nOpened SD card!\n");
    }
    else PRINT_Stringln(UART1,"\nFailed to open SD card!\n");
  }
}


void PRINT_close(void)
{
  while(busy) vTaskDelay(pdMS_TO_TICKS(1));
  /* Close the file */
  if(open) {
    if(f_close(&fsrc) == FR_OK) {
      busy = 0;
      open = 0;
      PRINT_Stringln(UART1,"Closed SD card!");
    }
    else PRINT_Stringln(UART1,"Failed to close SD card!");
  }
}


void PRINT_getBusy(void)
{
  while(busy) vTaskDelay(pdMS_TO_TICKS(1));
  busy = 1;
}


void PRINT_releaseBusy(void)
{
	f_sync(&fsrc);
  busy = 0;
}
