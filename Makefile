DEVICE = atmega32u4
TARGET = thrust
CLOCK = 8000000

SRC_DIR = src
SRC  := $(wildcard $(SRC_DIR)/*.cpp)
OBJ  := $(SRC:%.cpp=%.o)

CFLAGS = -Wall -g -Os -mmcu=$(DEVICE) -DF_CPU=$(CLOCK) -I include

all: $(TARGET).hex

%.hex: %.elf
	avr-objcopy -O ihex $< $@

%.elf: $(OBJ)
	avr-g++ $(CFLAGS) -o $@ $^

%.o: %.cpp
	avr-g++ $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ) $(TARGET).hex

test:
	tools/upload

burn: $(TARGET).hex
	tools/upload $<
