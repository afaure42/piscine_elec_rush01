#ifndef I2C_EXPANDER_H
#define I2C_EXPANDER_H

#include "i2c.h"


void expander_init();
void expander_segment_select_digit(uint8_t select_digit);
uint8_t expander_get_register(uint8_t select_register);
void expander_set_register(uint8_t select_register, uint8_t register_status);
void segment_putnbr(uint16_t nbr);
void segment_putnbr_fill_zero(uint16_t nbr);
void clear_segment();

#endif
