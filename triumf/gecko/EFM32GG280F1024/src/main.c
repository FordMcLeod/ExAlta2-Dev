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
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_chip.h"
#include "em_emu.h"
#include "em_rmu.h"
#include "em_burtc.h"

#include "sleep.h"
#include "print.h"
#include "clock.h"
#include "clock_config.h"
#include "clockApp_stk.h"

#define STACK_SIZE_FOR_TASK    (configMINIMAL_STACK_SIZE + 100)
#define TASK_PRIORITY          (tskIDLE_PRIORITY + 1)

/* Structure with parameters for LedBlink */
typedef struct
{
  /* Delay between blink of led */
  portTickType delay;
  /* Number of led */
  int          ledNo;
} TaskParams_t;

/* Calendar struct for initial date setting */
static struct tm initialCalendar;

/* Declare variables */
static uint32_t resetcause = 0;
/* Calendar struct */
static struct tm calendar;
/* Declare variables for LCD output*/
static char displayStringBuf[9];
static char* displayString = displayStringBuf;
static time_t    currentTime;

/* Function prototypes */
void budSetup( void );

/**************************************************************************//**
 * @brief Simple task which is blinking led
 * @param *pParameters pointer to parameters passed to the function
 *****************************************************************************/
static void LedBlink(void *pParameters)
{

  for (;;)
  {
    GPIO_PortOutSetVal(LED_PORT, 1<<LED_PIN, 1<<LED_PIN);
    vTaskDelay(pdMS_TO_TICKS(100));
    GPIO_PortOutSetVal(LED_PORT, 0<<LED_PIN, 1<<LED_PIN);
    /* Make string from calendar */
	currentTime = time( NULL );
	calendar = * localtime( &currentTime );

    displayStringBuf[0] = 0x30 + (calendar.tm_hour / 10);
    displayStringBuf[1] = 0x30 + (calendar.tm_hour % 10);
    displayStringBuf[2] = ':';
    displayStringBuf[3] = 0x30 + (calendar.tm_min / 10);
    displayStringBuf[4] = 0x30 + (calendar.tm_min % 10);
    displayStringBuf[5] = ':';
    displayStringBuf[6] = 0x30 + (calendar.tm_sec / 10);
    displayStringBuf[7] = 0x30 + (calendar.tm_sec % 10);
    displayStringBuf[8] = '\0';

    printString(UART1,(char*)"Time: ");
    printStringln(UART1,(displayString));
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

  /* Read and clear RMU->RSTCAUSE as early as possible */
  resetcause = RMU->RSTCAUSE;
  RMU_ResetCauseClear();

  /* Initialize SLEEP driver, no calbacks are used */
  SLEEP_Init(NULL, NULL);
#if (configSLEEP_MODE < 3)
  /* do not let to sleep deeper than define */
  SLEEP_SleepBlockBegin((SLEEP_EnergyMode_t)(configSLEEP_MODE+1));
#endif

  /* Configure Backup Domain */
  budSetup();

  /* Setting up a structure to initialize the calendar
     for 1 January 2012 12:00:00
     The struct tm is declared in time.h
     More information for time.h library in http://en.wikipedia.org/wiki/Time.h */
  initialCalendar.tm_sec    =  0;    /* 0 seconds (0-60, 60 = leap second)*/
  initialCalendar.tm_min    =  0;    /* 0 minutes (0-59) */
  initialCalendar.tm_hour   =  12;   /* 12 hours (0-23) */
  initialCalendar.tm_mday   =  1;    /* 1st day of the month (1 - 31) */
  initialCalendar.tm_mon    =  0;    /* January (0 - 11, 0 = January) */
  initialCalendar.tm_year   =  112;  /* Year 2012 (year since 1900) */
  initialCalendar.tm_wday   =  0;    /* Sunday (0 - 6, 0 = Sunday) */
  initialCalendar.tm_yday   =  0;    /* 1st day of the year (0-365) */
  initialCalendar.tm_isdst  =  -1;   /* Daylight saving time; enabled (>0), disabled (=0) or unknown (<0) */

  /* Set the calendar */
  clockInit(&initialCalendar);

  enter_DefaultMode_from_RESET();

  unsigned int sdcd = GPIO_PinInGet(SDCD_PORT,SDCD_PIN);

  printStringln(UART1,(char*)"HELLO");
  if (sdcd) printStringln(UART1,"SD Card Detected");
  else printStringln(UART1,"No SD Card Detected");

  /* If waking from backup mode, restore time from retention registers */
  if (    (resetcause & RMU_RSTCAUSE_BUMODERST)
  && !(resetcause & RMU_RSTCAUSE_BUBODREG)
  && !(resetcause & RMU_RSTCAUSE_BUBODUNREG)
  && !(resetcause & RMU_RSTCAUSE_BUBODBUVIN)
  &&  (resetcause & RMU_RSTCAUSE_BUBODVDDDREG)
  && !(resetcause & RMU_RSTCAUSE_EXTRST)
  && !(resetcause & RMU_RSTCAUSE_PORST) )
  {

  /* Initialize display application */
  clockAppInit();

  /* Restore time from backup RTC + retention memory and print backup info*/
  clockAppRestore();

  /* Clear BURTC timestamp */
  BURTC_StatusClear();
  }
  /* If normal startup, initialize application and start BURTC */
  else
  {

    /* Initialize display application */
    clockAppInit();

    /* Start BURTC */
    BURTC_Enable( true );

    /* Backup initial calendar (initialize retention registers) */
    clockAppBackup();
  }

 
  /*Create two task for blinking leds*/
  xTaskCreate( LedBlink, (const char *) "LedBlink1", STACK_SIZE_FOR_TASK, NULL, TASK_PRIORITY, NULL);

  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();

  return 0;
}

/***************************************************************************//**
 * @brief Set up backup domain.
 ******************************************************************************/
void budSetup(void)
{
  /* Assign default TypeDefs */
  EMU_EM4Init_TypeDef em4Init = EMU_EM4INIT_DEFAULT;
  EMU_BUPDInit_TypeDef bupdInit = EMU_BUPDINIT_DEFAULT;

  /*Setup EM4 configuration structure */
  em4Init.lockConfig = true;
  em4Init.osc = emuEM4Osc_LFXO;
  em4Init.buRtcWakeup = false;
  em4Init.vreg = true;

  /* Setup Backup Power Domain configuration structure */
  bupdInit.probe = emuProbe_Disable;
  bupdInit.bodCal = false;
  bupdInit.statusPinEnable = false;
  bupdInit.resistor = emuRes_Res0;
  bupdInit.voutStrong = false;
  bupdInit.voutMed = false;
  bupdInit.voutWeak = false;
  bupdInit.inactivePower = emuPower_MainBU;
  bupdInit.activePower = emuPower_MainBU;
  bupdInit.enable = true;

  /* Unlock configuration */
  EMU_EM4Lock( false );

  /* Initialize EM4 and Backup Power Domain with init structs */
  EMU_BUPDInit( &bupdInit );
  EMU_EM4Init( &em4Init );

  /* Release reset for backup domain */
  RMU_ResetControl( rmuResetBU, false );

  /* Lock configuration */
  EMU_EM4Lock( true );
}



