/*
 * i2c.c
 *
 *  Created on: Apr 2, 2015
 *      Author: sdamkjar
 */

#include <stdbool.h>
#include "i2c.h"
#include "em_i2c.h"
#include "em_gpio.h"

uint8_t TxBuffer[I2C_MAX_TX_BUFFER_SIZE];
uint16_t TxBufferSize = 0;
uint16_t TxBufferHead = 0;
uint16_t TxBufferTail = 0;

uint8_t RxBuffer[I2C_MAX_RX_BUFFER_SIZE];
uint16_t RxBufferSize = 0;
uint16_t RxBufferHead = 0;
uint16_t RxBufferTail = 0;

/**************************************************************************//**
 * @brief  Setup I2C
 *****************************************************************************/
void I2C0_setup(void)
{
  /* Setting up to enable slave mode */
  I2C0->SADDR |= I2C_ADDRESS << _I2C_SADDR_ADDR_SHIFT;
  I2C0->CTRL  |= I2C_CTRL_SLAVE | I2C_CTRL_AUTOACK | I2C_CTRL_AUTOSN;

  I2C0->IFC = ~0;
  I2C0->IEN = I2C_IEN_ADDR | I2C_IEN_SSTOP;
  NVIC_EnableIRQ(I2C0_IRQn);
}

status_t commandRdy(void)
{
	if ( RxBufferSize >= 2 ) return MEMS_SUCCESS;
	else return MEMS_ERROR;
}

/**************************************************************************//**
 * @brief  Write data to the I2C transmit buffer (will be pending transmit)
 * @param  size Bytes to write to I2C
 * @param  point to read data from
 * @return Return error if buffer is full
 *****************************************************************************/
status_t writeI2C(uint8_t* ptr)
{
	if ( TxBufferSize < I2C_MAX_TX_BUFFER_SIZE ) {

		TxBufferSize++;

		TxBuffer[TxBufferHead++] = *ptr;
		TxBufferHead %= I2C_MAX_TX_BUFFER_SIZE;


		return MEMS_SUCCESS;
	}

	else return MEMS_ERROR;
}

/**************************************************************************//**
 * @brief  Read pull from the I2C recieve buffer
 * @param  size Bytes to read from I2C
 * @param  point to write data to
 * @return Return error if buffer is empty
 *****************************************************************************/
status_t readI2C(uint8_t* ptr)
{

	if ( RxBufferSize  > 0 ) {

		*ptr = (uint8_t)RxBuffer[RxBufferTail];
		RxBuffer[RxBufferTail++] = '\0';
		RxBufferTail %= I2C_MAX_RX_BUFFER_SIZE;

		RxBufferSize--;

	}

	if ( RxBufferSize >= 2 ) return MEMS_SUCCESS;

	else return MEMS_ERROR;
}

/**************************************************************************//**
 * @brief I2C Interrupt Handler.
 *        The interrupt table is in assembly startup file startup_efm32.s
 *****************************************************************************/
void I2C0_IRQHandler(void)
{
  int status;
  status = I2C0->IF;

  if (status & I2C_IF_ADDR)
  {
    /* Address Match */
    I2C_IntClear(I2C0, I2C_IFC_ADDR);
    if (I2C0->RXDATA & 0x01)
    {
      /* Mater read, enable slave Tx */
      I2C0->IEN |= I2C_IEN_ACK;
      I2C0->TXDATA = TxBuffer[TxBufferHead++];
    }
    else
    {
      /* Mater write, enable slave Rx */
      I2C0->IEN |= I2C_IEN_RXDATAV;
    }
  }
  else if (status & I2C_IF_RXDATAV)
  {
    /* Data received */
	TxBuffer[TxBufferHead++] = I2C0->RXDATA;
  }
  else if (status & I2C_IF_ACK)
  {
    /* ACK received, send next data */
    I2C_IntClear(I2C0, I2C_IFC_ACK);
    I2C0->TXDATA = TxBuffer[TxBufferHead++];
  }
  else
  {
    /* Stop received, Tx/Rx is ended */
    I2C_IntClear(I2C0, I2C_IFC_SSTOP);
    I2C0->IEN &= ~(I2C_IEN_ACK + I2C_IEN_RXDATAV);
    TxBufferHead = 0;
  }
}
