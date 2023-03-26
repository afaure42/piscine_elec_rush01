#include "modes.h"

//set ADC reading in RV1
void init_mode0(void)
{
	uart_printstr("Mode 0 init\r\n");
	ADMUX = 0;

	//select ADC voltage input as external
	ADMUX |= (1 << REFS0);


	ADCSRA |= (1 << ADEN) | (1 << ADSC);
}

void clear_mode0(void)
{
	uart_printstr("Mode 0 clear\r\n");
	//disable ADC

	clear_segment();
	ADCSRA &= ~(1 << ADEN);
}
