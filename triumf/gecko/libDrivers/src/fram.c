/**
 * @file fram.c
 * @author Brandon Borden
 * @date 2015-03-13
 */

/* Includes ------------------------------------------------------------------*/
#include "fram.h"
#include "em_usart.h"
#include "em_gpio.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
FRAM_Mode_t FRAM_Mode = FRAM_NORMAL;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
 * Function Name  : FRAM_SetWriteEnableLatch
 * Description    : Allows the issuing of subsequent opcodes for write
 * 				  : instructions.  Must be issued before any write operation
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_SetWriteEnableLatch(void) {
	FRAM_SetSleepMode(FRAM_NORMAL); // Ensure FRAM not in sleep mode

	GPIO->P[FRAM_CS_PORT].DOUTCLR = 1 << FRAM_CS_PIN; // Set CS low

	USART_SpiTransfer(FRAM_SPI, FRAM_OP_WREN);

	GPIO->P[FRAM_CS_PORT].DOUTSET = 1 << FRAM_CS_PIN; // Set CS high
}

/*******************************************************************************
 * Function Name  : FRAM_ResetWriteEnableLatch
 * Description    : Disables all activity by clearing the write enable latch
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_ResetWriteEnableLatch(void) {
	FRAM_SetSleepMode(FRAM_NORMAL); // Ensure FRAM not in sleep mode

	GPIO->P[FRAM_CS_PORT].DOUTCLR = 1 << FRAM_CS_PIN; // Set CS low

	USART_SpiTransfer(FRAM_SPI, FRAM_OP_WRDI);

	GPIO->P[FRAM_CS_PORT].DOUTSET = 1 << FRAM_CS_PIN; // Set CS high
}

/*******************************************************************************
 * Function Name  : FRAM_ReadStatusReg
 * Description    : Provides information about the current state of the
 *				  : write-protection features
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_ReadStatusReg(uint8_t* data) {
	GPIO->P[FRAM_CS_PORT].DOUTCLR = 1 << FRAM_CS_PIN; // Set CS low

	USART_SpiTransfer(FRAM_SPI, FRAM_OP_RDSR);
	* data = USART_SpiTransfer(FRAM_SPI, 0x00);

	GPIO->P[FRAM_CS_PORT].DOUTSET = 1 << FRAM_CS_PIN; // Set CS high
}

/*******************************************************************************
 * Function Name  : FRAM_ReadStatusReg
 * Description    : Write into the status register and change the write protect
 * 				  : configuration
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_WriteStatusReg(uint8_t data) {
	FRAM_SetSleepMode(FRAM_NORMAL); // Ensure FRAM not in sleep mode

	FRAM_ResetWriteEnableLatch(); // Allow writing
	GPIO->P[FRAM_WP_PORT].DOUTSET = 1 << FRAM_WP_PIN; // Set #WP high
	GPIO->P[FRAM_CS_PORT].DOUTCLR = 1 << FRAM_CS_PIN; // Set CS low

	USART_SpiTransfer(FRAM_SPI, FRAM_OP_WRSR);
	USART_SpiTransfer(FRAM_SPI, data);

	GPIO->P[FRAM_CS_PORT].DOUTSET = 1 << FRAM_CS_PIN; // Set CS high
	GPIO->P[FRAM_WP_PORT].DOUTCLR = 1 << FRAM_WP_PIN; // Set #WP low
	FRAM_SetWriteEnableLatch();
}

/*******************************************************************************
 * Function Name  : FRAM_ReadStatusReg
 * Description    : Read memory from the FRAM.
 * Input          : Address (18-bit) of the first byte of the read operation,
 * 				  : upper 6 bytes are ignored
 * Output         : Memory data
 * Return         : None
 *******************************************************************************/
void FRAM_ReadMemory(uint32_t address, uint8_t* data) {
	FRAM_SetSleepMode(FRAM_NORMAL); // Ensure FRAM not in sleep mode

	GPIO->P[FRAM_CS_PORT].DOUTCLR = 1 << FRAM_CS_PIN; // Set CS low

	USART_SpiTransfer(FRAM_SPI, FRAM_OP_READ);

	/* Send address bits 17 - 0. Bits 23- 18 are don't care */
	USART_SpiTransfer(FRAM_SPI, (uint8_t) (address >> 16));
	USART_SpiTransfer(FRAM_SPI, (uint8_t) (address >> 8));
	USART_SpiTransfer(FRAM_SPI, (uint8_t) address);

	* data = USART_SpiTransfer(FRAM_SPI, 0x00);

	GPIO->P[FRAM_CS_PORT].DOUTSET = 1 << FRAM_CS_PIN; // Set CS high
}

