#include <asf.h>

#include <gpio.h>
#include <delay.h>

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
sysclk_init();
	board_init();

	/* Insert application code here, after the board has been initialized. */
	
	AVR32_GPIO.port[0].oders = 1 << (8 & 0x1F); // The GPIO output driver is enabled for that pin.
	AVR32_GPIO.port[0].gpers = 1 << (8 & 0x1F); // The GPIO module controls that pin.

	while (true) {
		gpio_toggle_pin(AVR32_PIN_PA08);
		delay_ms(200);
	}
}