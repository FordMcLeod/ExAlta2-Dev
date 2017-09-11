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

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "croutine.h"

#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_chip.h"

#include "sleep.h"

#define LED_PORT    gpioPortC
#define LED_PIN     12

#define STACK_SIZE_FOR_TASK    (configMINIMAL_STACK_SIZE + 10)
#define TASK_PRIORITY          (tskIDLE_PRIORITY + 1)

/* Structure with parameters for LedBlink */
typedef struct
{
  /* Delay between blink of led */
  portTickType delay;
  /* Number of led */
  int          ledNo;
} TaskParams_t;


/**************************************************************************//**
 * @brief Simple task which is blinking led
 * @param *pParameters pointer to parameters passed to the function
 *****************************************************************************/
static void LedBlink(void *pParameters)
{
  TaskParams_t     * pData = (TaskParams_t*) pParameters;

  for (;;)
  {
	  GPIO_PortOutSetVal(LED_PORT, 1<<LED_PIN, 1<<LED_PIN);
	  vTaskDelay(pdMS_TO_TICKS(100));
	  GPIO_PortOutSetVal(LED_PORT, 0<<LED_PIN, 1<<LED_PIN);
	  vTaskDelay(pdMS_TO_TICKS(100));
  }
}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Chip errata */
  CHIP_Init();

  /* Initialize SLEEP driver, no calbacks are used */
  SLEEP_Init(NULL, NULL);
#if (configSLEEP_MODE < 3)
  /* do not let to sleep deeper than define */
  SLEEP_SleepBlockBegin((SLEEP_EnergyMode_t)(configSLEEP_MODE+1));
#endif

  /* Enable clock for GPIO */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Configure LED_PORT pin LED_PIN (User LED) as push/pull outputs */
  GPIO_PinModeSet(LED_PORT,         /* Port */
                  LED_PIN,          /* Pin */
                  gpioModePushPull, /* Mode */
                  0 );              /* Output value */

  /*Create two task for blinking leds*/
  xTaskCreate( LedBlink, (const char *) "LedBlink1", STACK_SIZE_FOR_TASK, NULL, TASK_PRIORITY, NULL);

  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();

  return 0;
}



