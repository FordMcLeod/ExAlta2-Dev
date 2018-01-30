/*
 * AT32UC3C2512C Port.c
 *
 * Created: 12/20/2017 11:59:48 AM
 * Author : Brendan
 */ 

#include <avr32/io.h>

// Force include all headers just to make sure it builds.
#include "flashc.h"
#include "gpio.h"
#include "intc.h"
#include "pm_uc3c.h"
#include "power_clocks_lib.h"
#include "sleep.h"
#include "scif_uc3c.h"
#include "tc.h"
#include "usart.h"

#include "uc3d_defines_fix.h"
#include "uc3l3_l4_defines_fix.h"
#include "mrepeat.h"
#include "preprocessor.h"
#include "stringz.h"
#include "tpaste.h"
#include "trampoline_uc3.h"
#include "compiler.h"
#include "status_codes.h"

#include "board.h"
#include "user_board.h"
#include "interrupt.h"
#include "parts.h"
#include "interrupt_avr32.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "croutine.h"
#include "list.h"
#include "mpu_wrappers.h"
#include "portable.h"
#include "projdefs.h"
#include "queue.h"
#include "semphr.h"
#include "StackMacros.h"
#include "task.h"
#include "timers.h"
#include "portmacro.h"

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

