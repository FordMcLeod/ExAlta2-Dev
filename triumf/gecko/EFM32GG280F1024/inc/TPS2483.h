#ifndef __TPS2483_H
#define __TPS2483_H

#include "em_device.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

/** I2C device address for temperature sensor on DVK */
#define TPS2483_ADDR0      0x8A
#define TPS2483_ADDR1      0x9E
#define TPS2483_ADDR2      0x9A
#define TPS2483_ADDR3      0x80

#define TPS2483_CONFIG_MODE 			(0x7UL << 0)
#define _TPS2483_CONFIG_MODE_SHIFT 		0
#define _TPS2483_CONFIG_MODE_MASK 		0x7UL
#define _TPS2483_CONFIG_MODE_DEFAULT 	0x7UL
#define _TPS2483_CONFIG_MODE_POWERDOWN1 0x0UL
#define _TPS2483_CONFIG_MODE_SVTRIG	  	0x1UL
#define _TPS2483_CONFIG_MODE_BVTRIG  	0x2UL
#define _TPS2483_CONFIG_MODE_SBTRIG  	0x3UL
#define _TPS2483_CONFIG_MODE_POWERDOWN2 0x4UL
#define _TPS2483_CONFIG_MODE_SVCONT  	0x5UL
#define _TPS2483_CONFIG_MODE_BVCONT  	0x6UL
#define _TPS2483_CONFIG_MODE_SBCONT  	0x7UL
#define TPS2483_CONFIG_MODE_DEFAULT 	(_TPS2483_CONFIG_MODE_DEFAULT << 0)
#define TPS2483_CONFIG_MODE_POWERDOWN1  (_TPS2483_CONFIG_MODE_POWERDOWN1 << 0)
#define TPS2483_CONFIG_MODE_SVTRIG	  	(_TPS2483_CONFIG_MODE_SVTRIG << 0)
#define TPS2483_CONFIG_MODE_BVTRIG  	(_TPS2483_CONFIG_MODE_BVTRIG << 0)
#define TPS2483_CONFIG_MODE_SBTRIG  	(_TPS2483_CONFIG_MODE_SBTRIG << 0)
#define TPS2483_CONFIG_MODE_POWERDOWN2  (_TPS2483_CONFIG_MODE_POWERDOWN2 << 0)
#define TPS2483_CONFIG_MODE_SVCONT  	(_TPS2483_CONFIG_MODE_SVCONT << 0)
#define TPS2483_CONFIG_MODE_BVCONT  	(_TPS2483_CONFIG_MODE_BVCONT << 0)
#define TPS2483_CONFIG_MODE_SBCONT  	(_TPS2483_CONFIG_MODE_SBCONT << 0)
#define TPS2483_CONFIG_VSHCT			(0x7UL << 3)
#define _TPS2483_CONFIG_VSHCT_SHIFT		3
#define _TPS2483_CONFIG_VSHCT_MASK		0x38UL
#define _TPS2483_CONFIG_VSHCT_DEFAULT	0x5UL
#define _TPS2483_CONFIG_VSHCT_140US		0x0UL
#define _TPS2483_CONFIG_VSHCT_204US		0x1UL
#define _TPS2483_CONFIG_VSHCT_332US		0x2UL
#define _TPS2483_CONFIG_VSHCT_588US		0x3UL
#define _TPS2483_CONFIG_VSHCT_1100US	0x4UL
#define _TPS2483_CONFIG_VSHCT_2116US	0x5UL
#define _TPS2483_CONFIG_VSHCT_4156US	0x6UL
#define _TPS2483_CONFIG_VSHCT_8244US	0x7UL
#define TPS2483_CONFIG_VSHCT_DEFAULT	(_TPS2483_CONFIG_VSHCT_DEFAULT << 3)
#define TPS2483_CONFIG_VSHCT_140US		(_TPS2483_CONFIG_VSHCT_140US << 3)
#define TPS2483_CONFIG_VSHCT_204US		(_TPS2483_CONFIG_VSHCT_204US << 3)
#define TPS2483_CONFIG_VSHCT_332US		(_TPS2483_CONFIG_VSHCT_332US << 3)
#define TPS2483_CONFIG_VSHCT_588US		(_TPS2483_CONFIG_VSHCT_588US << 3)
#define TPS2483_CONFIG_VSHCT_1100US		(_TPS2483_CONFIG_VSHCT_1100US << 3)
#define TPS2483_CONFIG_VSHCT_2116US		(_TPS2483_CONFIG_VSHCT_2116US << 3)
#define TPS2483_CONFIG_VSHCT_4156US		(_TPS2483_CONFIG_VSHCT_4156US << 3)
#define TPS2483_CONFIG_VSHCT_8244US		(_TPS2483_CONFIG_VSHCT_8244US << 3)
#define TPS2483_CONFIG_VBUSCT 			(0x7UL << 6)
#define _TPS2483_CONFIG_VBUSCT_SHIFT	6
#define _TPS2483_CONFIG_VBUSCT_MASK		0x700UL
#define _TPS2483_CONFIG_VBUSCT_DEFAULT	0x5UL
#define _TPS2483_CONFIG_VBUSCT_140US	0x0UL
#define _TPS2483_CONFIG_VBUSCT_204US	0x1UL
#define _TPS2483_CONFIG_VBUSCT_332US	0x2UL
#define _TPS2483_CONFIG_VBUSCT_588US	0x3UL
#define _TPS2483_CONFIG_VBUSCT_1100US	0x4UL
#define _TPS2483_CONFIG_VBUSCT_2116US	0x5UL
#define _TPS2483_CONFIG_VBUSCT_4156US	0x6UL
#define _TPS2483_CONFIG_VBUSCT_8244US	0x7UL
#define TPS2483_CONFIG_VBUSCT_DEFAULT	(_TPS2483_CONFIG_VBUSCT_DEFAULT << 6)
#define TPS2483_CONFIG_VBUSCT_140US		(_TPS2483_CONFIG_VBUSCT_140US << 6)
#define TPS2483_CONFIG_VBUSCT_204US		(_TPS2483_CONFIG_VBUSCT_204US << 6)
#define TPS2483_CONFIG_VBUSCT_332US		(_TPS2483_CONFIG_VBUSCT_332US << 6)
#define TPS2483_CONFIG_VBUSCT_588US		(_TPS2483_CONFIG_VBUSCT_588US << 6)
#define TPS2483_CONFIG_VBUSCT_1100US	(_TPS2483_CONFIG_VBUSCT_1100US << 6)
#define TPS2483_CONFIG_VBUSCT_2116US	(_TPS2483_CONFIG_VBUSCT_2116US << 6)
#define TPS2483_CONFIG_VBUSCT_4156US	(_TPS2483_CONFIG_VBUSCT_4156US << 6)
#define TPS2483_CONFIG_VBUSCT_8244US	(_TPS2483_CONFIG_VBUSCT_8244US << 6)
#define TPS2483_CONFIG_AVG    			(0x7UL << 9)
#define _TPS2483_CONFIG_AVG_SHIFT		9
#define _TPS2483_CONFIG_AVG_MASK		0xE00UL
#define _TPS2483_CONFIG_AVG_DEFAULT		0x0UL
#define _TPS2483_CONFIG_AVG_1SAMPLE     0x0UL
#define _TPS2483_CONFIG_AVG_4SAMPLE     0x1UL
#define _TPS2483_CONFIG_AVG_16SAMPLE    0x2UL
#define _TPS2483_CONFIG_AVG_64SAMPLES   0x3UL
#define _TPS2483_CONFIG_AVG_128SAMPLES  0x4UL
#define _TPS2483_CONFIG_AVG_256SAMPLES  0x5UL
#define _TPS2483_CONFIG_AVG_512SAMPLES  0x6UL
#define _TPS2483_CONFIG_AVG_1024SAMPLES 0x7UL
#define TPS2483_CONFIG_AVG_DEFAULT		(_TPS2483_CONFIG_AVG_DEFAULT << 9)
#define TPS2483_CONFIG_AVG_1SAMPLE      (_TPS2483_CONFIG_AVG_1SAMPLE << 9)
#define TPS2483_CONFIG_AVG_4SAMPLE      (_TPS2483_CONFIG_AVG_4SAMPLE << 9)
#define TPS2483_CONFIG_AVG_16SAMPLE     (_TPS2483_CONFIG_AVG_16SAMPLE << 9)
#define TPS2483_CONFIG_AVG_64SAMPLES    (_TPS2483_CONFIG_AVG_64SAMPLES << 9)
#define TPS2483_CONFIG_AVG_128SAMPLES   (_TPS2483_CONFIG_AVG_128SAMPLES << 9)
#define TPS2483_CONFIG_AVG_256SAMPLES   (_TPS2483_CONFIG_AVG_256SAMPLES << 9)
#define TPS2483_CONFIG_AVG_512SAMPLES   (_TPS2483_CONFIG_AVG_512SAMPLES << 9)
#define TPS2483_CONFIG_AVG_1024SAMPLES  (_TPS2483_CONFIG_AVG_1024SAMPLES << 9)
#define TPS2483_CONFIG_RST    			(0x1UL << 15)
#define _TPS2483_CONFIG_RST_SHIFT		15
#define _TPS2483_CONFIG_RST_MASK		0x8000

