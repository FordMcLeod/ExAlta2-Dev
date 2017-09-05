/*
 * sharedtypes.h
 *
 *  Created on: Apr 6, 2015
 *      Author: sdamkjar
 */

#ifndef SHAREDTYPES_H_
#define SHAREDTYPES_H_

/* --Exported common structure -----------------------------------------------*/
#ifndef __SHARED__TYPES
#define __SHARED__TYPES

typedef enum {
	MEMS_SUCCESS = 0x01, MEMS_ERROR = 0x00
} status_t;

typedef enum {
	MEMS_ENABLE = 0x01, MEMS_DISABLE = 0x00
} State_t;

typedef struct {
	int16_t AXIS_X;
	int16_t AXIS_Y;
	int16_t AXIS_Z;
} AxesRaw_t;

#endif /*__SHARED__TYPES*/

#endif /* SHAREDTYPES_H_ */
