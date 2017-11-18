/******************************************************************************
 * @file 2_leds_solution.c
 * @brief Blinking LEDs with STK solution
 * @author Silicon Labs
 * @version 1.18
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
 * obligation to support this Software. Silicon Labs is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Silicon Labs will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "InitDevice.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "croutine.h"

#include "em_device.h"
#include "em_gpio.h"
#include "em_chip.h"
#include "em_rmu.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "em_burtc.h"
#include "em_usart.h"
#include "em_leuart.h"

#include "sleep.h"
#include "print.h"
#include "clockApp_stk.h"
#include "fatfs.h"
#include "microsd.h"
#include "ff.h"
#include "duts.h"
#include "TPS2483.h"

#define STACK_SIZE_FOR_TASK    (configMINIMAL_STACK_SIZE + 100)
#define TASK_PRIORITY          (tskIDLE_PRIORITY + 1)
#define MUTEX_TIMEOUT          (pdMS_TO_TICKS(250))
#define LED_PERIOD			   (pdMS_TO_TICKS(1000))
#define CURR_PERIOD			   (pdMS_TO_TICKS(100))
#define MAX_DUT_LINE_LENGTH    (20)
#define DUT_MAX_RETRIES        (10)
#define DUT_WDT_TIMEOUT		   (pdMS_TO_TICKS(2000))
#define MAX_OVERCURR_COUNTS    (10)

/* Declare variables */
static uint32_t resetcause = 0;

xSemaphoreHandle gatekeeper = 0;

/* Structure with parameters for TASK_DutRx */
typedef struct
{
  uint8_t DUTnum;
  DUTNUM_TypeDef uart;
} RxTaskParams_t;


/**************************************************************************//**
 * @brief Simple task which is blinking led
 * @param *pParameters pointer to parameters passed to the function
 *****************************************************************************/
static void TASK_LedBlink(void *pParameters)
{

  TickType_t xLastWakeTime;
  const TickType_t xFrequency = LED_PERIOD;

  for (;;)
  {

	vTaskDelayUntil( &xLastWakeTime, xFrequency );
	GPIO_PinOutToggle(LED_PORT,LED_PIN);


	if (DUTS_needReset(DUT_A)){
	  GPIO_PinOutClear(DUT0_EN_PORT,DUT0_EN_PIN);
	  vTaskDelay(RESET_DELAY);
	  GPIO_PinOutSet(DUT0_EN_PORT,DUT0_EN_PIN);
	}
	if (DUTS_needReset(DUT_B)){
	  GPIO_PinOutClear(DUT1_EN_PORT,DUT1_EN_PIN);
	  vTaskDelay(RESET_DELAY);
	  GPIO_PinOutSet(DUT1_EN_PORT,DUT1_EN_PIN);
	}
	if (DUTS_needReset(DUT_C)){
	  GPIO_PinOutClear(DUT2_EN_PORT,DUT2_EN_PIN);
	  vTaskDelay(RESET_DELAY);
	  GPIO_PinOutSet(DUT2_EN_PORT,DUT2_EN_PIN);
	}
	if (DUTS_needReset(DUT_D)){
	  GPIO_PinOutClear(DUT3_EN_PORT,DUT3_EN_PIN);
	  vTaskDelay(RESET_DELAY);
	  GPIO_PinOutSet(DUT3_EN_PORT,DUT3_EN_PIN);
	}
  }
}