#define TPS2483_MASKEN_LEN				(0x1UL << 0)
#define _TPS2483_MASKEN_LEN_SHIFT		0
#define _TPS2483_MASKEN_LEN_MASK		0x1UL
#define _TPS2483_MASKEN_LEN_DEFAULT		0x0UL
#define TPS2483_MASKEN_LEN_DEFAULT 		(_TPS2483_MASKEN_LEN_DEFAULT << 0)
#define TPS2483_MASKEN_APOL				(0x1UL << 1)
#define _TPS2483_MASKEN_APOL_SHIFT		1
#define _TPS2483_MASKEN_APOL_MASK		0x2UL
#define _TPS2483_MASKEN_APOL_DEFAULT	0x0UL
#define TPS2483_MASKEN_APOL_DEFAULT 	(_TPS2483_MASKEN_APOL_DEFAULT << 0)
#define TPS2483_MASKEN_OVF				(0x1UL << 2)
#define _TPS2483_MASKEN_OVF_SHIFT		2
#define _TPS2483_MASKEN_OVF_MASK		0x4UL
#define _TPS2483_MASKEN_OVF_DEFAULT		0x0UL
#define TPS2483_MASKEN_OVF_DEFAULT 		(_TPS2483_MASKEN_OVF_DEFAULT << 0)
#define TPS2483_MASKEN_CVRF				(0x1UL << 3)
#define _TPS2483_MASKEN_CVRF_SHIFT		3
#define _TPS2483_MASKEN_CVRF_MASK		0x8UL
#define _TPS2483_MASKEN_CVRF_DEFAULT	0x0UL
#define TPS2483_MASKEN_CVRF_DEFAULT 	(_TPS2483_MASKEN_CVRF_DEFAULT << 0)
#define TPS2483_MASKEN_AFF				(0x1UL << 4)
#define _TPS2483_MASKEN_AFF_SHIFT		4
#define _TPS2483_MASKEN_AFF_MASK		0x20UL
#define _TPS2483_MASKEN_AFF_DEFAULT		0x0UL
#define TPS2483_MASKEN_AFF_DEFAULT 		(_TPS2483_MASKEN_AFF_DEFAULT << 0)
#define TPS2483_MASKEN_CNVR				(0x1UL << 10)
#define _TPS2483_MASKEN_CNVR_SHIFT		10
#define _TPS2483_MASKEN_CNVR_MASK		0x400UL
#define _TPS2483_MASKEN_CNVR_DEFAULT	0x0UL
#define TPS2483_MASKEN_CNVR_DEFAULT 	(_TPS2483_MASKEN_CNVR_DEFAULT << 0)
#define TPS2483_MASKEN_POL				(0x1UL << 11)
#define _TPS2483_MASKEN_POL_SHIFT		11
#define _TPS2483_MASKEN_POL_MASK		0x800UL
#define _TPS2483_MASKEN_POL_DEFAULT		0x0UL
#define TPS2483_MASKEN_POL_DEFAULT 		(_TPS2483_MASKEN_POL_DEFAULT << 0)
#define TPS2483_MASKEN_BUL				(0x1UL << 12)
#define _TPS2483_MASKEN_BUL_SHIFT		12
#define _TPS2483_MASKEN_BUL_MASK		0x1000UL
#define _TPS2483_MASKEN_BUL_DEFAULT		0x0UL
#define TPS2483_MASKEN_BUL_DEFAULT 		(_TPS2483_MASKEN_BUL_DEFAULT << 0)
#define TPS2483_MASKEN_BOL				(0x1UL << 13)
#define _TPS2483_MASKEN_BOL_SHIFT		13
#define _TPS2483_MASKEN_BOL_MASK		0x2000UL
#define _TPS2483_MASKEN_BOL_DEFAULT		0x0UL
#define TPS2483_MASKEN_BOL_DEFAULT 		(_TPS2483_MASKEN_BOL_DEFAULT << 0)
#define TPS2483_MASKEN_SUL				(0x1UL << 14)
#define _TPS2483_MASKEN_SUL_SHIFT		14
#define _TPS2483_MASKEN_SUL_MASK		0x4000UL
#define _TPS2483_MASKEN_SUL_DEFAULT		0x0UL
#define TPS2483_MASKEN_SUL_DEFAULT 		(_TPS2483_MASKEN_SUL_DEFAULT << 0)
#define TPS2483_MASKEN_SOL				(0x1UL << 15)
#define _TPS2483_MASKEN_SOL_SHIFT		15
#define _TPS2483_MASKEN_SOL_MASK		0x8000UL
#define _TPS2483_MASKEN_SOL_DEFAULT		0x0UL
#define TPS2483_MASKEN_SOL_DEFAULT 		(_TPS2483_MASKEN_SOL_DEFAULT << 0)

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

