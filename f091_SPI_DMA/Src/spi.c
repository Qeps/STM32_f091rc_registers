/*
 * spi.c
 *
 *  Created on: Nov 19, 2025
 *      Author: lenovo
 */
#include "spi.h"

// Alternate functions (AF0) selected through GPIOA_AFR registers for port a
// PA4 - SPI1_NSS
// PA5 - SPI1_SCK
// PA6 - SPI1_MISO
// PA7 - SPI1_MOSI

void spi1_dma_init(void){
	// GPIO PINS CONFIG
	// 1. Enable clock access to port A for SPI pins - GPIOA
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	// 2. Set SPI pins to alternate function mode
	// Clear every 2bits if needed in more complicated code - GPIOA->MODER &= ~GPIO_MODER_MODER7_Msk;
	GPIOA->MODER |= GPIO_MODER_MODER4_1;
	GPIOA->MODER |= GPIO_MODER_MODER5_1;
	GPIOA->MODER |= GPIO_MODER_MODER6_1;
	GPIOA->MODER |= GPIO_MODER_MODER7_1;
	// 3. Set SPI pins alternate mode to AF0
	// AF0 = 0000
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL4_Msk;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL5_Msk;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL6_Msk;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL7_Msk;

	// SPI CONFIG
	// 1. Enable clock access to SPI1 module
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	// 2. Set software/hardware slave managment
	SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;
	// 3. Set SPI to master mode
	SPI1->CR1 |= SPI_CR1_MSTR;
	// 4. Set CPHA - clock phase (rising/falling) and CPOL - clock polarity (high/low state is 1/0)
	SPI1->CR1 |= SPI_CR1_CPOL | SPI_CR1_CPHA;
	// 5. Clock divider fplk/4
	SPI1->CR1 |= SPI_CR1_BR_0;
	SPI1->CR1 &= ~SPI_CR1_BR_1;
	SPI1->CR1 &= ~SPI_CR1_BR_2;
	// 5. Select to use DMA
	SPI1->CR2 |= SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN;
	// 6. Enable SPI
	SPI1->CR1 |= SPI_CR1_SPE;
}

void dma1_spi_rx_CxS0000_init(void){
	// DMA config
	//1. Enable clock access to DMA
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	//2. Disable DMA channel
	DMA1_Channel2->CCR = 0;

	//DMA channel2 parameters
	//1. Enable mem increment
	DMA1_Channel2->CCR |= DMA_CCR_MINC;
	//2. Set transfer direction peripheral to mem
	DMA1_Channel2->CCR &= ~DMA_CCR_DIR;
	//3 Set interrupts error/transfer complete
	DMA1_Channel2->CCR |= DMA_CCR_TCIE | DMA_CCR_TEIE;
	//4. Enable DMA interrupt in NVIC
	NVIC_EnableIRQ(DMA1_Channel2_IRQn);
}

void dma1_spi_tx_CxS0000_init(void){
	// DMA config
	//1. Enable clock access to DMA
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	//2. Disable DMA channel
	DMA1_Channel3->CCR = 0;

	//DMA channel3 parameters
	//1. Enable mem increment
	DMA1_Channel3->CCR |= DMA_CCR_MINC;
	//2. Set transfer direction mem to peripheral
	DMA1_Channel3->CCR |= DMA_CCR_DIR;
	//3 Set interrupts error/transfer complete
	DMA1_Channel3->CCR |= DMA_CCR_TCIE | DMA_CCR_TEIE;
	//4. Enable DMA interrupt in NVIC
	NVIC_EnableIRQ(DMA1_Channel3_IRQn);
}

void dma1_channel2_spi_rx_transfer_start(uint8_t *buf, uint32_t len){
	//1. Clear interrupt flags
	DMA1->IFCR = DMA_IFCR_CGIF2 | DMA_IFCR_CTCIF2 | DMA_IFCR_CTEIF2;
	//2. Set peripheral address
	DMA1_Channel2->CPAR  = (uint32_t)&SPI1->DR;
	//3. Set memory address
	DMA1_Channel2->CMAR  = (uint32_t)buf;
	//4. Set transfer length
	DMA1_Channel2->CNDTR = len;
	//5. Enable RX
	DMA1_Channel2->CCR |= DMA_CCR_EN;
}

void dma1_channel3_spi_tx_transfer_start(uint8_t *buf, uint32_t len){
	//1. Clear interrupt flags
	DMA1->IFCR = DMA_IFCR_CGIF3 | DMA_IFCR_CTCIF3 | DMA_IFCR_CTEIF3;
	//2. Set peripheral address
	DMA1_Channel3->CPAR  = (uint32_t)&SPI1->DR;
	//3. Set memory address
	DMA1_Channel3->CMAR  = (uint32_t)buf;
	//4. Set transfer length
	DMA1_Channel3->CNDTR = len;
	//5. Enable TX
	DMA1_Channel3->CCR |= DMA_CCR_EN;
}

