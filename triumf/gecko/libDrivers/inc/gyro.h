/******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
 * File Name          : gyro.h
 * Author             : MSH Application Team
 * Author             : Andrea Labombarda
 * Version            : $Revision:$
 * Date               : $Date:$
 * Description        : Descriptor Header for l3gd20(H) driver file
 *
 * HISTORY:
 * Date        	| 	Modification                                	|	Author
 * 22/03/2011  	| 	Initial Revision                            	|	Andrea Labombarda
 * 07/03/2015	|	Modified to L3GD20H driver for EFM32GG280F1024	|	Brandon Borden
 ********************************************************************************
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
 * AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
 * CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
 * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * THIS SOFTWARE IS SPECIFICALLY DESIGNED FOR EXCLUSIVE USE WITH ST PARTS.
 *
 *******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GYRO_DRIVER__H
#define __GYRO_DRIVER__H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <sharedtypes.h>
/* Exported types ------------------------------------------------------------*/
typedef uint8_t GYRO_Int1PinConf_t;
typedef uint8_t GYRO_Int2PinConf_t;
typedef uint8_t GYRO_Int1Conf_t;
typedef uint8_t GYRO_Axis_t;

// Target specific location information
#define GYRO_CS_PIN	 	5
#define GYRO_CS_PORT	gpioPortB
#define GYRO_SPI		USART1

// Read Period
#define GYRO_READ_DELAY 5

typedef enum {
	GYRO_ODR_12_5Hz_BW_NA = 0x10,
	GYRO_ODR_25Hz_BW_NA = 0x14,
	GYRO_ODR_50Hz_BW_16_6 = 0x18,
	GYRO_ODR_100Hz_BW_12_5 = 0x00,
	GYRO_ODR_100Hz_BW_25 = 0x01,
	GYRO_ODR_200Hz_BW_12_5 = 0x04,
	GYRO_ODR_200Hz = 0x05,
	GYRO_ODR_200Hz_BW_70 = 0x07,
	GYRO_ODR_400Hz_BW_20 = 0x08,
	GYRO_ODR_400Hz_BW_25 = 0x09,
	GYRO_ODR_400Hz_BW_50 = 0x0A,
	GYRO_ODR_400Hz_BW_110 = 0x0B,
	GYRO_ODR_800Hz_BW_30 = 0x0C,
	GYRO_ODR_800Hz_BW_35 = 0x0D,
	GYRO_ODR_800Hz = 0x0E,
	GYRO_ODR_800Hz_BW_100 = 0x0F,
} GYRO_ODR_t;

typedef enum {
	GYRO_POWER_DOWN = 0x00, GYRO_SLEEP = 0x01, GYRO_NORMAL = 0x02
} GYRO_Mode_t;

typedef enum {
	GYRO_HPM_NORMAL_MODE_RES = 0x00,
	GYRO_HPM_REF_SIGNAL = 0x01,
	GYRO_HPM_NORMAL_MODE = 0x02,
	GYRO_HPM_AUTORESET_INT = 0x03
} GYRO_HPFMode_t;

typedef enum {
	GYRO_HPFCF_0 = 0x00,
	GYRO_HPFCF_1 = 0x01,
	GYRO_HPFCF_2 = 0x02,
	GYRO_HPFCF_3 = 0x03,
	GYRO_HPFCF_4 = 0x04,
	GYRO_HPFCF_5 = 0x05,
	GYRO_HPFCF_6 = 0x06,
	GYRO_HPFCF_7 = 0x07,
	GYRO_HPFCF_8 = 0x08,
	GYRO_HPFCF_9 = 0x09
} GYRO_HPFCutOffFreq_t;

typedef enum {
	GYRO_PUSH_PULL = 0x00, GYRO_OPEN_DRAIN = 0x01
} GYRO_IntPinMode_t;

typedef enum {
	GYRO_FULLSCALE_250 = 0x00,
	GYRO_FULLSCALE_500 = 0x01,
	GYRO_FULLSCALE_2000 = 0x02
} GYRO_Fullscale_t;

