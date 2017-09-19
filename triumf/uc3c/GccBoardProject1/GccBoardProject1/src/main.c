/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>

#include <gpio.h>
#include <delay.h>

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();

	/* Insert application code here, after the board has been initialized. */
	
	AVR32_GPIO.port[0].oders = 1 << (19 & 0x1F); // The GPIO output driver is enabled for that pin.
	AVR32_GPIO.port[0].gpers = 1 << (19 & 0x1F); // The GPIO module controls that pin.

	while (true) {
		gpio_toggle_pin(AVR32_PIN_PA19);
		delay_ms(200);
	}
}
