/***************************************************************************//**
 * @file clockApp_stk.c
 * @brief Application handling calendar display and user input in 
 *        EFM32 Backup Power Domain Application Note
 * @author Silicon Labs
 * @version 1.26
 *******************************************************************************
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

/* Include standard libraries */ 
#include <stdint.h>
#include <stddef.h>

/* Include emlib */
#include "em_burtc.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_gpio.h"
#include "em_emu.h"
#include "em_rmu.h"

/* Include other */
#include "clock.h"
#include "clock_config.h"
#include "clockApp_stk.h"

#include "InitDevice.h"

/* Declare variables for time keeping */
//static uint32_t  burtcCount = 0;
static uint32_t  burtcOverflowCounter = 0;
static uint32_t  burtcOverflowIntervalRem;
static uint32_t  burtcTimestamp;

/* Calendar struct for initial date setting */
static struct tm initialCalendar;

/***************************************************************************//**
 * @brief RTC Interrupt Handler, invoke callback if defined.
 *        The interrupt table is in assembly startup file startup_efm32gg.s
 *        Do critical tasks in interrupt handler. Other tasks are handled in main
 *        while loop.
 ******************************************************************************/
void BURTC_IRQHandler(void)
{
  /*   Interrupt source: compare match */
  /*   Increment compare value and
   *   update TFT display            */

  static uint8_t LED_state = 0;


  if ( BURTC_IntGet() & BURTC_IF_COMP0 )
  {
    BURTC_CompareSet( 0, BURTC_CompareGet(0) + COUNTS_BETWEEN_UPDATE );
    GPIO_PortOutSetVal(LED_PORT, LED_state<<LED_PIN, 1<<LED_PIN);
    LED_state = !LED_state;
    BURTC_IntClear( BURTC_IF_COMP0 );
  }

  /* Interrupt source: counter overflow */
  /*   Increase overflow counter 
   *   and backup calendar              */
  if ( BURTC_IntGet() & BURTC_IF_OF )
  {
    clockOverflow( );
    clockAppBackup();
    BURTC_IntClear( BURTC_IF_OF );
  }

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
  em4Init.osc = emuEM4Osc_LFRCO;
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


void clockSetup(uint32_t resetcause)
{
  /* Configure Backup Domain */
  //budSetup();



  /* Setting up a structure to initialize the calendar
	 for 1 January 2012 12:00:00
	 The struct tm is declared in time.h
	 More information for time.h library in http://en.wikipedia.org/wiki/Time.h */
  initialCalendar.tm_sec    =  INITIAL_SEC;    	/* 0 seconds (0-60, 60 = leap second)*/
  initialCalendar.tm_min    =  INITIAL_MIN;    	/* 0 minutes (0-59) */
  initialCalendar.tm_hour   =  INITIAL_HOUR0;   /* 12 hours (0-23) */
  initialCalendar.tm_mday   =  INITIAL_MDAY;    /* 1st day of the month (1 - 31) */
  initialCalendar.tm_mon    =  INITIAL_MON;    	/* January (0 - 11, 0 = January) */
  initialCalendar.tm_year   =  INITIAL_YEAR;  	/* Year 2012 (year since 1900) */
  initialCalendar.tm_wday   =  INITIAL_WDAY;    /* Sunday (0 - 6, 0 = Sunday) */
  initialCalendar.tm_yday   =  INITIAL_YDAT;    /* 1st day of the year (0-365) */
  initialCalendar.tm_isdst  =  INITIAL_ISDST;   /* Daylight saving time; enabled (>0), disabled (=0) or unknown (<0) */

  /* Set the calendar */
  clockInit(&initialCalendar);

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

  /* Enable BURTC interrupt on compare match and counter overflow */
  BURTC_IntEnable( BURTC_IF_COMP0 | BURTC_IF_OF );


}


/***************************************************************************//**
 * @brief Initialize application
 *
 ******************************************************************************/
void clockAppInit(void)
{
  /* Compute overflow interval (integer) and remainder */
  burtcOverflowIntervalRem = ((uint64_t)UINT32_MAX+1)%COUNTS_BETWEEN_UPDATE;

  /* Set BURTC compare value for first wakeup */
  BURTC_CompareSet( 0, COUNTS_BETWEEN_UPDATE );

}



/***************************************************************************//**
 * @brief  Backup CALENDAR to retention registers
 *
 *   RET[0].REG : number of BURTC overflows
 *   RET[1].REG : epoch offset
 *
 ******************************************************************************/
void clockAppBackup(void)
{
  /* Write overflow counter to retention memory */
  BURTC_RetRegSet( 0, clockGetOverflowCounter() );

  /* Write local epoch offset to retention memory */
  BURTC_RetRegSet( 1, clockGetStartTime() );
}



/***************************************************************************//**
 * @brief  Restore CALENDAR from retention registers
 *
 *
 ******************************************************************************/
void clockAppRestore( void )
{
  uint32_t burtcCount;
  uint32_t burtcStart;
  uint32_t nextUpdate ;

  /* Store current BURTC value for consistency in display output within this function */
  burtcCount = BURTC_CounterGet();

  /* Timestamp is BURTC value at time of main power loss */
  burtcTimestamp = BURTC_TimestampGet();

  /* Read overflow counter from retention memory */  
  burtcOverflowCounter = BURTC_RetRegGet( 0 );

  /* Check for overflow while in backup mode 
     Assume that overflow interval >> backup source capacity 
     i.e. that overflow has only occured once during main power loss */
  if ( burtcCount < burtcTimestamp )
  {
    burtcOverflowCounter++;
  }
  
  /* Restore epoch offset from retention memory */
  clockSetStartTime( BURTC_RetRegGet( 1 ) );

  /* Restore clock overflow counter */
  clockSetOverflowCounter( burtcOverflowCounter );

  /* Calculate start point for current BURTC count cycle 
     If (COUNTS_BETWEEN_UPDATE/burtcOverflowInterval) is not an integer,
     BURTC value at first update is different between each count cycle */
  burtcStart = (burtcOverflowCounter * (COUNTS_BETWEEN_UPDATE - burtcOverflowIntervalRem)) % COUNTS_BETWEEN_UPDATE;

  /*  Calculate compare value for next display update. 
      Add 1 extra UPDATE_INTERVAL to be sure that counter doesn't 
      pass COMP value before interrupts are enabled */
  nextUpdate = burtcStart + ((burtcCount / COUNTS_BETWEEN_UPDATE) +1 ) * COUNTS_BETWEEN_UPDATE ;
  BURTC_CompareSet( 0, nextUpdate );
}
