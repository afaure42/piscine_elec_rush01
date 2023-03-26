#ifndef RUSH_H
 #define RUSH_H

// DEFINES
 #ifndef F_CPU
  #define F_CPU 16000000UL
 #endif
 #ifndef UART_BAUDRATE
  #define UART_BAUDRATE 115200
 #endif

// HEADERS

 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <util/delay.h>
 #include "i2c.h"
 #include "i2c_expander.h"
 #include "uart.h"

#endif
