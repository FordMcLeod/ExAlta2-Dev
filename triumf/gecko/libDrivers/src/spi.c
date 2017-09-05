
/**************************************************************************//**
 * THIS CONTENT HAS BEEN ALTERED FROM THE ORIGINAL SOFTWARE AND IS SUBJECT TO
 * EXISTING LICENSE TERMS AND RESTRICTIONS FROM A THIRD PARTY
 *****************************************************************************/

/**************************************************************************//**
 * @file spi.c
 * @brief SPI
 * @author Silicon Labs
 * @version 1.14
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
 * obligation to support this Software. Silicon Labs is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Silicon Labs will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/



/* Driver Includes */
#include "spi.h"

/* EFM32 Includes */
#include "em_device.h"
#include "em_usart.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"


/* Buffer pointers and indexes */
char* slaveTxBuffer;
int slaveTxBufferSize;
volatile int slaveTxBufferIndex;
char* slaveRxBuffer;
int slaveRxBufferSize;
volatile int slaveRxBufferIndex;
char* masterRxBuffer;
int masterRxBufferSize;
volatile int masterRxBufferIndex;


/**************************************************************************//**
 * @brief Setup a USART as SPI
 * @param spiNumber is the number of the USART to use (e.g. 1 USART1)
 * @param location is the GPIO location to use for the device
 * @param master set if the SPI is to be master
 *****************************************************************************/
void SPI_setup(USART_TypeDef *spi, uint8_t location, bool master)
{
  USART_InitSync_TypeDef initsync = USART_INITSYNC_DEFAULT;
  USART_PrsTriggerInit_TypeDef initprs = USART_INITPRSTRIGGER_DEFAULT;

  CMU_Clock_TypeDef clock;

  /* Determining USART */
  switch ((int)spi)
  {
  case (int)USART0:
    spi   = USART0;
    clock = cmuClock_USART0;
    break;
  case (int)USART1:
    spi   = USART1;
    clock = cmuClock_USART1;
    break;
  case (int)USART2:
    spi   = USART2;
    clock = cmuClock_USART2;
    break;
  default:
    return;
  }

  /* Enabling clock to USART peripheral */
  CMU_ClockEnable(clock, true);

  /* Initializing USART in synchronous mode */
  initsync.baudrate              = 115200;
  initsync.databits              = usartDatabits8;
  initsync.master                = master;
  initsync.msbf                  = true;
  initsync.clockMode             = usartClockMode0;
  #if defined( USART_INPUT_RXPRS ) && defined( USART_TRIGCTRL_AUTOTXTEN )
  initsync.prsRxEnable           = false;
  initsync.prsRxCh               = false;
  initsync.autoTx                = false;
  #endif

  USART_InitSync(spi, &initsync);
  
  /* Initializing Peripheral Reflex System Trigger */
  initprs.rxTriggerEnable        = false;
  initprs.txTriggerEnable        = false;
  initprs.prsTriggerChannel      = usartPrsTriggerCh0;

  USART_InitPrsTrigger(spi, &initprs);

  /* Enable signal CS for slave mode */
  if (!master)
  {
    spi->ROUTE |= USART_ROUTE_CSPEN;
  } 

  /* Enable signals CLK, RX, TX and set location */
  spi->ROUTE |= USART_ROUTE_CLKPEN | USART_ROUTE_RXPEN |
  	  USART_ROUTE_TXPEN | (location << _USART_ROUTE_LOCATION_SHIFT);
}



/**************************************************************************//**
 * @brief USART1 RX IRQ Handler Setup
 * @param receiveBuffer points to where to place recieved data
 * @param receiveBufferSize indicates the number of bytes to receive
 *****************************************************************************/
void SPI1_setupRXInt(char* receiveBuffer, int receiveBufferSize)
{
  USART_TypeDef *spi = USART1;

  /* Setting up pointer and indexes */
  slaveRxBuffer      = receiveBuffer;
  slaveRxBufferSize  = receiveBufferSize;
  slaveRxBufferIndex = 0;

  /* Clear RX */
  spi->CMD = USART_CMD_CLEARRX;

  /* Enable interrupts */
  NVIC_ClearPendingIRQ(USART1_RX_IRQn);
  NVIC_EnableIRQ(USART1_RX_IRQn);
  spi->IEN |= USART_IEN_RXDATAV;
}



/**************************************************************************//**
 * @brief USART1 TX IRQ Handler Setup
 * @param transmitBuffer points to the data to send
 * @param transmitBufferSize indicates the number of bytes to send
 *****************************************************************************/
void SPI1_setupTXInt(char* transmitBuffer, int transmitBufferSize)
{
  USART_TypeDef *spi = USART1;

  /* Setting up pointer and indexes */
  slaveTxBuffer      = transmitBuffer;
  slaveTxBufferSize  = transmitBufferSize;
  slaveTxBufferIndex = 0;

  /* Clear TX */
  spi->CMD = USART_CMD_CLEARTX;

  /* Enable interrupts */
  NVIC_ClearPendingIRQ(USART1_TX_IRQn);
  NVIC_EnableIRQ(USART1_TX_IRQn);
  spi->IEN |= USART_IEN_TXBL;
}



/**************************************************************************//**
 * @brief Setting up RX interrupts from USART2 RX
 * @param receiveBuffer points to where received data is to be stored
 * @param bytesToReceive indicates the number of bytes to receive
 *****************************************************************************/
