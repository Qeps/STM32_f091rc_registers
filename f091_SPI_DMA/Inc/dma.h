/*
 * dma.h
 *
 *  Created on: Nov 13, 2025
 *      Author: lenovo
 */

#ifndef DMA_H_
#define DMA_H_

#include <stdint.h>
#include "stm32f0xx.h"

typedef enum {
	DMA_MEM_SIZE_8BIT         = 0,
	DMA_MEM_SIZE_16BIT        = DMA_CCR_MSIZE_0,
	DMA_MEM_SIZE_32BIT 	      = DMA_CCR_MSIZE_1,
	DMA_MEM_SIZE_RESERVED  	  = (DMA_CCR_MSIZE_0 | DMA_CCR_MSIZE_1)
} dma_mem_size_t;

typedef enum {
	DMA_PERIPH_SIZE_8BIT      = 0,
	DMA_PERIPH_SIZE_16BIT     = DMA_CCR_PSIZE_0,
	DMA_PERIPH_SIZE_32BIT 	  = DMA_CCR_PSIZE_1,
	DMA_PERIPH_SIZE_RESERVED  = (DMA_CCR_PSIZE_0 | DMA_CCR_PSIZE_1)
} dma_periph_size_t;

typedef enum {
    DMA_MINC_DISABLE = 0,
    DMA_MINC_ENABLE  = DMA_CCR_MINC
} dma_mem_inc_t;

typedef enum {
    DMA_DIR_PERIPH2MEM = 0,
    DMA_DIR_MEM2PERIPH = DMA_CCR_DIR
} dma_direction_t;

typedef enum {
    DMA_CIRC_DISABLE = 0,
    DMA_CIRC_ENABLE  = DMA_CCR_CIRC
} dma_circular_t;


void dma1_ch1_mem2mem_init();
void dma1_ch1_mem2mem_transfer_start(uint32_t src_buf, uint32_t dest_buf, uint32_t len);
void dma1_ch1_periph_mem_init(dma_circular_t 	  mode,
							  dma_mem_size_t 	  mem_size,
							  dma_periph_size_t   periph_size,
							  dma_mem_inc_t		  mem_inc,
							  uint32_t 			  periph_address,
							  uint32_t			  *mem_address,
							  dma_direction_t	  transfer_dir);

#endif /* DMA_H_ */