typedef enum {
	GYRO_BLE_LSB = 0x00, GYRO_BLE_MSB = 0x01
} GYRO_Endianess_t;

typedef enum {
	GYRO_SPI_4_WIRE = 0x00, GYRO_SPI_3_WIRE = 0x01
} GYRO_SPIMode_t;

typedef enum {
	GYRO_FIFO_DISABLE = 0x05,
	GYRO_FIFO_BYPASS_MODE = 0x00,
	GYRO_FIFO_MODE = 0x01,
	GYRO_FIFO_STREAM_MODE = 0x02,
	GYRO_FIFO_STREAM_TO_FIFO_MODE = 0x03,
	GYRO_FIFO_BYPASS_TO_STREAM_MODE = 0x04
} GYRO_FifoMode_t;

typedef enum {
	GYRO_NONE = 0x00, GYRO_HPF = 0x01, GYRO_LPF2 = 0x02, GYRO_HPFLPF2 = 0x03
} GYRO_HPF_LPF2_Enable;

typedef enum {
	GYRO_THS_X = 0x00, GYRO_THS_Y = 0x01, GYRO_THS_Z = 0x02
} GYRO_IntThsAxis;

/* Exported macro ------------------------------------------------------------*/

#ifndef __SHARED__MACROS

#define __SHARED__MACROS
#define ValBit(VAR,Place)         (VAR & (1<<Place))
#define BIT(x) ( (x) )

#endif /*__SHARED__MACROS*/

/* Exported constants --------------------------------------------------------*/

#ifndef __SHARED__CONSTANTS
#define __SHARED__CONSTANTS

#define MEMS_SET                                        0x01
#define MEMS_RESET                                      0x00

#endif /*__SHARED__CONSTANTS*/

/**************CONTROL REGISTERS*****************/

#define GYRO_MEMS_I2C_ADDRESS         0xD6

/***************CTRL1***************/
#define GYRO_CTRL1				0x20
#define GYRO_ODR_BIT                BIT(4)
#define GYRO_PD						BIT(3)
#define GYRO_ZEN					BIT(2)
#define GYRO_YEN					BIT(1)
#define GYRO_XEN					BIT(0)
#define GYRO_X_ENABLE                                 0x02
#define GYRO_Y_ENABLE                                 0x01
#define GYRO_Z_ENABLE                                 0x04

/***************CTRL2***************/
#define GYRO_CTRL2				0x21
#define GYRO_EXTREN					BIT(7)
#define GYRO_LVLEN					BIT(6)
#define GYRO_HPM					BIT(4)
#define GYRO_HPFC3					BIT(3)
#define GYRO_HPFC2					BIT(2)
#define GYRO_HPFC1					BIT(1)
#define GYRO_HPFC0					BIT(0)

/***************CTRL3***************/
#define GYRO_CTRL3				0x22
#define GYRO_I1_IG					BIT(7)
#define GYRO_I1_BOOT				BIT(6)
#define GYRO_H_LACTIVE				BIT(5)
#define GYRO_PP_OD					BIT(4)
#define GYRO_I2_DRDY				BIT(3)
#define GYRO_I2_WTM					BIT(2)
#define GYRO_I2_ORUN				BIT(1)
#define GYRO_I2_EMPTY				BIT(0)
#define GYRO_I1_ON_PIN_INT1_ENABLE                   0x80
#define GYRO_I1_ON_PIN_INT1_DISABLE                  0x00
#define GYRO_I1_BOOT_ON_INT1_ENABLE                  0x40
#define GYRO_I1_BOOT_ON_INT1_DISABLE                 0x00
#define GYRO_INT1_ACTIVE_HIGH                        0x00
#define GYRO_INT1_ACTIVE_LOW                         0x20
#define GYRO_I2_DRDY_ON_INT2_ENABLE                  0x08
#define GYRO_I2_DRDY_ON_INT2_DISABLE                 0x00
#define GYRO_WTM_ON_INT2_ENABLE                      0x04
#define GYRO_WTM_ON_INT2_DISABLE                     0x00
#define GYRO_OVERRUN_ON_INT2_ENABLE                  0x02
#define GYRO_OVERRUN_ON_INT2_DISABLE                 0x00
#define GYRO_EMPTY_ON_INT2_ENABLE                    0x01
#define GYRO_EMPTY_ON_INT2_DISABLE                   0x00

