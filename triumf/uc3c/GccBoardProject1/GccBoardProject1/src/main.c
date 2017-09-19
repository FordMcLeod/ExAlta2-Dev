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
#include <usart.h>
#include <stdio.h>
#include <stdint.h>

#  define USART                 (&AVR32_USART0)
#  define USART_RX_PIN          AVR32_USART0_RXD_2_PIN
#  define USART_RX_FUNCTION     AVR32_USART0_RXD_2_FUNCTION
#  define USART_TX_PIN          AVR32_USART0_TXD_2_PIN
#  define USART_TX_FUNCTION     AVR32_USART0_TXD_2_FUNCTION

#  define TARGET_PBACLK_FREQ_HZ   BOARD_OSC0_HZ// PBA clock target frequency, in Hz

#define BUFFER_SIZE 255
#define TEST_SIZE 1024

typedef unsigned int word;

volatile word testMemArray[TEST_SIZE] = {0};
unsigned int ram_errors = 0;
word previous_write = 0;
word next_write = 0;

char buffer[BUFFER_SIZE] = {0};

void PRINT_Stringln(char* data);
void Delay(uint16_t milliseconds);
void RAM_test(void);
uint16_t CRC_calc(uint8_t *start, uint8_t *end);

int main (void)
{
	sysclk_init();

	board_init();

	uint32_t flashSize = 64000;

	uint16_t crc     = 0;
	uint16_t old_crc = 0;
	
	static const gpio_map_t USART_GPIO_MAP =
	{
		{USART_RX_PIN, USART_RX_FUNCTION},
		{USART_TX_PIN, USART_TX_FUNCTION}
	};
	
	// USART options.
	static const usart_options_t USART_OPTIONS =
	{
		.baudrate     = 115200,
		.charlength   = 8,
		.paritytype   = USART_NO_PARITY,
		.stopbits     = USART_1_STOPBIT,
		.channelmode  = USART_NORMAL_CHMODE
	};
	
	// Assign GPIO to USART.
	gpio_enable_module(USART_GPIO_MAP,
	sizeof(USART_GPIO_MAP) / sizeof(USART_GPIO_MAP[0]));
	
	// Initialize USART in RS232 mode.
	usart_init_rs232(USART, &USART_OPTIONS, TARGET_PBACLK_FREQ_HZ);
	
	

	/* Insert application code here, after the board has been initialized. */
	
	AVR32_GPIO.port[0].oders = 1 << (19 & 0x1F); // The GPIO output driver is enabled for that pin.
	AVR32_GPIO.port[0].gpers = 1 << (19 & 0x1F); // The GPIO module controls that pin.

	  /* Infinite loop */
  while (1) {
    delay_ms(1000);
  	gpio_set_pin_high(AVR32_PIN_PA19);
    PRINT_Stringln("\rram\n");
    RAM_test();
    PRINT_Stringln("\rfla\n");
    crc = CRC_calc((void *) 0, (void *) flashSize);
    if (old_crc != crc) {
      sprintf(buffer,"\rCRC:%x\n",crc);
      PRINT_Stringln(buffer);
      old_crc = crc;
    }
    PRINT_Stringln("\rend\n");
    gpio_set_pin_low(AVR32_PIN_PA19);
  }
}

void PRINT_Stringln(char* data)
{
  // avoid taking over other print calls
  int i = 0;

  for(i = 0;data[i]!='\0';i++){
    usart_write_line(USART, &data[i]);
  }
}

void RAM_test(void) {
  word read = 0;
  unsigned int j = 0;
  previous_write = next_write;
  next_write = next_write ^ (word)(~0);
  for(j = 0; j<TEST_SIZE; j++) {
    read = testMemArray[j];
    if (read != previous_write) {
      // delayed read
      sprintf(buffer,"\rDR:%0x,%0x,%0x\n",j,read,previous_write);
      PRINT_Stringln(buffer);
      ram_errors++; 
    }
    testMemArray[j]= next_write;
    read = testMemArray[j];
    if (read != next_write) {
      // instantaneous read
      sprintf(buffer,"\rIR:%0x,%0x,%0x\n",j,read,previous_write);
      PRINT_Stringln(buffer);
      ram_errors++;
    }
  }
  sprintf(buffer,"\rRE:%u\n",ram_errors);
  PRINT_Stringln(buffer);
}


uint16_t CRC_calc(uint8_t *start, uint8_t *end)
{
  uint16_t crc = 0x0;
  uint8_t  *data;

  for (data = start; data < end; data++)
  {
    crc  = (crc >> 8) | (crc << 8);
    crc ^= *data;
    crc ^= (crc & 0xff) >> 4;
    crc ^= crc << 12;
    crc ^= (crc & 0xff) << 5;
  }
  return crc;
}
