#include "em_device.h"
#include "em_chip.h"
#include "em_usart.h"
#include "em_gpio.h"

#include <stdio.h>

#include "InitDevice.h"


#define BUFFER_SIZE 255
#define TEST_SIZE 30000
#define MAX_RETRIES 10

typedef unsigned int word;

volatile word testMemArray[TEST_SIZE] = {0};
unsigned int ram_errors = 0;
unsigned int irRetries = 0;
word previous_write = 0;
word next_write = 0;

char buffer[BUFFER_SIZE] = {0};

void PRINT_Stringln(USART_TypeDef* uart, char* data);
void RAM_test(void);
uint16_t CRC_calc(uint8_t *start, uint8_t *end);


int main(void)
{
  /* Chip errata */
  CHIP_Init();

  enter_DefaultMode_from_RESET();

  uint32_t flashSize = 0;

  uint16_t crc     = 0;
  unsigned int iteration = 0;

  /* Find the size of the flash. DEVINFO->MSIZE is the
   * size in KB so left shift by 10. */
  flashSize = ((DEVINFO->MSIZE & _DEVINFO_MSIZE_FLASH_MASK) >> _DEVINFO_MSIZE_FLASH_SHIFT)
              << 10;

  /* Infinite loop */
  while (1) {
    PRINT_Stringln(USART0,"\rram\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    RAM_test();
    PRINT_Stringln(USART0,"\rfla\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    crc = CRC_calc((void *) 0, (void *) flashSize);
    sprintf(buffer,"\rCRC:%x\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n",crc);
    PRINT_Stringln(USART0,buffer);
    sprintf(buffer,"\rend%u\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n",iteration++);
    PRINT_Stringln(USART0,buffer);
    GPIO_PinOutToggle(LED_PORT,LED_PIN);
  }
}


void PRINT_Stringln(USART_TypeDef* uart, char* data)
{
  // avoid taking over other print calls
  int i = 0;

  //USART_Tx(uart,'\r');
  for(i = 0;data[i]!='\0';i++){
    USART_Tx(uart,data[i]);
  }
  //USART_Tx(uart,'\n');
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
      sprintf(buffer,"\rDR:%0x,%0x,%0x\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n",j,read,previous_write);
      PRINT_Stringln(USART0,buffer);
      ram_errors++; 
    }
    testMemArray[j]= next_write;
    read = testMemArray[j];
    if (read != next_write) {
      // instantaneous read
      sprintf(buffer,"\rIR:%0x,%0x,%0x\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n",j,read,previous_write);
      PRINT_Stringln(USART0,buffer);
      ram_errors++;
      irRetries++;
    }
    else irRetries = 0;

    if(irRetries > MAX_RETRIES){
		  PRINT_Stringln(USART0,"\rTOO MANY IR ERRORS! Halting...\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    	while (1){
    		/* DO NOTHING */
    	}
    }
  }
  sprintf(buffer,"\rRE:%u\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n",ram_errors);

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
