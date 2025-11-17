#include "main.h"
#include "uart.h"
#include "dma.h"
#include "adc.h"

#define BUFFER_SIZE 6
#define ADC_CHANNEL(n) (1U << (n))

uint16_t adc_buffer[BUFFER_SIZE];
uint32_t channels = ADC_CHANNEL(0) | ADC_CHANNEL(1);

int main(void)
{
	uart2_init();
	adc_dma_init(ADC_RES_12BIT, ADC_SCAN_UP, channels, adc_buffer, BUFFER_SIZE);
	while (1){
	    for (int i = 0; i < BUFFER_SIZE; i++) {
	        uart2_send_u16(adc_buffer[i]);
	        uart2_send_char(' ');
	    }

	    uart2_send_string("\r\n");

	    for (volatile int d = 0; d < 300000; d++);
	}

}
