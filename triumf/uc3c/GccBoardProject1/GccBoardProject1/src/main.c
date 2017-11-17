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
#include <common_nvm.h>


#  define USART                 (&AVR32_USART0)
#  define USART_RX_PIN          AVR32_USART0_RXD_PIN
#  define USART_RX_FUNCTION     AVR32_USART0_RXD_FUNCTION
#  define USART_TX_PIN          AVR32_USART0_TXD_PIN
#  define USART_TX_FUNCTION     AVR32_USART0_TXD_FUNCTION

#  define TARGET_PBACLK_FREQ_HZ   BOARD_OSC0_HZ// PBA clock target frequency, in Hz

#define MAX_RETRIES 10

#define BUFFER_SIZE 255
#define TEST_SIZE 15000

typedef unsigned int word;

volatile word testMemArray[TEST_SIZE] = {0};
unsigned int ram_errors = 0;
word previous_write = 0;
word next_write = 0;
unsigned int irRetries = 0;

char buffer[BUFFER_SIZE] = {0};

void PRINT_Stringln(char* data);
void Delay(uint16_t milliseconds);
void RAM_test(void);
uint16_t CRC_calc(uint32_t start, uint32_t end);

int main (void)
{
	sysclk_init();

	board_init();



	uint16_t crc     = 0;
	unsigned int iteration = 0;
	
	static const gpio_map_t USART_GPIO_MAP =
	{
		{USART_RX_PIN, USART_RX_FUNCTION},
		{USART_TX_PIN, USART_TX_FUNCTION}
	};
	
	// USART options.
	static const usart_options_t USART_OPTIONS =
	{
		.baudrate     = 32786,
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
	
	usart_write_line(USART,"\rboot\n");

	/* Insert application code here, after the board has been initialized. */
	
	AVR32_GPIO.port[0].oders = 1 << (8 & 0x1F); // The GPIO output driver is enabled for that pin.
	AVR32_GPIO.port[0].gpers = 1 << (8 & 0x1F); // The GPIO module controls that pin.

	gpio_set_pin_high(AVR32_PIN_PA08);
	  /* Infinite loop */
  while (1) {
    gpio_toggle_pin(AVR32_PIN_PA08);
    usart_write_line(USART,"\rram\n");
    RAM_test();
    usart_write_line(USART,"\rfla\n");
	crc = CRC_calc(AVR32_FLASH_ADDRESS,AVR32_FLASH_ADDRESS+AVR32_FLASH_SIZE);
    sprintf(buffer,"\rCRC:%x\n",crc);
    usart_write_line(USART,buffer);
	sprintf(buffer,"\rend%u\n",iteration++);
    usart_write_line(USART,buffer);
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
      usart_write_line(USART,buffer);
      ram_errors++; 
    }
    testMemArray[j]= next_write;
    read = testMemArray[j];
    if (read != next_write) {
      // instantaneous read
      sprintf(buffer,"\rIR:%0x,%0x,%0x\n",j,read,previous_write);
      usart_write_line(USART,buffer);
      ram_errors++;
      irRetries++;
    }
    else irRetries = 0;

    if(irRetries > MAX_RETRIES){
      usart_write_line(USART,"\rTOO MANY IR ERRORS! Halting...\n");
      while (1){
        /* DO NOTHING */
      }
    }
  }
  sprintf(buffer,"\rRE:%u\n",ram_errors);
  usart_write_line(USART,buffer);
}


uint16_t CRC_calc(uint32_t start, uint32_t end)
{
  uint16_t crc = 0x0;
  uint32_t  address;
  uint8_t  data = 0;

  for (address = start; address < end; address++)
  {
    crc  = (crc >> 8) | (crc << 8);
	nvm_read_char(INT_FLASH, address, &data);
    crc ^= data;
    crc ^= (crc & 0xff) >> 4;
    crc ^= crc << 12;
    crc ^= (crc & 0xff) << 5;
  }
  return crc;
}