/*******************************************************************************
 * Function Name  : FRAM_WriteMemory
 * Description    : Write data into the FRAMs memory
 * Input          : Address (18-bit) of the first byte of the write operation,
 * 				  : upper 6 bytes are ignored
 * 				  : Data to be written
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_WriteMemory(uint32_t address, uint8_t data) {
	FRAM_SetSleepMode(FRAM_NORMAL); // Ensure FRAM not in sleep mode

	FRAM_ResetWriteEnableLatch(); // Allow writing

	GPIO->P[FRAM_CS_PORT].DOUTCLR = 1 << FRAM_CS_PIN; // Set CS low

	USART_SpiTransfer(FRAM_SPI, FRAM_OP_WRITE);

	/* Send address bits 17 - 0. Bits 23- 18 are don't care */
	USART_SpiTransfer(FRAM_SPI, (uint8_t) (address >> 16));
	USART_SpiTransfer(FRAM_SPI, (uint8_t) (address >> 8));
	USART_SpiTransfer(FRAM_SPI, (uint8_t) address);

	USART_SpiTransfer(FRAM_SPI, data);

	GPIO->P[FRAM_CS_PORT].DOUTSET = 1 << FRAM_CS_PIN; // Set CS high

	FRAM_SetWriteEnableLatch();
}

/*******************************************************************************
 * Function Name  : FRAM_EnterSleepMode
 * Description    : Puts the FRAM into a low-power sleep mode or normal mode
 * Input          : FRAM_NORMAL | FRAM_SLEEP
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_SetSleepMode(FRAM_Mode_t mode) {
	switch (mode) {

	case FRAM_SLEEP:
		if (FRAM_Mode == FRAM_NORMAL)
		{
			GPIO->P[FRAM_CS_PORT].DOUTCLR = 1 << FRAM_CS_PIN; // Set CS low
			USART_SpiTransfer(FRAM_SPI, FRAM_OP_SLEEP);
			GPIO->P[FRAM_CS_PORT].DOUTSET = 1 << FRAM_CS_PIN; // Set CS high
		}
		break;

	case FRAM_NORMAL:
		if (FRAM_Mode == FRAM_SLEEP)
		{
			uint8_t value;
			FRAM_ReadStatusReg(&value); // Do a dummy read to wake up the FRAM
			//TODO: make delay of at least 8ns
		}
		break;

		//TODO: return error if otherwise?
	}

	FRAM_Mode = mode;

}

/*******************************************************************************
 * Function Name  : FRAM_SetBlockProtectRange
 * Description    : Set the range for the write protected block in FRAM
 * Input          : FRAM_NONE | FRAM_00000_TO_3FFFF | FRAM_20000_TO_3FFFF |
 * 				  : FRAM_30000_TO_3FFFF
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_SetBlockProtectRange(FRAM_BlkProtectRange_t blockRange) {
	FRAM_SetSleepMode(FRAM_NORMAL); // Ensure FRAM not in sleep mode

	uint8_t value;
	FRAM_ReadStatusReg(&value);

	value &= 0xF3;	// Clear block protect bits
	value |= blockRange << FRAM_BLK_PROTECT; // Set new block protect range bits

	FRAM_WriteStatusReg(value);
}

/*******************************************************************************
 * Function Name  : FRAM_SetWriteProtectEnableMode
 * Description    : Enable or disable the write protect pin control.  Write
 * 				  : protect (#wp) disables writing to the status register when
 * 				  :	low
 * Input          : MEMS_ENABLE | MEMS_DISABLE
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_WriteProtectEnable(State_t mode) {
	FRAM_SetSleepMode(FRAM_NORMAL); // Ensure FRAM not in sleep mode

	uint8_t value;
	FRAM_ReadStatusReg(&value);

	value &= 0x7F;	// Clear write protect bit
	value |= mode << FRAM_WPEN; // Set new write protect bit

	FRAM_WriteStatusReg(value);
}
