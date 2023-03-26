#include "i2c_expander.h"



uint8_t segment_display_buffer[4];
uint8_t segment_display_index;
const uint8_t segment_digit_pins[4];

volatile uint8_t segment_digits[] =
{
	0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01100111, //9
};

void expander_init()
{
	i2c_start(EXPANDER_ADDR, TW_WRITE);

	uint8_t register_select;
	uint8_t register_status = 0;


	//set sw3 as input (1) and everything else as output (0)
	register_status = (1 << SW3);
	register_select = SELECT_CONFIG_PORT0;
	i2c_send_byte(&register_select, 1);
	i2c_send_byte(&register_status, 1);
	
	//set 7segment as output
	register_status = 0;
	i2c_send_byte(&register_status, 1); //config port 1 now

	//clear output registers
	i2c_start(EXPANDER_ADDR, TW_WRITE);
	register_status = 0xFF;
	register_select = SELECT_OUTPUT_PORT0;
	i2c_send_byte(&register_select, 1);
	i2c_send_byte(&register_status, 1); //first one will put 0 in register 0
	i2c_send_byte(&register_status, 1); //second one will automatically be put in register 1
	i2c_stop();

	segment_display_buffer[0] = 0x0;
	segment_display_buffer[1] = 0x0;
	segment_display_buffer[2] = 0x0;
	segment_display_buffer[3] = 0x0;

}

uint8_t expander_segment_select_digit(uint8_t select_digit)
{
	uint8_t status;
	if (expander_get_register(SELECT_OUTPUT_PORT0, &status) != 0)
		return (1);

	status |= 0b11110000; //clear digits ( clearing is setting bits)

	status &= ~(1 << segment_digit_pins[select_digit]);

	return (expander_set_register(SELECT_OUTPUT_PORT0, status));
}

uint8_t expander_get_register(uint8_t select_register, uint8_t * dest)
{
	uint8_t command;
	command = select_register;

	//sending write 
	i2c_start(EXPANDER_ADDR, TW_WRITE);
	if (TWSR != TW_MT_SLA_ACK)
		return (1);

	//selecting register
	i2c_send_byte(&command, 1);
	if (TWSR != TW_MT_DATA_ACK)
		return (1);

	//going in read mode using repeated start	
	i2c_start(EXPANDER_ADDR, TW_READ);
	if (TWSR != TW_MR_SLA_ACK)
		return (1);

	//reading register value
	i2c_read_byte(dest, 1);
	if (TWSR != TW_MR_DATA_NACK)
		return (1);

	i2c_stop();
	return 0;
}

uint8_t expander_set_register(uint8_t select_register, uint8_t register_status)
{
	i2c_start(EXPANDER_ADDR, TW_WRITE);
	if ((TWSR & TW_STATUS_MASK) != TW_MT_SLA_ACK) {
		i2c_stop();
		return (1);
	}

	i2c_send_byte(&select_register, 1);
	if ((TWSR & TW_STATUS_MASK) != TW_MT_DATA_ACK) {
		i2c_stop();
		return (1);
	}

	i2c_send_byte(&register_status, 1);
	if ((TWSR & TW_STATUS_MASK) != TW_MT_DATA_ACK) {
		i2c_stop();
		return (1);
	}

	i2c_stop();
	return (0);
}

uint8_t exp_set_pin(uint8_t led_id, uint8_t status)
{
	uint8_t register_status;
	if (expander_get_register(EXPANDER_REGISTER_0, &register_status) != 0)
		return 1;

	if (status == 0)
		register_status |= (1 << led_id);
	else
		register_status &= ~(1 << led_id);
	
	return (expander_set_register(SELECT_OUTPUT_PORT0, register_status));
}


void segment_putnbr(uint16_t nbr)
{
	clear_segment();
	if (nbr > 999)
		segment_display_buffer[3] = segment_digits[nbr / 1000];
	if (nbr > 99)
		segment_display_buffer[2] = segment_digits[(nbr % 1000) / 100];
	if (nbr > 9)
		segment_display_buffer[1] = segment_digits[(nbr % 100) / 10];
	segment_display_buffer[0] = segment_digits[nbr % 10];
}

void segment_putnbr_fill_zero(uint16_t nbr)
{
	clear_segment();

	segment_display_buffer[3] = segment_digits[nbr / 1000];
	segment_display_buffer[2] = segment_digits[(nbr % 1000) / 100];
	segment_display_buffer[1] = segment_digits[(nbr % 100) / 10];
	segment_display_buffer[0] = segment_digits[nbr % 10];
}

void clear_segment()
{
	segment_display_buffer[0] = 0;
	segment_display_buffer[1] = 0;
	segment_display_buffer[2] = 0;
	segment_display_buffer[3] = 0;
}
