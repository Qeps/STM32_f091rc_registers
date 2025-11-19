/*
 * adc.c
 *
 *  Created on: Nov 16, 2025
 *      Author: lenovo
 */

#include "adc.h"

void adc_dma_init(adc_resolution_t res,
				  adc_scan_dir_t scan,
				  uint32_t channels_mask,
				  uint16_t * adc_buffer,
				  uint16_t length){

	//1. GPIO config
	//Enable clock access to ADC GPIO Pin's port
	RCC->AHBENR 	|= RCC_AHBENR_GPIOAEN;
	//Set PA0 and PA1 mode to analog
	GPIOA->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1);
	GPIOA->MODER |=  (GPIO_MODER_MODER0 | GPIO_MODER_MODER1);

	//2. ADC config
	//Enable clock access to ADC
	RCC->CR2 |= RCC_CR2_HSI14ON;
	while (!(RCC->CR2 & RCC_CR2_HSI14RDY)) {
		//Time-out managment
	}
	RCC->APB2ENR |= RCC_APB2ENR_ADCEN;

	//Check if ADC is disabled before calibration
	ADC1->CR |= ADC_CR_ADDIS;
	while (ADC1->CR & ADC_CR_ADEN){}

	//Disable DMA during calibration
	ADC1->CFGR1 &= ~ADC_CFGR1_DMAEN;

	//Select channels and set sequence (which pin will be first)
	ADC1->CHSELR = channels_mask;

	//Configure resolution + scan direction + continuous coversion mode
	ADC1->CFGR1 &= ~(ADC_CFGR1_RES | ADC_CFGR1_SCANDIR | ADC_CFGR1_CONT);
	ADC1->CFGR1 |= (res | scan | ADC_CFGR1_CONT);

	//ADC calibration
	ADC1->CR |= ADC_CR_ADCAL;
	while (ADC1->CR & ADC_CR_ADCAL){
		//Time-out managment
	}

	// Ensure ADRDY = 0
	if (ADC1->ISR & ADC_ISR_ADRDY){
	    ADC1->ISR |= ADC_ISR_ADRDY;
	}

	//Enable ADC
	ADC1->CR |= ADC_CR_ADEN;
	//Wait for ADC to be ready
	while (!(ADC1->ISR & ADC_ISR_ADRDY)){
		//Time-out managment
	}

	//Select to use DMA
	ADC1->CFGR1	|= ADC_CFGR1_DMAEN | ADC_CFGR1_DMACFG;

	// CRUCIAL LINE if you skipped this line buffer will be filled once
	// 239.5 cycles sampling time
	ADC1->SMPR |= ADC_SMPR_SMP_2 | ADC_SMPR_SMP_1 | ADC_SMPR_SMP_0;

	//3. DMA config
	dma1_ch1_periph_mem_init(DMA_CIRC_ENABLE,
							 DMA_MEM_SIZE_16BIT,
							 DMA_PERIPH_SIZE_16BIT,
							 DMA_MINC_ENABLE,
							 (uint32_t)&ADC1->DR,
							 (uint32_t *)adc_buffer,
							 DMA_DIR_PERIPH2MEM);
	//Set transfer length
	DMA1_Channel1->CNDTR = length;
	//Enable DMA channel
	DMA1_Channel1->CCR |= DMA_CCR_EN;

	//5. ADC run
	ADC1->CR |= ADC_CR_ADSTART;

}
