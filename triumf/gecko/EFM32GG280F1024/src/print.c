/***************************************************************************//**
 * @file print.c
 * @brief 
 * @author Stefan Damkjar
 * @version 
 ******************************************************************************/

#include "print.h"
#include "em_usart.h"
#include "em_leuart.h"
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
void PRINT_Stringln_USART(USART_TypeDef* uart, char* data)
{
  int i = 0;
  for(i = 0;data[i]!='\0';i++){
    USART_Tx(uart,data[i]);
  }

  if(open) f_printf(&fsrc,"%s", data);
}
void PRINT_Stringln_LEUART(LEUART_TypeDef* leuart, char* data)
{
  int i = 0;
  for(i = 0;data[i]!='\0';i++){
    LEUART_Tx(leuart,data[i]);
  }

  if(open) f_printf(&fsrc,"%s", data);
}


/***************************************************************************//**
 * @brief
 ******************************************************************************/
void PRINT_Char_USART(USART_TypeDef* uart, char data)
{
  USART_Tx(uart,data);
  if(open) f_printf(&fsrc,"%c", data);
}
void PRINT_Char_LEUART(LEUART_TypeDef* leuart, char data)
{
  LEUART_Tx(leuart,data);
  if(open) f_printf(&fsrc,"%c", data);
}


void PRINT_Time_USART(USART_TypeDef* uart, time_t currentTime)
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
void PRINT_Time_LEUART(LEUART_TypeDef* leuart, time_t currentTime)
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
	  LEUART_Tx(leuart,displayStringBuf[i]);
  }
}

void PRINT_Current_USART(USART_TypeDef* uart, int curr)
{
	uint8_t i = 0;

	displayStringBuf[0] = '\t';
	if(curr < 0) {
		displayStringBuf[1] = '-';
		curr = -curr;
	}
	else displayStringBuf[1] = '+';
	displayStringBuf[2] = 0x30 + (curr / 100000);
	if(displayStringBuf[2] == '0') displayStringBuf[2] = ' ';
	displayStringBuf[3] = 0x30 + ((curr / 10000) % 10);
	if(displayStringBuf[3] == '0') displayStringBuf[3] = ' ';
	displayStringBuf[4] = 0x30 + ((curr /  1000) % 10);
	displayStringBuf[5] = '.';
	displayStringBuf[6] = 0x30 + ((curr /   100) % 10);
	displayStringBuf[7] = 0x30 + ((curr /    10) % 10);
	displayStringBuf[8] = 'm';
	displayStringBuf[9] = 'A';
	displayStringBuf[10] = '\0';
    if(open) f_printf(&fsrc,"%s", displayStringBuf);
    for(i = 0;i<10;i++){
	  USART_Tx(uart,displayStringBuf[i]);
    }
}
void PRINT_Current_LEUART(LEUART_TypeDef* leuart, int curr)
{
	uint8_t i = 0;

	displayStringBuf[0] = '\t';
	if(curr < 0) {
		displayStringBuf[1] = '-';
		curr = -curr;
	}
	else displayStringBuf[1] = '+';
	displayStringBuf[2] = 0x30 + (curr / 100000);
	if(displayStringBuf[2] == '0') displayStringBuf[2] = ' ';
	displayStringBuf[3] = 0x30 + ((curr / 10000) % 10);
	if(displayStringBuf[3] == '0') displayStringBuf[3] = ' ';
	displayStringBuf[4] = 0x30 + ((curr /  1000) % 10);
	displayStringBuf[5] = '.';
	displayStringBuf[6] = 0x30 + ((curr /   100) % 10);
	displayStringBuf[7] = 0x30 + ((curr /    10) % 10);
	displayStringBuf[8] = 'm';
	displayStringBuf[9] = 'A';
	displayStringBuf[10] = '\0';
    if(open) f_printf(&fsrc,"%s", displayStringBuf);
    for(i = 0;i<10;i++){
	  LEUART_Tx(leuart,displayStringBuf[i]);
    }
}


FRESULT PRINT_open(void)
{
  FRESULT res = FR_OK;

  /* Open or create a log file and ready to append */
  if(!open) {
    if(FATFS_append(&fsrc, FILENAME) == FR_OK) {
      busy = 0;
      open = 1;
      PRINT_Stringln(USART1,"\nOpened SD card!\n");
    }
    else {
	  PRINT_Stringln(USART1,"\nFailed to open SD card!\n");
    }
  }
  return res;
}


FRESULT PRINT_close(void)
{
  while(busy) vTaskDelay(pdMS_TO_TICKS(1));
  FRESULT res;

  /* Close the file */
  res = f_close(&fsrc);
  if(res == FR_OK) {
	busy = 0;
	open = 0;
	PRINT_Stringln(USART1,"Closed SD card!");
  }
  else {
	PRINT_Stringln(USART1,"Failed to close SD card!");
  }
  return res;
}


void PRINT_getBusy(void)
{
  while(busy) vTaskDelay(pdMS_TO_TICKS(1));
  busy = 1;
}


void PRINT_releaseBusy(void)
{
  if(open) f_sync(&fsrc);
  busy = 0;
}
