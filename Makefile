TARGET = thrust

MCU = atmega32u4
F_CPU = 16000000
F_USB = $(F_CPU)
ARCH = AVR8
OPTIMIZATION = s

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c) $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS) $(LUFA_SRC_PLATFORM)

LUFA_PATH = lufa/LUFA

#CC_FLAGS = -DUSE_LUFA_CONFIG_HEADER -IConfig
CC_FLAGS = 
LD_FLAGS = 

all:

include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk

#clean:
#	rm -rf $(OBJ) $(TARGET).hex

reset:
	tools/reset.sh

test:
	arduino --upload others/test/test.ino --port /dev/ttyACM0 --board arduino:avr:micro #--verbose-upload #-v

upload:
	tools/upload

burn: $(TARGET).hex
	tools/upload $<
