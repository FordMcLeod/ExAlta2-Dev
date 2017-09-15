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
#include "em_timer.h"

#include "sleep.h"
#include "print.h"
#include "clockApp_stk.h"
#include "fatfs.h"
#include "microsd.h"

#define STACK_SIZE_FOR_TASK    (configMINIMAL_STACK_SIZE + 100)
#define TASK_PRIORITY          (tskIDLE_PRIORITY + 1)


/* Declare variables */
static uint32_t resetcause = 0;


/**************************************************************************//**
 * @brief Simple task which is blinking led
 * @param *pParameters pointer to parameters passed to the function
 *****************************************************************************/
static void LedBlink(void *pParameters)
{

  for (;;)
  {
    //GPIO_PortOutSetVal(LED_PORT, 1<<LED_PIN, 1<<LED_PIN);
    //vTaskDelay(pdMS_TO_TICKS(100));
    //GPIO_PortOutSetVal(LED_PORT, 0<<LED_PIN, 1<<LED_PIN);
    vTaskDelay(pdMS_TO_TICKS(5000));
    PRINT_time(UART1,time( NULL ));
    PRINT_Stringln(UART1,"Hello world!");
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

  clockSetup(resetcause);

  /* Enable BURTC interrupts */
  NVIC_ClearPendingIRQ( BURTC_IRQn );
  NVIC_EnableIRQ( BURTC_IRQn );

  /* Initialize SD card and FATFS */
  MICROSD_Init();
  FATFS_Init();

  unsigned int sdcd = GPIO_PinInGet(SDCD_PORT,SDCD_PIN);

  PRINT_time(UART1,time( NULL ));
  PRINT_Stringln(UART1,(char*)"HELLO");
  if (sdcd) {
    PRINT_time(UART1,time( NULL ));
    PRINT_Stringln(UART1,"SD Card detected!");
  }
  else {
    PRINT_time(UART1,time( NULL ));
    PRINT_Stringln(UART1,"No SD Card detected!");
  }
 
  /*Create two task for blinking leds*/
  xTaskCreate( LedBlink, (const char *) "LedBlink1", STACK_SIZE_FOR_TASK, NULL, TASK_PRIORITY, NULL);

  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();

  return 0;
}


