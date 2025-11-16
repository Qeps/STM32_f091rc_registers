/*
 * adc.c
 *
 *  Created on: Nov 16, 2025
 *      Author: lenovo
 */

#include "adc.h"

void adc_dma_init(adc_resolution_t res, adc_scan_dir_t scan, uint32_t channels_mask){

	//1. GPIO config
	//	a. Enable clock access to ADC GPIO Pin's port
	RCC->AHBENR 	|= RCC_AHBENR_GPIOAEN;

	//	b. Set PA0 and PA1 mode to analog
	GPIOA->MODER 	|= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER0_1;
	GPIOA->MODER 	|= GPIO_MODER_MODER1_0 | GPIO_MODER_MODER1_1;

	//2. ADC config
	//	a. Enable clock access to ADC
	RCC->APB2ENR 	|= RCC_APB2ENR_ADCEN;

	//	b. Select channels and set sequence (which pin will be first)
	ADC1->CHSELR 	|= channels_mask;

	// 	c. Configure resolution + scan direction
	ADC1->CFGR1 	&= ~(ADC_CFGR1_RES | ADC_CFGR1_SCANDIR);
	ADC1->CFGR1		|= (res | scan);

	//  d. ADC calibration
	ADC1->CR |= ADC_CR_ADCAL;
	while (ADC1->CR & ADC_CR_ADCAL){
		//Time-out managment
	}

	//	e. Select continuous coversion and to use DMA
	ADC1->CFGR1		|= ADC_CFGR1_CONT | ADC_CFGR1_DMAEN | ADC_CFGR1_DMACFG;

	//3. DMA config
	//	a. Enable clock access to DMA
	//	b. Disable DMA channel
	//	c. Wait till disabled
	//	d. Enable circular mode
	//	e. Set mem transfer size
	//	f. Set periph transfer size
	//	g. Enable mem increment
	//	h. Set mem address
	//	i. Set periph address
	//	j. Set number of transfer
	//	k. Enable DMA channel

	//4. ADC run
	//	a. Enable ADC
	//	b. Start ADC

}
