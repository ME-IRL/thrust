TARGET = thrust

MCU = atmega32u4
F_CPU = 16000000
F_USB = $(F_CPU)
ARCH = AVR8
OPTIMIZATION = s

SRC_DIR = src
INC_DIR = include

SRC  := $(wildcard $(SRC_DIR)/*.cpp) $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS) $(LUFA_SRC_PLATFORM)
LUFA_PATH = ../lufa/LUFA

CC_FLAGS = -I $(INC_DIR) # -DUSE_LUFA_CONFIG -IConfig
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