/***************CTRL4***************/
#define GYRO_CTRL4				0x23
#define GYRO_BDU					BIT(7)
#define GYRO_BLE					BIT(6)
#define GYRO_FS						BIT(4)
#define GYRO_IMPEN					BIT(3)
#define GYRO_ST						BIT(1)
#define GYRO_SIM					BIT(0)

/***************CTRL5***************/
#define GYRO_CTRL5				0x24
#define GYRO_FIFO_EN                BIT(6)
#define GYRO_STOPONFTH				BIT(5)
#define GYRO_HPEN                   BIT(4)
#define GYRO_IG_SEL1                BIT(3)
#define GYRO_IG_SEL0                BIT(2)
#define GYRO_OUT_SEL1               BIT(1)
#define GYRO_OUT_SEL0               BIT(0)

/**************GYROSCOPE INTERRUPT REGISTERS***************/
#define GYRO_IG_CFG					0x30
#define GYRO_IG_SRC					0x31
#define GYRO_IG_THS_XH				0x32
#define GYRO_IG_THS_XL				0x33
#define GYRO_IG_THS_YH				0x34
#define GYRO_IG_THS_YL				0x35
#define GYRO_IG_THS_ZH				0x36
#define GYRO_IG_THS_ZL				0x37
#define GYRO_IG_DURATION			0x38
#define GYRO_LIR                    BIT(6)
#define GYRO_ANDOR                  BIT(7)
#define GYRO_ZHIE                   BIT(5)
#define GYRO_ZLIE                  	BIT(4)
#define GYRO_YHIE                   BIT(3)
#define GYRO_YLIE                   BIT(2)
#define GYRO_XHIE                   BIT(1)
#define GYRO_XLIE                   BIT(0)
#define GYRO_IG_AND                                0x80
#define GYRO_IG_OR                                 0x00
#define GYRO_IG_LIR_ENABLE                         0x40
#define GYRO_IG_LIR_DISABLE                        0x00
#define GYRO_IG_ZHIE_ENABLE                        0x20
#define GYRO_IG_ZHIE_DISABLE                       0x00
#define GYRO_IG_ZLIE_ENABLE                        0x10
#define GYRO_IG_ZLIE_DISABLE                       0x00
#define GYRO_IG_YHIE_ENABLE                        0x08
#define GYRO_IG_YHIE_DISABLE                       0x00
#define GYRO_IG_YLIE_ENABLE                        0x04
#define GYRO_IG_YLIE_DISABLE                       0x00
#define GYRO_IG_XHIE_ENABLE                        0x02
#define GYRO_IG_XHIE_DISABLE                       0x00
#define GYRO_IG_XLIE_ENABLE                        0x01
#define GYRO_IG_XLIE_DISABLE                       0x00

/***************LOW_ODR***************/
#define GYRO_LOW_ODR_REG		0x39
#define GYRO_DRDY_HL                BIT(5)
#define GYRO_I2C_DIS				BIT(3)
#define GYRO_LOW_ODR                BIT(0)