typedef enum
{
  TPS2483_RegConfig 		=   0,  /**< Configuration register */
  TPS2483_RegShuntV 		=   1,  /**< Shunt voltage register (read-only) */
  TPS2483_RegBusV 			= 	2,  /**< Bus voltage register (read-only) */
  TPS2483_RegPower 			=	3,  /**< Power register (read-only) */
  TPS2483_RegCurr 			= 	4,	/**< Current register (read-only) */
  TPS2483_RegCalib 			= 	5,	/**< Calibration register */
  TPS2483_RegMaskEn 		= 	6,	/**< Mask/Enable register */
  TPS2483_RegAlertLim 		= 	7 	/**< Alert limit register */
} TPS2483_Register_TypeDef;

typedef enum
{
  TPS2483_ModePowerDown 	=   0,  /**< Power-down mode */
  TPS2483_ModeShuntTrig 	=   1,  /**< Shunt voltage, triggered mode */
  TPS2483_ModeBusTrig 		= 	2,  /**< Bus voltage, triggered mode */
  TPS2483_ModeShuntBusTrig 	=	3,  /**< Shunt and bus, triggered mode */
  TPS2483_ModePowerDown2 	= 	4,	/**< Power-down mode */
  TPS2483_ModeShuntCont 	= 	5,	/**< Shunt voltage, continuous mode */
  TPS2483_ModeBusCont 		= 	6,	/**< Bus voltage, continuous mode */
  TPS2483_ModeShuntBusCont 	= 	7 	/**< Shunt and bus, continuous mode (default) */
} TPS2483_Mode_TypeDef;

