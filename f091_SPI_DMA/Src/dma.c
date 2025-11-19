/*
 * dma.c
 *
 *  Created on: Nov 13, 2025
 *      Author: lenovo
 */
#include "dma.h"

void dma1_ch1_mem2mem_transfer_start(uint32_t src_buf, uint32_t dest_buf, uint32_t len);

void dma1_ch1_mem2mem_init(){
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

void dma1_ch1_periph_mem_init(dma_circular_t 	  mode,
							  dma_mem_size_t 	  mem_size,
							  dma_periph_size_t   periph_size,
							  dma_mem_inc_t		  mem_inc,
							  uint32_t 			  periph_address,
							  uint32_t			  *mem_address,
							  dma_direction_t	  transfer_dir){
	//1. Enable clock access to DMA
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	//2. Disable DMA channel
	DMA1_Channel1->CCR = 0;

	//3. Enable circular mode
	DMA1_Channel1->CCR &= ~DMA_CCR_CIRC;
	DMA1_Channel1->CCR |= mode;

	//4. Set mem transfer size
	DMA1_Channel1->CCR &= ~(DMA_CCR_MSIZE_0 | DMA_CCR_MSIZE_1);
	DMA1_Channel1->CCR |= mem_size;

	//5. Set periph transfer size
	DMA1_Channel1->CCR &= ~(DMA_CCR_PSIZE_0 | DMA_CCR_PSIZE_1);
	DMA1_Channel1->CCR |= periph_size;

	//6. Enable mem increment - every sample from adc will be stored in next memory address instead being overwritten
	DMA1_Channel1->CCR &= ~DMA_CCR_MINC;
	DMA1_Channel1->CCR |= mem_inc;
	//PINC has to be 0, it is by default, DMA1_Channel1->CCR &= ~DMA_CCR_PINC;

	//7. Set periph address
	DMA1_Channel1->CPAR = periph_address;

	//8. Set mem address
	DMA1_Channel1->CMAR = mem_address;

	//9. Set transfer direction
	DMA1_Channel1->CCR &= ~DMA_CCR_DIR;
	DMA1_Channel1->CCR |= transfer_dir;
}

void dma1_ch1_mem2mem_transfer_start(uint32_t src_buf, uint32_t dest_buf, uint32_t len){
	//1. Set peripheral address
	DMA1_Channel1->CPAR = src_buf;

	//2. Set memory address
	DMA1_Channel1->CMAR = dest_buf;

	//3. Set transfer length
	DMA1_Channel1->CNDTR = len;

	//4. Set direction from peripheral (CPAR) to memory (CMAR)
	DMA1_Channel1->CCR &= ~DMA_CCR_DIR;

	//5. Enable DMA1 channel 1
	DMA1_Channel1->CCR |= DMA_CCR_EN;
}
