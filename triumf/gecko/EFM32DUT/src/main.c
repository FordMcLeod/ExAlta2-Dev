#include "em_device.h"
#include "em_chip.h"
#include "em_usart.h"
#include "em_gpio.h"

#include "InitDevice.h"

void PRINT_Stringln(USART_TypeDef* uart, char* data);
void Delay(uint16_t milliseconds);


int main(void)
{
  /* Chip errata */
  CHIP_Init();

  enter_DefaultMode_from_RESET();

  uint8_t toggle = 0;

  /* Infinite loop */
  while (1) {
  	GPIO_PortOutSetVal(LED_PORT, toggle<<LED_PIN, 1<<LED_PIN);
    toggle = !toggle;

    Delay(2000);

    PRINT_Stringln(USART0,"\t Hello from the other side!");
  	
  }
}

void PRINT_Stringln(USART_TypeDef* uart, char* data)
{
  // avoid taking over other print calls
  int i = 0;

  for(i = 0;data[i]!='\0';i++){
    USART_Tx(uart,data[i]);
  }
  USART_Tx(uart,'\n');
  USART_Tx(uart,'\r');
  USART_Tx(uart,'\0');
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
