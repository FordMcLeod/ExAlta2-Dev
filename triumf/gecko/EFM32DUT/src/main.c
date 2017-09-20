#include "em_device.h"
#include "em_chip.h"
#include "em_usart.h"
#include "em_gpio.h"

#include <stdio.h>

#include "InitDevice.h"


#define BUFFER_SIZE 255
#define TEST_SIZE 1024

typedef unsigned int word;

volatile word testMemArray[TEST_SIZE] = {0};
unsigned int ram_errors = 0;
word previous_write = 0;
word next_write = 0;

char buffer[BUFFER_SIZE] = {0};

void PRINT_Stringln(USART_TypeDef* uart, char* data);
void Delay(uint16_t milliseconds);
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
    Delay(1000);
  	GPIO_PinOutSet(LED_PORT,LED_PIN);
    PRINT_Stringln(USART0,"\rram\n");
    RAM_test();
    PRINT_Stringln(USART0,"\rfla\n");
    crc = CRC_calc((void *) 0, (void *) flashSize);
    sprintf(buffer,"\rCRC:%x\n",crc);
    PRINT_Stringln(USART0,buffer);
    sprintf(buffer,"\rend%u\n",iteration++);
    PRINT_Stringln(USART0,buffer);
    GPIO_PinOutClear(LED_PORT,LED_PIN);
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


/******************************************************************************
 * @brief Delay function
 *****************************************************************************/
void Delay(uint16_t milliseconds)
{
  /* Enable clock for TIMER0 */
  CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER0;
  
  /* Set prescaler to maximum */
  TIMER0->CTRL = (TIMER0->CTRL & ~_TIMER_CTRL_PRESC_MASK) |  TIMER_CTRL_PRESC_DIV1024;
  
  /* Clear TIMER0 counter value */
  TIMER0->CNT = 0;
  
  /* Start TIMER0 */
  TIMER0->CMD = TIMER_CMD_START;
  
  /* Wait until counter value is over the threshold */
  while(TIMER0->CNT < 13*milliseconds){
   /* Do nothing, just wait */ 
  }
  
  /* Stop TIMER0 */
  TIMER0->CMD = TIMER_CMD_STOP;
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
      PRINT_Stringln(USART0,buffer);
      ram_errors++; 
    }
    testMemArray[j]= next_write;
    read = testMemArray[j];
    if (read != next_write) {
      // instantaneous read
      sprintf(buffer,"\rIR:%0x,%0x,%0x\n",j,read,previous_write);
      PRINT_Stringln(USART0,buffer);
      ram_errors++;
    }
  }
  sprintf(buffer,"\rRE:%u\n",ram_errors);
  PRINT_Stringln(USART0,buffer);
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