static void TASK_getCurr(void *pParameters)
{

  int curr0 = 0;
  int curr1 = 0;
  int curr2 = 0;
  int curr3 = 0;

  uint8_t highCurrCount0 = 0;
  uint8_t highCurrCount1 = 0;
  uint8_t highCurrCount2 = 0;
  uint8_t highCurrCount3 = 0;

  TickType_t xLastWakeTime;
  const TickType_t xFrequency = CURR_PERIOD;

  time_t timestamp = 0;

  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount();

  for (;;)
  {

	vTaskDelayUntil( &xLastWakeTime, xFrequency );

	timestamp = time( NULL );
	TPS2483_ReadShuntVoltage(I2C0,TPS2483_ADDR0,&curr0);
    TPS2483_ReadShuntVoltage(I2C0,TPS2483_ADDR1,&curr1);
    TPS2483_ReadShuntVoltage(I2C0,TPS2483_ADDR2,&curr2);
    TPS2483_ReadShuntVoltage(I2C0,TPS2483_ADDR3,&curr3);

    if(curr0 > 50000) highCurrCount0++;
    else highCurrCount0 = 0;
    if(curr1 > 50000) highCurrCount1++;
    else highCurrCount1 = 0;
    if(curr2 > 50000) highCurrCount2++;
    else highCurrCount2 = 0;
    if(curr3 > 50000) highCurrCount3++;
    else highCurrCount3 = 0;

	if(xSemaphoreTake(gatekeeper, MUTEX_TIMEOUT))
	{
	  PRINT_Time(USART1,timestamp);
	  PRINT_Current(USART1,curr0);
	  PRINT_Current(USART1,curr1);
	  PRINT_Current(USART1,curr2);
	  PRINT_Current(USART1,curr3);
	  PRINT_Char(USART1,'\n');
	  xSemaphoreGive(gatekeeper);
	}

	if(highCurrCount0 > MAX_OVERCURR_COUNTS){
	  DUTS_reset(DUT_A);
	  //DUTS_purge(DUT_A);
	  if(xSemaphoreTake(gatekeeper, MUTEX_TIMEOUT))
	  {
		PRINT_Time(USART1,time( NULL ));
		PRINT_Char(USART1,'A');
		PRINT_Stringln(USART1,"\tLatchup? Resetting..\n");
		xSemaphoreGive(gatekeeper);
	  }
	}
	if(highCurrCount1 > MAX_OVERCURR_COUNTS){
	  DUTS_reset(DUT_B);
	  //DUTS_purge(DUT_B);
	  if(xSemaphoreTake(gatekeeper, MUTEX_TIMEOUT))
	  {
		PRINT_Time(USART1,time( NULL ));
		PRINT_Char(USART1,'B');
		PRINT_Stringln(USART1,"\tLatchup? Resetting..\n");
		xSemaphoreGive(gatekeeper);
	  }
	}
	if(highCurrCount2 > MAX_OVERCURR_COUNTS){
	  DUTS_reset(DUT_C);
	  //DUTS_purge(DUT_C);
	  if(xSemaphoreTake(gatekeeper, MUTEX_TIMEOUT))
	  {
		PRINT_Time(USART1,time( NULL ));
		PRINT_Char(USART1,'C');
		PRINT_Stringln(USART1,"\tLatchup? Resetting..\n");
		xSemaphoreGive(gatekeeper);
	  }
	}
	if(highCurrCount3 > MAX_OVERCURR_COUNTS){
	  DUTS_reset(DUT_D);
	  //DUTS_purge(DUT_D);
	  if(xSemaphoreTake(gatekeeper, MUTEX_TIMEOUT))
	  {
		PRINT_Time(USART1,time( NULL ));
		PRINT_Char(USART1,'D');
		PRINT_Stringln(USART1,"\tLatchup? Resetting..\n");
		xSemaphoreGive(gatekeeper);
	  }
	}
  }
}

/**************************************************************************//**
 * @brief Simple task which is blinking led
 * @param *pParameters pointer to parameters passed to the function
 *****************************************************************************/
static void TASK_DutRx(void *pParameters)
{
  RxTaskParams_t* pData = (RxTaskParams_t*) pParameters;
  uint8_t data = 0;
  uint8_t charCount = 0;
  uint8_t noCharCount = 0;

  TickType_t lastMessageTime = 0;

  for (;;)
  {
  	data = DUTS_getChar(pData->uart);

  	if(xTaskGetTickCount()-lastMessageTime > DUT_WDT_TIMEOUT) {
  	  DUTS_reset(pData->uart);
  	  lastMessageTime = xTaskGetTickCount();
  	  //DUTS_purge(pData->uart);
  	  if(xSemaphoreTake(gatekeeper, MUTEX_TIMEOUT))
  	  {
		PRINT_Time(USART1,time( NULL ));
		PRINT_Char(USART1,pData->DUTnum);
		PRINT_Stringln(USART1,"\tNo response. Resetting..\n");
		xSemaphoreGive(gatekeeper);
  	  }
  	}

  	if (data == '\r') {
      lastMessageTime = xTaskGetTickCount();
      if(xSemaphoreTake(gatekeeper, MUTEX_TIMEOUT))
      {
		PRINT_Time(USART1,time( NULL ));
		PRINT_Char(USART1,pData->DUTnum);
		PRINT_Char(USART1,'\t');
		charCount = 0;
		noCharCount = 0;
		while(charCount < MAX_DUT_LINE_LENGTH)
		{
		  data = DUTS_getChar(pData->uart);
		  if(!data)
		  {
			  noCharCount++;
		  }
		  else
		  {
			  charCount++;
			  PRINT_Char(USART1,data);
			  noCharCount = 0;
		  }
		  if (data == '\n')
		  {
			  PRINT_fsync();
			  xSemaphoreGive(gatekeeper);
			  charCount = MAX_DUT_LINE_LENGTH;
		  }
		  else if (noCharCount > DUT_MAX_RETRIES)
		  {
			  PRINT_Char(USART1,'!');
			  PRINT_Char(USART1,pData->DUTnum);
			  PRINT_Char(USART1,'\n');
			  xSemaphoreGive(gatekeeper);
			  charCount = MAX_DUT_LINE_LENGTH;
			  //DUTS_purge(pData->uart);

		  }
		}
		xSemaphoreGive(gatekeeper);
      }
    }
  }
}


