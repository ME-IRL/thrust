TARGET       = thrust

MCU          = atmega32u4
BOARD        = USER
F_CPU        = 16000000
F_USB        = $(F_CPU)
ARCH         = AVR8
OPTIMIZATION = s

SRC_DIR      = src
INC_DIR      = include

SRC          = $(wildcard $(SRC_DIR)/*.c) $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS) $(LUFA_SRC_PLATFORM)
LUFA_PATH    = ../lufa/LUFA

CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig -Iinclude
LD_FLAGS     =

AVRDUDE_PROGRAMMER = avrisp
AVRDUDE_PORT = /dev/arduino0
AVRDUDE_FLAGS = -b 19200

# Default target
all:

# Include LUFA-specific DMBS extension modules
DMBS_LUFA_PATH ?= $(LUFA_PATH)/Build/LUFA
include $(DMBS_LUFA_PATH)/lufa-sources.mk
include $(DMBS_LUFA_PATH)/lufa-gcc.mk

# Include common DMBS build system modules
DMBS_PATH      ?= $(LUFA_PATH)/Build/DMBS/DMBS
include $(DMBS_PATH)/core.mk
include $(DMBS_PATH)/cppcheck.mk
include $(DMBS_PATH)/doxygen.mk
include $(DMBS_PATH)/dfu.mk
include $(DMBS_PATH)/gcc.mk
include $(DMBS_PATH)/hid.mk
include $(DMBS_PATH)/avrdude.mk
include $(DMBS_PATH)/atprogram.mk
