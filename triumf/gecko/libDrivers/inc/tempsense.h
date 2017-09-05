/**
 * @file tempsense.h
 * @author Brandon Borden
 * @date 2015-02-25
 */

#ifndef TEMPSENSE_H_
#define TEMPSENSE_H_

#include <stdint.h>
#include "em_adc.h"


void ADCConfig(void);

uint32_t ADC_GetData(ADC_TypeDef *);



#endif /* TEMPSENSE_H_ */
