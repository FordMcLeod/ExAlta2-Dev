/***************************************************************************//**
 * @file print.c
 * @brief 
 * @author Stefan Damkjar
 * @version 
 ******************************************************************************/

#include "print.h"
#include "em_usart.h"


/***************************************************************************//**
 * @brief Must be null terminated.
 ******************************************************************************/
void printStringln(USART_TypeDef* uart, char* data)
{
  int i = 0;
  for(i = 0;data[i]!='\0';i++){
    USART_Tx(uart,data[i]);
  }
  USART_Tx(uart,'\n');
  USART_Tx(uart,'\r');
  USART_Tx(uart,'\0');
}


/***************************************************************************//**
 * @brief Must be null terminated.
 ******************************************************************************/
void printString(USART_TypeDef* uart, char* data)
{
  int i = 0;
  for(i = 0;data[i]!='\0';i++){
    USART_Tx(uart,data[i]);
  }
  USART_Tx(uart,'\0');
}


/***************************************************************************//**
 * @brief
 ******************************************************************************/
void printChar(USART_TypeDef* uart, char data)
{
  USART_Tx(uart,data);
  USART_Tx(uart,'\0');
}


/***************************************************************************//**
 * @brief
 ******************************************************************************/
void println(USART_TypeDef* uart, char* data,  uint8_t len)
{
  int i = 0;
  for(i = 0;i < len;i++){
    USART_Tx(uart,data[i]);
  }
  USART_Tx(uart,'\n');
  USART_Tx(uart,'\r');
  USART_Tx(uart,'\0');
}


/***************************************************************************//**
 * @brief
 ******************************************************************************/
void print(USART_TypeDef* uart, char* data, uint8_t len)
{
  int i = 0;
  for(i = 0;i < len;i++){
    USART_Tx(uart,data[i]);
  }
  USART_Tx(uart,'\0');
}
