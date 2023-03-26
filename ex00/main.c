#include "rush.h"

#define LED_D1 PB0
#define LED_D2 PB1
#define LED_D3 PB2
#define LED_D4 PB4

extern uint8_t segment_display_buffer[4];
extern uint8_t segment_display_index;

volatile uint8_t g_switch1_counter;
volatile uint8_t g_switch2_counter;
volatile uint8_t g_switch3_status = 0;
volatile uint8_t g_mode = 0;


void display_mode(void);
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

//sw1 ISR that can change current mode and light up led D9
ISR(INT0_vect)
{
	uart_printstr("INTERRUPT\r\n");
	g_switch1_counter++;
	if (g_switch1_counter & 1)
	{
		g_mode++;
		if (g_mode > 10)
			g_mode = 0;
		display_mode();
		exp_set_pin(LED_D9, 1);
	}
	else
		exp_set_pin(LED_D9, 0);
	_delay_ms(1);
	EIFR |= (1 << INTF0); //clear the interrupt bit in case rebounce set it again
}

// PCINT20 ( SW2 switch ) ISR that can change current mode and light up led D10
ISR(PCINT2_vect)
{
	g_switch2_counter++;
	if (g_switch2_counter & 1)
	{
		if (g_mode == 0)
			g_mode = 10;
		else
			g_mode--;
			display_mode();
		exp_set_pin(LED_D10, 1);
	}
	else
		exp_set_pin(LED_D10, 0);
	_delay_ms(1);
	PCIFR |= (1 << PCIF2);
}

void poll_sw3(void)
{
	uint8_t save_sreg = SREG;
	uint8_t register_status = 0;
	uint8_t return_value = 0;
	//clearing interrupt enable flag
	cli();

	return_value = expander_get_register(SELECT_INPUT_PORT0, &register_status);
	//reloading saved SREG status
	SREG = save_sreg;

	if (return_value != 0)//if there was an error with i2c
		return;

	//if button just got pressed since last poll
	if (((register_status & (1 << SW3)) == 0) && g_switch3_status == 1) 
	{
		g_switch3_status = 0;
		exp_set_pin(LED_D11, 1);
	}
	else if (((register_status & (1 << SW3)) == 1) && g_switch3_status == 0)// if button just got released since last poll
	{
		g_switch3_status = 1;
		exp_set_pin(LED_D11, 0);
	}
}

void display_mode(void)
{
	PORTB &= ~(1 << PB0) & ~(1 << PB1) & ~(1 << PB2) & ~(1 << PB4);

	PORTB |= (g_mode & 0b0111) << PB0;

	PORTB |= ((g_mode & 0b1000) >> 3) << PB4;
}

int main()
{
	DDRD = 0;
	DDRB = (1 << LED_D1) | (1 << LED_D2) | (1 << LED_D3) | (1 << LED_D4);
	uart_init();
	i2c_init();
	expander_init();

	EIMSK = (1 << INT0); //enable INT0 on logical change
	EICRA = (1 << ISC00);

	PCICR = (1 << PCIE2);
	PCMSK2 = (1 << PCINT20);

	sei();
	for(;;)
	{
		poll_sw3();
	}	
}
