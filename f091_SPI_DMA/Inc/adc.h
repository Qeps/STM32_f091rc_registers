/*
 * adc.h
 *
 *  Created on: Nov 16, 2025
 *      Author: lenovo
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "stm32f0xx.h"
#include "dma.h"

typedef enum {
	ADC_RES_12BIT = 0,
    ADC_RES_10BIT = ADC_CFGR1_RES_0,
    ADC_RES_8BIT  = ADC_CFGR1_RES_1,
    ADC_RES_6BIT  = (ADC_CFGR1_RES_1 | ADC_CFGR1_RES_0)
} adc_resolution_t;

typedef enum {
    ADC_SCAN_UP   = 0,                     // CH0→CH1→...
    ADC_SCAN_DOWN = ADC_CFGR1_SCANDIR      // CH1→CH0→...
} adc_scan_dir_t;

void adc_dma_init(adc_resolution_t res,
				  adc_scan_dir_t scan,
				  uint32_t channels_mask,
				  uint16_t * adc_buffer,
				  uint16_t length);

#endif /* ADC_H_ */