/**********GYROSCOPE: STATUS AND OUTPUT REGISTERS***********/
//OUTPUT REGISTER
#define GYRO_OUT_X_L					0x28
#define GYRO_OUT_X_H					0x29
#define GYRO_OUT_Y_L					0x2A
#define GYRO_OUT_Y_H					0x2B
#define GYRO_OUT_Z_L					0x2C
#define GYRO_OUT_Z_H					0x2D
#define GYRO_OUT_TEMP					0x26
#define GYRO_STATUS                              0x27
#define GYRO_STATUS_ZYXOR                        0x07    // 1	:	new data set has over written the previous one
// 0	:	no overrun has occurred (default)
#define GYRO_STATUS_ZOR                          0x06    // 0	:	no overrun has occurred (default)
// 1	:	new Z-axis data has over written the previous one
#define GYRO_STATUS_YOR                          0x05    // 0	:	no overrun has occurred (default)
// 1	:	new Y-axis data has over written the previous one
#define GYRO_STATUS_XOR                          0x04    // 0	:	no overrun has occurred (default)
// 1	:	new X-axis data has over written the previous one
#define GYRO_STATUS_ZYXDA                        0x03    // 0	:	a new set of data is not yet avvious one
// 1	:	a new set of data is available
#define GYRO_STATUS_ZDA                          0x02    // 0	:	a new data for the Z-Axis is not availvious one
// 1	:	a new data for the Z-Axis is available
#define GYRO_STATUS_YDA                          0x01    // 0	:	a new data for the Y-Axis is not available
// 1	:	a new data for the Y-Axis is available
#define STATUS_XDA                         			0x00    // 0	:	a new data for the X-Axis is not available
#define GYRO_DATAREADY_BIT                           GYRO_STATUS_ZYXDA

#define GYRO_I_AM_L3GD20H			        	 0x0F
#define GYRO_WHOIAM_VALUE					 0xD7

/*************GYROSCOPE FIFO CONTROL REGISTER**************/
#define GYRO_FM0                                      BIT(5)
#define GYRO_FIFO_CTRL                            0x2E
#define GYRO_FIFO_SRC			        0x2F

/* Exported functions --------------------------------------------------------*/
/**********Sensor Configuration Functions***********/
status_t GYRO_SetODR(GYRO_ODR_t ov);
status_t GYRO_SetMode(GYRO_Mode_t md);
status_t GYRO_SetAxis(GYRO_Axis_t axis);
status_t GYRO_SetFullScale(GYRO_Fullscale_t fs);
status_t GYRO_SetBDU(State_t bdu);
status_t GYRO_SetBLE(GYRO_Endianess_t ble);
status_t GYRO_SetSPIInterface(GYRO_SPIMode_t spi);

/***************Filtering Functions****************/
status_t GYRO_SetHPFMode(GYRO_HPFMode_t hpf);
status_t GYRO_SetHPFCutOFF(GYRO_HPFCutOffFreq_t hpf);
status_t GYRO_HPFEnable(State_t hpf);
status_t GYRO_SetOutputDataAndFifoFilters(GYRO_HPF_LPF2_Enable hpf);
status_t GYRO_SetInt1Filters(GYRO_HPF_LPF2_Enable hpf);

/***************Interrupt Functions****************/
status_t GYRO_SetIntPinMode(GYRO_IntPinMode_t pm);
status_t GYRO_SetInt1Pin(GYRO_Int1PinConf_t pinConf);
status_t GYRO_SetInt2Pin(GYRO_Int2PinConf_t pinConf);
status_t GYRO_Int1LatchEnable(State_t latch);
status_t GYRO_ResetInt1Latch(void);
status_t GYRO_SetIntConfiguration(GYRO_Int1Conf_t ic);
status_t GYRO_SetInt1Threshold(GYRO_IntThsAxis axis, uint16_t ths);
status_t GYRO_SetInt1Duration(GYRO_Int1Conf_t id);

/*****************FIFO Functions******************/
status_t GYRO_FIFOModeEnable(GYRO_FifoMode_t fm);
status_t GYRO_SetWaterMark(uint8_t wtm);

/****************Reading Functions*****************/
status_t GYRO_GetSatusReg(uint8_t* buff);
status_t GYRO_GetAngRateRaw(AxesRaw_t* buff);
status_t GYRO_GetFifoSourceReg(uint8_t* buff);
status_t GYRO_GetInt1Src(uint8_t* buff);

/****************Testing Functions****************/
status_t GYRO_SetSelfTest(State_t setst);

/*********************Generic*********************/
uint8_t GYRO_ReadReg(uint8_t Reg, uint8_t* Data);
uint8_t GYRO_WriteReg(uint8_t WriteAddr, uint8_t Data);

#endif /* __GYRO_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

