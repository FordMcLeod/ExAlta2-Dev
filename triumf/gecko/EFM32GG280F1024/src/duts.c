/******************************************************************************
 * @file duts.c
 * @brief 
 * @author 
 * @version 
 ******************************************************************************/

#define BUF_DEFAULT {{0},0,0,0,0}
#define BUFFERSIZE 1024

#include "em_usart.h"
#include "FreeRTOS.h"
#include "task.h"

typedef struct {
	char data[BUFFERSIZE];
	uint16_t wrI;
	uint16_t rdI;
	uint16_t pendingBytes;
	uint8_t  overflow;
} data_buffer;

data_buffer rxBuf_UART0  = BUF_DEFAULT;
data_buffer txBuf_UART0  = BUF_DEFAULT;
data_buffer rxBuf_UART1  = BUF_DEFAULT;
data_buffer txBuf_UART1  = BUF_DEFAULT;
data_buffer rxBuf_USART0 = BUF_DEFAULT;
data_buffer txBuf_USART0 = BUF_DEFAULT;
data_buffer rxBuf_USART1 = BUF_DEFAULT;
data_buffer txBuf_USART1 = BUF_DEFAULT;
data_buffer rxBuf_USART2 = BUF_DEFAULT;
data_buffer txBuf_USART2 = BUF_DEFAULT;


/**************************************************************************//**
 * @brief UART0 TX IRQ Handler
 *****************************************************************************/
void UART0_RX_IRQHandler(void)
{
  /* Check for RX data valid interrupt */
  if (UART0->STATUS & UART_STATUS_RXDATAV)
  {
    /* Copy data into RX Buffer */
    uint8_t rxData = USART_Rx(UART0);
    rxBuf_UART0.data[rxBuf_UART0.wrI] = rxData;
    rxBuf_UART0.wrI = (rxBuf_UART0.wrI + 1) % BUFFERSIZE;
    rxBuf_UART0.pendingBytes++;

    /* Flag Rx overflow */
    if (rxBuf_UART0.pendingBytes > BUFFERSIZE)
    {
    	rxBuf_UART0.overflow = true;
    }

    /* Clear RXDATAV interrupt */
    USART_IntClear(UART0, UART_IF_RXDATAV);
  }
}

/**************************************************************************//**
 * @brief UART0 TX IRQ Handler
 *****************************************************************************/
void UART0_TX_IRQHandler(void)
{
  /* Clear interrupt flags by reading them. */
  USART_IntGet(UART0);

  /* Check TX buffer level status */
  if (UART0->STATUS & UART_STATUS_TXBL)
  {
    if (txBuf_UART0.pendingBytes > 0)
    {
      /* Transmit pending character */
      USART_Tx(UART0, txBuf_UART0.data[txBuf_UART0.rdI]);
      txBuf_UART0.rdI = (txBuf_UART0.rdI + 1) % BUFFERSIZE;
      txBuf_UART0.pendingBytes--;
    }

    /* Disable Tx interrupt if no more bytes in queue */
    if (txBuf_UART0.pendingBytes == 0)
    {
      USART_IntDisable(UART0, UART_IF_TXBL);
    }
  }
}

/**************************************************************************//**
 * @brief UART0 TX IRQ Handler
 *****************************************************************************/
void USART1_RX_IRQHandler(void)
{
  /* Check for RX data valid interrupt */
  if (USART1->STATUS & UART_STATUS_RXDATAV)
  {
    /* Copy data into RX Buffer */
    uint8_t rxData = USART_Rx(USART1);
    rxBuf_USART1.data[rxBuf_USART1.wrI] = rxData;
    rxBuf_USART1.wrI = (rxBuf_USART1.wrI + 1) % BUFFERSIZE;
    rxBuf_USART1.pendingBytes++;

    /* Flag Rx overflow */
    if (rxBuf_USART1.pendingBytes > BUFFERSIZE)
    {
    	rxBuf_USART1.overflow = true;
    }

    /* Clear RXDATAV interrupt */
    USART_IntClear(USART1, UART_IF_RXDATAV);
  }
}

