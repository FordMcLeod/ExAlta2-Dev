/***************************************************************************//**
 * @file clockApp_stk.h
 * @brief CALENDAR header file
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
#ifndef __CLOCKAPP_STK_H
#define __CLOCKAPP_STK_H

/* Include standard libraries */
#include <stdint.h>

#define INITIAL_SEC 	(0) 	/* 0 seconds (0-60, 60 = leap second)*/
#define INITIAL_MIN 	(0) 	/* 0 minutes (0-59) */
#define INITIAL_HOUR0	(12) 	/* 12 hours (0-23) */
#define INITIAL_MDAY 	(1) 	/* 1st day of the month (1 - 31) */
#define INITIAL_MON 	(0) 	/* January (0 - 11, 0 = January) */
#define INITIAL_YEAR 	(112) 	/* Year 2012 (year since 1900) */
#define INITIAL_WDAY 	(0) 	/* Sunday (0 - 6, 0 = Sunday) */
#define INITIAL_YDAT 	(0) 	/* 1st day of the year (0-365) */
#define INITIAL_ISDST 	(-1) 	/* Daylight saving time; enabled (>0), disabled (=0) or unknown (<0) */

/* Function prototypes */
void clockSetup(uint32_t);
void clockAppInit(void);
void clockAppBackup(void);
void clockAppRestore(void);

#endif
