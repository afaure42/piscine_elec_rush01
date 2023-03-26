#ifndef I2C_EXPANDER_H
#define I2C_EXPANDER_H

#include "i2c.h"
#define EXPANDER_ADDR 0b00100000

#define SW3 0
#define LED_D9  3
#define LED_D10 2
#define LED_D11 1
#define SEGMENT_DIGIT_0 4
#define SEGMENT_DIGIT 1 5
#define SEGMENT_DIGIT_2 6
#define SEGMENT_DIGIT_3 7

#define SELECT_INPUT_PORT0 0
#define SELECT_INPUT_PORT1 1
#define SELECT_OUTPUT_PORT0 2
#define SELECT_OUTPUT_PORT1 3
#define SELECT_CONFIG_PORT0 6
#define SELECT_CONFIG_PORT1 7

#define EXPANDER_REGISTER_0 0
#define EXPANDER_REGISTER_1 1


#define SEGMENT_DOT (0b10000000)

void expander_init();
uint8_t expander_segment_select_digit(uint8_t select_digit);
uint8_t expander_get_register(uint8_t select_register, uint8_t* dest);
uint8_t expander_set_register(uint8_t select_register, uint8_t register_status);
uint8_t exp_set_pin(uint8_t led_id, uint8_t status);

void segment_putnbr(uint16_t nbr);
void segment_putnbr_fill_zero(uint16_t nbr);
void clear_segment();

#endif
