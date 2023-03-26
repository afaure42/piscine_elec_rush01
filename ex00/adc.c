#include "adc.h"

void adc_init(void)
{
	//setting prescaler at 128 because 16 000 000 / 128 = 125 000 wich is in the range of the ADC
	//and enabling auto trigger
	ADCSRA = (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADATE);

	ADCSRA |= (1 << ADIE); //enabling interrupt

	ADMUX = (1 << REFS0); //setting reference voltage as AREF pin / AVcc
	
	//leaving MUX selection bits as false in ADMUX since i only want ADC0 as input
}
