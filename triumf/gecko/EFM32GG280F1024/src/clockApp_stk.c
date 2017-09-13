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

/* Include other */
#include "clock.h"
#include "clock_config.h"
#include "clockApp_stk.h"

/* Declare variables for time keeping */
//static uint32_t  burtcCount = 0;
static uint32_t  burtcOverflowCounter = 0;
static uint32_t  burtcOverflowIntervalRem;
static uint32_t  burtcTimestamp;

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
  if ( BURTC_IntGet() & BURTC_IF_COMP0 )
  {
    BURTC_CompareSet( 0, BURTC_CompareGet(0) + COUNTS_BETWEEN_UPDATE );
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