typedef enum
{
  TPS2483_BusCT140us		=	0,
  TPS2483_BusCT204us		=	1,
  TPS2483_BusCT332us		=	2,
  TPS2483_BusCT588us		=	3,
  TPS2483_BusCT1100us		=	4, /**< (default) */
  TPS2483_BusCT2116us		=	5,
  TPS2483_BusCT4156us		=	6,
  TPS2483_BusCT8244us		=	7
} TPS2483_BusCT_TypeDef;

typedef enum
{
  TPS2483_ShuntCT140us		=	0,
  TPS2483_ShuntCT204us		=	1,
  TPS2483_ShuntCT332us		=	2,
  TPS2483_ShuntCT588us		=	3,
  TPS2483_ShuntCT1100us		=	4, /**< (default) */
  TPS2483_ShuntCT2116us		=	5,
  TPS2483_ShuntCT4156us		=	6,
  TPS2483_ShuntCT8244us		=	7
} TPS2483_ShuntCT_TypeDef;

typedef enum
{
  TPS2483_AVG1				=	0, /**< (default) */
  TPS2483_AVG4				=	1,
  TPS2483_AVG16				=	2,
  TPS2483_AVG64				=	3,
  TPS2483_AVG128			=	4,
  TPS2483_AVG256			=	5,
  TPS2483_AVG512			=	6,
  TPS2483_AVG1024			=	7
} TPS2483_AVG_TypeDef;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

void TPS2483_Init(void);

int TPS2483_RegisterSet(I2C_TypeDef *i2c,
                         uint8_t addr,
						 TPS2483_Register_TypeDef reg,
                         uint16_t val);

int TPS2483_RegisterGet(I2C_TypeDef *i2c,
                         uint8_t addr,
						 TPS2483_Register_TypeDef reg,
                         uint16_t *val);

int TPS2483_ReadShuntVoltage(I2C_TypeDef *i2c,
                         uint8_t addr,
                         int *val);

int TPS2483_ReadBusVoltage(I2C_TypeDef *i2c,
                         uint8_t addr,
                         int *val);

int TPS2483_ReadPower(I2C_TypeDef *i2c,
                         uint8_t addr,
                         int *val);

int TPS2483_ReadCurr(I2C_TypeDef *i2c,
                         uint8_t addr,
                         int *val);


#endif /* __TPS2483_H */