/**************************************************************************//**
 * @brief UART0 TX IRQ Handler
 *****************************************************************************/
void USART1_TX_IRQHandler(void)
{
  /* Clear interrupt flags by reading them. */
  USART_IntGet(USART1);

  /* Check TX buffer level status */
  if (USART1->STATUS & UART_STATUS_TXBL)
  {
    if (txBuf_USART1.pendingBytes > 0)
    {
      /* Transmit pending character */
      USART_Tx(USART1, txBuf_USART1.data[txBuf_USART1.rdI]);
      txBuf_USART1.rdI = (txBuf_USART1.rdI + 1) % BUFFERSIZE;
      txBuf_USART1.pendingBytes--;
    }

    /* Disable Tx interrupt if no more bytes in queue */
    if (txBuf_USART1.pendingBytes == 0)
    {
      USART_IntDisable(USART1, UART_IF_TXBL);
    }
  }
}

void DUTS_initIRQs(USART_TypeDef* uart, IRQn_Type rxIRQn, IRQn_Type txIRQn)
{
  /* Prepare UART Rx and Tx interrupts */
  USART_IntClear(uart, _UART_IF_MASK);
  USART_IntEnable(uart, UART_IF_RXDATAV);
  if (rxIRQn != 0) {
  	NVIC_ClearPendingIRQ(rxIRQn);
  	NVIC_EnableIRQ(rxIRQn);
  }
  if (txIRQn != 0) {
  	NVIC_ClearPendingIRQ(txIRQn);
  	NVIC_EnableIRQ(txIRQn);
  }
}


uint8_t DUTS_getChar(USART_TypeDef* uart)
{
  uint8_t ch;

  data_buffer *rxBuf;

  if (uart == UART0)
      rxBuf = &rxBuf_UART0;
  else if (uart == UART1)
      rxBuf = &rxBuf_UART1;
  else if (uart == USART0)
      rxBuf = &rxBuf_USART0;
  else if (uart == USART1)
      rxBuf = &rxBuf_USART1;
  else if (uart == USART2)
      rxBuf = &rxBuf_USART2;

  /* Check if there is a byte that is ready to be fetched. If no byte is ready, wait for incoming data */
  while (rxBuf->pendingBytes < 1)
  {
    vTaskDelay(pdMS_TO_TICKS(1));
  }

  /* Copy data from buffer */
  ch        = rxBuf->data[rxBuf->rdI];
  rxBuf->rdI = (rxBuf->rdI + 1) % BUFFERSIZE;

  /* Decrement pending byte counter */
  rxBuf->pendingBytes--;

  return ch;
}

/******************************************************************************
 * @brief  uart1PutChar function
 *****************************************************************************/
void DUTS_PutChar(uint8_t ch, USART_TypeDef* uart)
{

  data_buffer *txBuf;

  if (uart == UART0)
  	  txBuf = &txBuf_UART0;
  else if (uart == UART1)
  	  txBuf = &txBuf_UART1;
  else if (uart == USART0)
  	  txBuf = &txBuf_USART0;
  else if (uart == USART1)
  	  txBuf = &txBuf_USART1;
  else if (uart == USART2)
  	  txBuf = &txBuf_USART2;

  /* Check if Tx queue has room for new data */
  while ((txBuf->pendingBytes + 1) > BUFFERSIZE)
  {
    /* Wait until there is room in queue */
    vTaskDelay(pdMS_TO_TICKS(1));
  }

  /* Copy ch into txBuffer */
  txBuf->data[txBuf->wrI] = ch;
  txBuf->wrI             = (txBuf->wrI + 1) % BUFFERSIZE;

  /* Increment pending byte counter */
  txBuf->pendingBytes++;

  /* Enable interrupt on USART TX Buffer*/
  USART_IntEnable(uart, USART_IF_TXBL);
}
