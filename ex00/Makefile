NAME	=	main.hex
BIN		=	main.bin

DEVICE=atmega328p
F_CPU = 16000000UL
BAUDRATE=115200
PROGRAMMER= -c arduino -b$(BAUDRATE) -p $(DEVICE)

SRCS = main.c uart.c i2c.c i2c_expander.c adc.c mode_0.c mode_1.c mode_2.c \
		mode_3.c

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

CC = avr-gcc


CPPFLAGS	=	-Wall -Wextra -D F_CPU=$(F_CPU) -MMD -DUART_BAUDRATE=$(BAUDRATE)
CFLAGS = -Wall -Wextra -mmcu=$(DEVICE) -Os

all: flash

$(BIN):	$(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

%.o:	%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(BIN)
	avr-objcopy -O ihex ${BIN} ${NAME}

hex: $(NAME)

flash: $(NAME)
	avrdude $(PROGRAMMER) -P /dev/ttyUSB0 -U flash:w:$(NAME):i

# flash2: hex
# 	avrdude $(PROGRAMMER) -P /dev/ttyUSB1 -U flash:w:$(NAME):i
# 	avrdude $(PROGRAMMER) -P /dev/ttyUSB0 -U flash:w:$(NAME):i


clean:
	rm -rf $(OBJS) $(DEPS)
	
fclean: clean
	rm -rf $(BIN)
	rm -rf $(NAME)

re: clean
	make all

-include $(DEPS)

.PHONY: all, hex, flash, clean, re, fclean
