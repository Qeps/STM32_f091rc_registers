/*
 * dma.c
 *
 *  Created on: Nov 13, 2025
 *      Author: lenovo
 */
#include "dma.h"

void dma1_MEM2MEM_init(){
	//1. Enable clock on AHBNER for DMA1, bit 0
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	//2. Disable DMA channel
	DMA1_Channel1->CCR = 0;

	//3. Configure DMA parameters
	//MSIZE   - Defines the data size of each DMA transfer to the identified memory.
	//PSIZE   - Defines the data size of each DMA transfer to the identified peripheral.
	//MINC    - Defines the increment mode for each DMA transfer to the identified memory.
	//PINC    - Defines the increment mode for each DMA transfer to the identified peripheral.
	//MEM2MEM - Memory-to-memory mode
	//TCIE    - Transfer complete interrupt enable
	//TEIE    - Transfer error interrupt enable
	//HTIE	  - Half transfer interrupt enable

	//a) Set mem size to 16 bits - 01
	DMA1_Channel1->CCR |= DMA_CCR_MSIZE_0;
	DMA1_Channel1->CCR &= ~DMA_CCR_MSIZE_1;

	//b) Set peripheral size to 16 bits - 01
	DMA1_Channel1->CCR |= DMA_CCR_PSIZE_0;
	DMA1_Channel1->CCR &= ~DMA_CCR_PSIZE_1;

	//c) Set mem increment mode for automatic incrementation - 1
	DMA1_Channel1->CCR |= DMA_CCR_MINC;

	//d) Set peripheral increment mode
	DMA1_Channel1->CCR |= DMA_CCR_PINC;

	//e) Set mem2mem transfer
	DMA1_Channel1->CCR |= DMA_CCR_MEM2MEM;

	//f) Set interrupts error/transfer complete/half transfer
	DMA1_Channel1->CCR |= DMA_CCR_TCIE;
	DMA1_Channel1->CCR |= DMA_CCR_TEIE;
//	DMA1_Channel1->CCR |= DMA_CCR_HTIE;

	//4. Enable DMA interrupt in NVIC
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}