/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Chip errata */
  CHIP_Init();

  /* Read and clear RMU->RSTCAUSE as early as possible */
  resetcause = RMU->RSTCAUSE;
  RMU_ResetCauseClear();

  /* Initialize SLEEP driver, no callbacks are used */
  SLEEP_Init(NULL, NULL);
#if (configSLEEP_MODE < 3)
  /* do not let to sleep deeper than define */
  SLEEP_SleepBlockBegin((SLEEP_EnergyMode_t)(configSLEEP_MODE+1));
#endif

  enter_DefaultMode_from_RESET();

  CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_CORELEDIV2);
    CMU_ClockEnable(cmuClock_LFB, true);
    CMU_ClockEnable(cmuClock_CORELE, true);
    GPIO_PinModeSet(gpioPortC, 6, gpioModeInput, 1);
    LEUART_Init_TypeDef init = LEUART_INIT_DEFAULT;
    CMU_ClockEnable(cmuClock_LEUART1, true);
    LEUART_Reset(LEUART1);
    init.refFreq = CMU_ClockFreqGet(cmuClock_LEUART1);
    init.baudrate = 921600;
    LEUART_Init(LEUART1, &init);
    LEUART1->ROUTE |= LEUART_ROUTE_RXPEN;

  clockSetup(resetcause);

  /* Enable BURTC interrupts */
  NVIC_ClearPendingIRQ( BURTC_IRQn );
  NVIC_EnableIRQ( BURTC_IRQn );

  TPS2483_Init();

  unsigned int sdcd = GPIO_PinInGet(SD_CD_PORT,SD_CD_PIN);

  PRINT_Time(USART1,time( NULL ));
  PRINT_Stringln(USART1,(char*)"\tHELLO");


  if (sdcd) {
    PRINT_Time(USART1,time( NULL ));
    PRINT_Stringln(USART1,"\tSD Card detected!");
    /* Initialize SD card and FATFS */
    MICROSD_Init();
    FATFS_Init();
    PRINT_open();
  }
  else {
    PRINT_Time(USART1,time( NULL ));
    PRINT_Stringln(USART1,"\tNo SD Card detected!");
  }

  PRINT_fsync();

  gatekeeper = xSemaphoreCreateMutex();

  USART_BaudrateSyncSet(MICROSD_USART, 0, 16000000);

  /* Prepare UART Rx and Tx interrupts */
  DUTS_initIRQs(UART0,UART0_RX_IRQn);
  DUTS_initIRQs(USART0,USART0_RX_IRQn);
  DUTS_initIRQs(UART1,UART1_RX_IRQn);
  DUTS_initIRQs(LEUART1,LEUART1_IRQn);
  //DUTS_initIRQs(USART1,USART1_RX_IRQn);
  //DUTS_initIRQs(USART2,USART2_RX_IRQn);


  GPIO_PinOutSet(DUT0_EN_PORT,DUT0_EN_PIN);
  GPIO_PinOutSet(DUT1_EN_PORT,DUT1_EN_PIN);
  GPIO_PinOutSet(DUT2_EN_PORT,DUT2_EN_PIN);
  GPIO_PinOutSet(DUT3_EN_PORT,DUT3_EN_PIN);

  
  static RxTaskParams_t parametersToArx = { 'A', DUT_A };
  static RxTaskParams_t parametersToBrx = { 'B', DUT_B };
  static RxTaskParams_t parametersToCrx = { 'C', DUT_C };
  static RxTaskParams_t parametersToDrx = { 'D', DUT_D };
  
  xTaskCreate( TASK_DutRx, (const char *) "Arx", STACK_SIZE_FOR_TASK, &parametersToArx, TASK_PRIORITY+2, NULL);
  xTaskCreate( TASK_DutRx, (const char *) "Brx", STACK_SIZE_FOR_TASK, &parametersToBrx, TASK_PRIORITY+2, NULL);
  xTaskCreate( TASK_DutRx, (const char *) "Crx", STACK_SIZE_FOR_TASK, &parametersToCrx, TASK_PRIORITY+2, NULL);
  xTaskCreate( TASK_DutRx, (const char *) "Drx", STACK_SIZE_FOR_TASK, &parametersToDrx, TASK_PRIORITY+2, NULL);

  xTaskCreate( TASK_LedBlink, (const char *) "LedBlink1", STACK_SIZE_FOR_TASK, NULL, TASK_PRIORITY+1, NULL);

  xTaskCreate( TASK_getCurr, (const char *) "curr", STACK_SIZE_FOR_TASK, NULL, TASK_PRIORITY+2, NULL);

  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();

  return 0;
}


