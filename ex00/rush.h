#ifndef RUSH_H
 #define RUSH_H

// DEFINES
 #ifndef F_CPU
  #define F_CPU 16000000UL
 #endif
 #ifndef UART_BAUDRATE
  #define UART_BAUDRATE 115200
 #endif

#define LED_D1 PB0
#define LED_D2 PB1
#define LED_D3 PB2
#define LED_D4 PB4
// HEADERS

 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <util/delay.h>
 #include "i2c.h"
 #include "i2c_expander.h"
 #include "uart.h"
 #include "modes.h"

#endif
