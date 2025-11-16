/*
 * adc.c
 *
 *  Created on: Nov 16, 2025
 *      Author: lenovo
 */

#include "adc.h"

void adc_dma_init(void){

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
	ADC1->CHSELR 	|= ADC_CHSELR_CHSEL0 | ADC_CHSELR_CHSEL1;
	ADC1->CFGR1 	&= ~ADC_CFGR1_SCANDIR; //ch0->ch1->...
	//	c. Select continuous coversion
	ADC1->CFGR1		|= ADC_CFGR1_CONT;
	//	d. Select to use DMA
	ADC1->CFGR1		|= ADC_CFGR1_DMAEN | ADC_CFGR1_DMACFG;

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
