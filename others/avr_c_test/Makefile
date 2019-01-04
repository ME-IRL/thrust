PROGRAM = blink

CFLAGS = -Wall -I . -g -Os -mmcu=atmega328p 

all: $(PROGRAM).hex

%.hex: %.elf
	avr-objcopy -O ihex $< $@

%.elf: %.o
	avr-gcc $(CFLAGS) -o $@ $^

%.o: %.c
	avr-gcc $(CFLAGS) -o $@ -c $<

burn: $(PROGRAM).hex
	avrdude -F -v -c arduino -p m328p -P /dev/ttyACM0 -U flash:w:$(PROGRAM).hex
