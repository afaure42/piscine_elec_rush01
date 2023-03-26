#include "modes.h"


void init_mode2(void)
{
	uart_printstr("init_mode1\r\n");
	ADMUX = 0;

	//select ADC voltage input as external
	ADMUX |= (1 << REFS0);

	//select NTC port
	ADMUX |= NTC_PIN;

	ADCSRA |= (1 << ADEN) | (1 << ADSC);
}

void clear_mode2(void)
{
	ADCSRA &= ~(1 << ADEN);
}