void SPI2_setupRXInt(char* receiveBuffer, int bytesToReceive)
{
  USART_TypeDef *spi = USART2;

  /* Setting up pointer and indexes */
  masterRxBuffer      = receiveBuffer;
  masterRxBufferSize  = bytesToReceive;
  masterRxBufferIndex = 0;

  /* Flushing rx */
  spi->CMD = USART_CMD_CLEARRX;

  /* Enable interrupts */
  NVIC_ClearPendingIRQ(USART2_RX_IRQn);
  NVIC_EnableIRQ(USART2_RX_IRQn);
  spi->IEN = USART_IEN_RXDATAV;
}



/**************************************************************************//**
 * @brief USART2 TX IRQ Handler Setup
 * @param transmitBuffer points to the data to send
 * @param transmitBufferSize indicates the number of bytes to send
 *****************************************************************************/
void SPI2_setupTXInt(char* transmitBuffer, int transmitBufferSize)
{
  USART_TypeDef *spi = USART2;

  /* Setting up pointer and indexes */
  slaveTxBuffer      = transmitBuffer;
  slaveTxBufferSize  = transmitBufferSize;
  slaveTxBufferIndex = 0;

  /* Clear TX */
  spi->CMD = USART_CMD_CLEARTX;

  /* Enable interrupts */
  NVIC_ClearPendingIRQ(USART2_TX_IRQn);
  NVIC_EnableIRQ(USART2_TX_IRQn);
  spi->IEN |= USART_IEN_TXBL;
}



/**************************************************************************//**
 * @brief USART1 IRQ Handler Setup
 * @param receiveBuffer points to where received data is to be stored
 * @param receiveBufferSize indicates the number of bytes to receive
 * @param transmitBuffer points to the data to send
 * @param transmitBufferSize indicates the number of bytes to send
 *****************************************************************************/
void SPI1_setupSlaveInt(char* receiveBuffer, int receiveBufferSize, char* transmitBuffer, int transmitBufferSize)
{
  SPI1_setupRXInt(receiveBuffer, receiveBufferSize);
  SPI1_setupTXInt(transmitBuffer, transmitBufferSize);
}



/**************************************************************************//**
 * @brief USART2 IRQ Handler Setup
 * @param receiveBuffer points to where received data is to be stored
 * @param receiveBufferSize indicates the number of bytes to receive
 * @param transmitBuffer points to the data to send
 * @param transmitBufferSize indicates the number of bytes to send
 *****************************************************************************/
void SPI2_setupSlaveInt(char* receiveBuffer, int receiveBufferSize, char* transmitBuffer, int transmitBufferSize)
{
  SPI2_setupRXInt(receiveBuffer, receiveBufferSize);
  SPI2_setupTXInt(transmitBuffer, transmitBufferSize);
}



/**************************************************************************//**
 * @brief USART1 RX IRQ Handler
 *****************************************************************************/
void USART1_RX_IRQHandler(void)
{
  USART_TypeDef *spi = USART1;
  uint8_t       rxdata;

  if (spi->STATUS & USART_STATUS_RXDATAV)
  {
    /* Reading out data */
    rxdata = spi->RXDATA;

    if (slaveRxBufferIndex < slaveRxBufferSize)
    {
      /* Store Data */
      slaveRxBuffer[slaveRxBufferIndex] = rxdata;
      slaveRxBufferIndex++;
    }
  }
}



/**************************************************************************//**
 * @brief USART1 TX IRQ Handler
 *****************************************************************************/
void USART1_TX_IRQHandler(void)
{
  USART_TypeDef *spi = USART1;

  if (spi->STATUS & USART_STATUS_TXBL)
  {
    /* Checking that valid data is to be transferred */
    if (slaveTxBuffer != 0)
    {
      /* Writing new data */
      spi->TXDATA = slaveTxBuffer[slaveTxBufferIndex];
      slaveTxBufferIndex++;
      /*Checking if more data is to be transferred */
      if (slaveTxBufferIndex == slaveTxBufferSize)
      {
        slaveTxBuffer = 0;
      }
    }
    else
    {
      /* Sending 0 if no data to send */
      spi->TXDATA = 0;
    }
  }
}



/**************************************************************************//**
 * @brief USART2 RX IRQ Handler
 *****************************************************************************/
void USART2_RX_IRQHandler(void)
{
  USART_TypeDef *spi = USART2;
  uint8_t       rxdata;

  if (spi->STATUS & USART_STATUS_RXDATAV)
  {
    /* Reading out data */
    rxdata = spi->RXDATA;

    if (masterRxBuffer != 0)
    {
      /* Store Data */
      masterRxBuffer[masterRxBufferIndex] = rxdata;
      masterRxBufferIndex++;

      if (masterRxBufferIndex == masterRxBufferSize)
      {
        masterRxBuffer = 0;
      }
    }
  }
}



/**************************************************************************//**
 * @brief USART2 TX IRQ Handler
 *****************************************************************************/
void USART2_TX_IRQHandler(void)
{
  USART_TypeDef *spi = USART2;

  if (spi->STATUS & USART_STATUS_TXBL)
  {
    /* Checking that valid data is to be transferred */
    if (slaveTxBuffer != 0)
    {
      /* Writing new data */
      spi->TXDATA = slaveTxBuffer[slaveTxBufferIndex];
      slaveTxBufferIndex++;
      /*Checking if more data is to be transferred */
      if (slaveTxBufferIndex == slaveTxBufferSize)
      {
        slaveTxBuffer = 0;
      }
    }
    else
    {
      /* Sending 0 if no data to send */
      spi->TXDATA = 0;
    }
  }
}
