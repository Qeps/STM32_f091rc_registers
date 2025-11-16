#include "main.h"
#include "uart.h"
#include "dma.h"

#define BUFFER_SIZE 5

int main(void)
{
	uart2_init();
	while(1){

	}
}

void DMA1_CH1_IRQHandler(void){
	// Handle interrupt:
	// DMA_ISR	- DMA interrupt status register
	// DMA_IFCR	- DMA interrupt flag clear register
	// TCIF1	- transfer complete (TC) flag for channel 1
	// CTCIF1	- transfer complete flag clear for channel 1
	// TEIF1	- transfer error (TE) flag for channel 1
	// CTEIF1	- transfer error flag clear for channel 1

	// 1. Check if transfer complete flag is set to 1
    if (DMA1->ISR & DMA_ISR_TCIF1){

    // 2. Set flag for main loop to perform printing results
        dma1_m2m_transf_cmplt = 1;

    // 3. Set clear flag for coresponding register
        DMA1->IFCR |= DMA_IFCR_CTCIF1;
    }

    // 4. Check if transfer error flag occured
    if (DMA1->ISR & DMA_ISR_TEIF1) {

    // 5. Set clear flag for coresponding error register
        DMA1->IFCR |= DMA_IFCR_CTEIF1;
    }
}
