/**
 * @file tempsense.c
 * @author Brandon Borden
 * @date 2015-02-25
 */

#include "tempsense.h"

#include "em_cmu.h"
#include "em_adc.h"

/***************************************************************************//**
* @brief
*   Configure ADC usage for the temperature sensor.
*******************************************************************************/
void ADCConfig(void)
{
	ADC_Init_TypeDef       init       = ADC_INIT_DEFAULT;
	ADC_InitSingle_TypeDef singleInit = ADC_INITSINGLE_DEFAULT;

	/* WARMUPMODE must be set to Normal according to ref manual before */
	/* entering EM2. In this example, the warm-up time is not a big problem */
	/* due to relatively infrequent polling. Leave at default NORMAL, */

	ADC_Init(ADC0, &init);

	/* Init for single conversion use, measure VDD with 2.5V reference. */
	singleInit.reference  = adcRef2V5;
	singleInit.input      = adcSingleInpCh4;
	singleInit.resolution = adcRes12Bit;

	/* The datasheet specifies a minimum acquisition time when sampling vdd/3 */
	/* 32 cycles should be safe for all ADC clock frequencies */
	singleInit.acqTime = adcAcqTime32;

	ADC_InitSingle(ADC0, &singleInit);
}


uint32_t ADC_GetData(ADC_TypeDef * ADC_Base_Ptr)
{

	uint32_t sample;

	ADC_Start(ADC_Base_Ptr, adcStartSingle);

	/* Wait while conversion is active */
	while (ADC_Base_Ptr->STATUS & ADC_STATUS_SINGLEACT);

	/* Get ADC result */
	sample = ADC_DataSingleGet(ADC_Base_Ptr);

	return sample;
}
