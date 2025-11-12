#include "main.h"
#include "uart.h"

int main(void)
{
	uart2_init();
	while(1){
		uart2_send_char('x');
	}
}
