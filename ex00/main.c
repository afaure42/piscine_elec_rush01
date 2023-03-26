#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include "uart.h"
#include "i2c.h"
#include "i2c_expander.h"

extern uint8_t segment_display_buffer[4];
extern uint8_t segment_display_index;

//timer 0 reserved for 7 segment display
ISR(TIMER0_OVF_vect)
{
	uint8_t temp;

	//clearing the digit select bit
	if (expander_get_register(SELECT_OUTPUT_PORT0, &temp) != 0)
	{
		// uart_print_twi_status();
		// uart_printstr("get register failed\r\n");
		reti();
	}

	if (expander_set_register(SELECT_OUTPUT_PORT0, temp | 0b11110000) != 0)
	{
		// uart_print_twi_status();
		// uart_printstr("set register failed\r\n");
		reti();
	}

	//setting digit in display register		
	if (expander_set_register(SELECT_OUTPUT_PORT1, segment_display_buffer[segment_display_index]) != 0)
	{
		// uart_print_twi_status();
		// uart_printstr("set register failed\r\n");
		reti();
	}

	if (expander_segment_select_digit(segment_display_index) != 0)
	{
		// uart_printstr("select digit failed\r\n");
		reti();
	}

	segment_display_index++;
	if (segment_display_index == 4)
		segment_display_index = 0;
}


int main()
{

	uart_init();
	expander_init();
	i2c_init();

	for(;;);	
}
