/*
 * uart.h
 *
 *  Created on: Nov 12, 2025
 *      Author: lenovo
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f0xx.h"

void uart2_init(void);
void uart2_send_char(int ch);

#endif /* UART_H_ */
