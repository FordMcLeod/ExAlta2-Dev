#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_i2c.h"
#include "em_chip.h"
#include "InitDevice.h"
#include "TPS2483.h"

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

int main(void)
{
  /* Chip errata */
  CHIP_Init();

  enter_DefaultMode_from_RESET();

  /* Turn current sensor on */
  GPIO_PortOutSetVal(DUT3EN_PORT, 1<<DUT3EN_PIN, 1<<DUT3EN_PIN);
  GPIO_PortOutSetVal(DUT2EN_PORT, 1<<DUT2EN_PIN, 1<<DUT2EN_PIN);
  GPIO_PortOutSetVal(DUT1EN_PORT, 1<<DUT1EN_PIN, 1<<DUT1EN_PIN);
  GPIO_PortOutSetVal(DUT0EN_PORT, 1<<DUT0EN_PIN, 1<<DUT0EN_PIN);
  Delay(100); /* Wait */

  TPS2483_Init();

  uint16_t val = 0;
  int curr = 0;
  int sv = 0;
  int bv = 0;
  int pwr = 0;

  /* Infinite loop */
  while (1) {

	  TPS2483_RegisterGet(I2C0,0x80,TPS2483_RegConfig,&val);

	  /* Turn LED off */
	  GPIO_PortOutSetVal(LED_PORT, 0x0, 1<<LED_PIN);
	  Delay(100); /* Wait */


	  TPS2483_ReadShuntVoltage(I2C0,0x80,&sv);
	  Delay(100); /* Wait */
	  TPS2483_ReadBusVoltage(I2C0,0x80,&bv);
	  Delay(100); /* Wait */

	  /* Turn LED on */
	  GPIO_PortOutSetVal(LED_PORT, 1<<LED_PIN, 1<<LED_PIN);
	  Delay(100); /* Wait */

  }
}
