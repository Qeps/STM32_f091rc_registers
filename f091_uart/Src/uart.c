/*
 * uart.c
 *
 *  Created on: Nov 12, 2025
 *      Author: lenovo
 */

#include <uart.h>

#define UART_BAUDRATE 115200
#define CLK			  8000000
static uint16_t compute_uart_baudrate(uint32_t periph_clk, uint32_t baudrate);
static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
void uart2_send_char(int ch);

void uart2_init(void){
	// 1. Enable clock signal for GPIOA
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	// 2. Set PA2 mode to alternate function mode (10)
	GPIOA->MODER |= GPIO_MODER_MODER2_1;
	GPIOA->MODER &= ~GPIO_MODER_MODER2_0;

	// 3. Set PA3 mode to alternate function mode
	GPIOA->MODER |= GPIO_MODER_MODER3_1;
	GPIOA->MODER &= ~GPIO_MODER_MODER3_0;

	// 4. Set PA2 alternate function type to AF1(UART2_TX) - GPIOx_AFRL 0001
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL2_Msk;			// clear all 4 bitfields
	GPIOA->AFR[0] |= (1U << GPIO_AFRL_AFSEL2_Pos);	// set 0001 value

	// 5. Set PA3 alternate function type to AF1(UART2_RX)
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL3_Msk;			// clear all 4 bitfields
	GPIOA->AFR[0] |= (1U << GPIO_AFRL_AFSEL3_Pos);	// set 0001 value

	// 6. Enable clock signal for USART2 on APB bus (17th bit)
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	// 7. Set baudrate
	uart_set_baudrate(CLK, UART_BAUDRATE);

	// 8. Set transfer direction
	USART2->CR1 = 0;
	USART2->CR1 |= USART_CR1_TE; // Bit 3: Transmitter enable
	USART2->CR1 |= USART_CR1_RE; // Bit 2: Receiver enable

	// 9. Enable UART module
	USART2->CR1 |= USART_CR1_UE;
}

void uart2_send_char(int ch){
	// 1. Transmit data register must be empty
	while (!(USART2->ISR & USART_ISR_TXE));
	// 2. Write to transmit data
	USART2->TDR = (ch & 0xFF);
}

static uint16_t compute_uart_baudrate(uint32_t periph_clk, uint32_t baudrate){
	return ((periph_clk + (baudrate/2U))/baudrate);
}

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate){
	USART2->BRR = compute_uart_baudrate(periph_clk, baudrate);
}


