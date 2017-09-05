/*
 * i2c.h
 *
 *  Created on: Apr 2, 2015
 *      Author: sdamkjar
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include <sharedtypes.h>

#define I2C_ADDRESS         (98)
#define I2C_MAX_TX_BUFFER_SIZE ((uint8_t)200)
#define I2C_MAX_RX_BUFFER_SIZE ((uint8_t)200)

#define I2C_DELAY              (1 / portTICK_RATE_MS)

void I2C0_setup(void);

void I2C0_IRQHandler(void);

status_t commandRdy(void);
status_t writeI2C(uint8_t*);
status_t readI2C(uint8_t*);

#endif /* I2C_H_ */
