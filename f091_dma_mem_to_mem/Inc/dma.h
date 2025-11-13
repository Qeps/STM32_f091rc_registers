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

void dma1_ch1_mem2mem_init();
void dma1_ch1_mem2mem_transfer_start(uint32_t src_buf, uint32_t dest_buf, uint32_t len);

#endif /* DMA_H_ */
