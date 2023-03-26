#include "modes.h"


void init_mode1(void)
{
	uart_printstr("init_mode1\r\n");
	ADMUX = 0;

	//select ADC voltage input as external
	ADMUX |= (1 << REFS0);

	//select LDR port
	ADMUX |= (1 << MUX0);

	ADCSRA |= (1 << ADEN) | (1 << ADSC);
}

void clear_mode1(void)
{
	ADCSRA &= ~(1 << ADEN);
}
