
#include "em_i2c.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "TPS2483.h"

/*******************************************************************************
 **************************   GLOBAL VARIABLES   *******************************
 ******************************************************************************/
I2C_TransferReturn_TypeDef I2C_Status;

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/**************************************************************************//**
 * @brief I2C Interrupt Handler.
 *        The interrupt table is in assembly startup file startup_efm32.s
 *****************************************************************************/
void I2C0_IRQHandler(void)
{
  /* Just run the I2C_Transfer function that checks interrupts flags and returns */
  /* the appropriate status */
  I2C_Status = I2C_Transfer(I2C0);
}

/***************************************************************************//**
 * @brief
 *   Initalize basic I2C interrupt
 ******************************************************************************/
void TPS2483_Init(void)
{
  
  /* Clear and enable interrupt from I2C module */
  NVIC_ClearPendingIRQ(I2C0_IRQn);
  NVIC_EnableIRQ(I2C0_IRQn);
}

/***************************************************************************//**
 * @brief
 *   Write to sensor register.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address for temperature sensor, in 8 bit format, where LSB is reserved
 *   for R/W bit.
 *
 * @param[in] reg
 *   Register to write (temperature register cannot be written).
 *
 * @param[in] val
 *   Value used when writing to register.
 *
 * @return
 *   Returns 0 if register written, <0 if unable to write to register.
 ******************************************************************************/
int TPS2483_RegisterSet(I2C_TypeDef *i2c,
                         uint8_t addr,
						 TPS2483_Register_TypeDef reg,
                         uint16_t val)
{
  I2C_TransferSeq_TypeDef seq;
  uint8_t data[3];

  seq.addr = addr;
  seq.flags = I2C_FLAG_WRITE;

  data[0] = ((uint8_t)reg);
  data[1] = (uint8_t)(val >> 8);
  data[2] = (uint8_t)val;
  
  seq.buf[0].data = data;
  seq.buf[0].len = 3;

  I2C_Status = I2C_TransferInit(i2c, &seq);

  while (I2C_Status == i2cTransferInProgress)
  {
    /* Enter EM1 while waiting for I2C interrupt */
    EMU_EnterEM1();
    /* Could do a timeout function here. */
  }
  
  return((int)I2C_Status);
}

/***************************************************************************//**
 * @brief
 *   Read sensor register content.
 *
 * @details
 *   If reading the temperature register, when a measurement is completed inside
 *   the sensor device, the new measurement may not be stored. For this reason,
 *   the temperature should not be polled with a higher frequency than the
 *   measurement conversion time for a given resolution configuration. Please
 *   refer to sensor device datasheet.
 *
 * @param[in] i2c
 *   Pointer to I2C peripheral register block.
 *
 * @param[in] addr
 *   I2C address for temperature sensor, in 8 bit format, where LSB is reserved
 *   for R/W bit.
 *
 * @param[in] reg
 *   Register to read.
 *
 * @param[out] val
 *   Reference to place register read.
 *
 * @return
 *   Returns 0 if register read, <0 if unable to read register.
 ******************************************************************************/
int TPS2483_RegisterGet(I2C_TypeDef *i2c,
                         uint8_t addr,
                         TPS2483_Register_TypeDef reg,
                         uint16_t *val)
{
  I2C_TransferSeq_TypeDef seq;
  uint8_t regid[1];
  uint8_t data[2];

  seq.addr = addr;
  seq.flags = I2C_FLAG_WRITE_READ;
  /* Select register to be read */
  regid[0] = ((uint8_t)reg) & 0x7;
  seq.buf[0].data = regid;
  seq.buf[0].len = 1;
  
  seq.buf[1].data = data;
  seq.buf[1].len = 2;

  /* Do a polled transfer */
  I2C_Status = I2C_TransferInit(i2c, &seq);
  while (I2C_Status == i2cTransferInProgress)
  {
    /* Enter EM1 while waiting for I2C interrupt */
    EMU_EnterEM1();
    /* Could do a timeout function here. */
  }
  
  if (I2C_Status != i2cTransferDone)
  {
    return((int)I2C_Status);
  }

  *val = (((uint16_t)(data[0])) << 8) | data[1];

  return((int)I2C_Status);
}

int TPS2483_ReadShuntVoltage(I2C_TypeDef *i2c,
                         uint8_t addr,
                         int *val)
{

  int ret;

  uint16_t tmp = 0;

  ret = TPS2483_RegisterGet(i2c,addr,TPS2483_RegShuntV,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  if(tmp >> 15)
  {
  	*val = -(tmp & 0x7FFF);
  }
  else *val = tmp*5;

  return((int)I2C_Status);

}

int TPS2483_ReadBusVoltage(I2C_TypeDef *i2c,
                         uint8_t addr,
                         int *val)
{

  int ret;

  uint16_t tmp = 0;

  ret = TPS2483_RegisterGet(i2c,addr,TPS2483_RegBusV,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  *val = tmp & 0x7FFF;

  return((int)I2C_Status);

}

int TPS2483_ReadPower(I2C_TypeDef *i2c,
                         uint8_t addr,
                         int *val)
{

  int ret;

  uint16_t tmp = 0;

  ret = TPS2483_RegisterGet(i2c,addr,TPS2483_RegPower,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  *val = tmp;

  return((int)I2C_Status);

}

int TPS2483_ReadCurr(I2C_TypeDef *i2c,
                         uint8_t addr,
                         int *val)
{

  int ret;

  uint16_t tmp = 0;

  ret = TPS2483_RegisterGet(i2c,addr,TPS2483_RegCurr,&tmp);
  if (ret < 0)
  {
    return(ret);
  }

  if(tmp >> 15)
  {
  	*val = -(tmp & 0x7FFF);
  }
  else *val = tmp;

  return((int)I2C_Status);

}
