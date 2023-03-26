#include "modes.h"

void init_mode3(void)
{
	uart_printstr("init_mode3\r\n");
	ADMUX = 0;

	//select ADC voltage input as internal 1.1volts
	ADMUX |= (1 << REFS0) | (1 << REFS1);

	//select NTC port
	ADMUX |= 0b1000 << MUX0;

	ADCSRA |= (1 << ADEN) | (1 << ADSC);
}

void clear_mode3(void)
{
	ADCSRA &= ~(1 << ADEN);
}
