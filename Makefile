TARGET = thrust

MCU = atmega32u4
F_CPU = 16000000

SRC_DIR = src
SRC  := $(wildcard $(SRC_DIR)/*.cpp)
OBJ  := $(SRC:%.cpp=%.o)

CFLAGS = -Wall -g -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I include

all: $(TARGET).hex

%.hex: %.elf
	avr-objcopy -O ihex $< $@

%.elf: $(OBJ)
	avr-g++ $(CFLAGS) -o $@ $^

%.o: %.cpp
	avr-g++ $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ) $(TARGET).hex

reset:
	tools/reset.sh

test:
	arduino --upload others/test/test.ino --port /dev/ttyACM0 --board arduino:avr:micro #--verbose-upload #-v

upload:
	tools/upload

burn: $(TARGET).hex
	tools/upload $<
