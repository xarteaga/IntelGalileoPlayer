#
# Written by Amit Patwardhan Nov-2013
# Use as you see fit
#

BINARY = main
MAIN = $(BINARY).cpp
ARDUINO_VER = 153

# path

# change next line to point where arduino and proj folders exist
ABS_PATH = ..
BIN_PATH = $(ABS_PATH)/arduino-1.5.3/hardware/tools/sysroots/x86_64-pokysdk-linux/usr/bin/i586-poky-linux-uclibc/
SYS_ROOT = $(ABS_PATH)/arduino-1.5.3/hardware/tools/sysroots/i586-poky-linux-uclibc
ARDUINO_PATH = $(ABS_PATH)/arduino-1.5.3/hardware/arduino/x86/cores/arduino
LIBS_PATH = $(ABS_PATH)/arduino-1.5.3/hardware/arduino/x86/libraries
VARIANT = $(ABS_PATH)/arduino-1.5.3/hardware/arduino/x86/variants/galileo_fab_d

# tools

PREFIX = i586-poky-linux-uclibc-

CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
LD = $(PREFIX)gcc
AR = $(PREFIX)ar
OBJCOPY = $(PREFIX)objcopy
SIZE = $(PREFIX)size
STRIP = $(PREFIX)strip

# flags

COM_FLAGS = -m32 -march=i586 --sysroot=$(SYS_ROOT) -c -g -Os -w -ffunction-sections -fdata-sections -MMD -DARDUINO=$(ARDUINO_VER) -lpthread 
CFLAGS = $(COM_FLAGS)
CXXFLAGS = $(COM_FLAGS) -fno-exceptions

LDFLAGS = -m32 -march=i586 --sysroot=$(SYS_ROOT) -Os -Wl,--gc-sections -lpthread

# modules
# does not have all the files change as per project
C_MODULES = $(ARDUINO_PATH)/wiring_digital.c
C_MODULES += $(ARDUINO_PATH)/wiring_analog.c
C_MODULES += $(ARDUINO_PATH)/fast_gpio_sc.c  
C_MODULES += $(ARDUINO_PATH)/interrupt.c  
C_MODULES += $(ARDUINO_PATH)/sysfs.c  
C_MODULES += $(ARDUINO_PATH)/i2c.c     
C_MODULES += $(ARDUINO_PATH)/mux.c        
C_MODULES += $(ARDUINO_PATH)/trace.c  

CXX_MODULES = $(ABS_PATH)/arduino-1.5.3/hardware/arduino/x86/variants/galileo_fab_d/variant.cpp
CXX_MODULES += $(ARDUINO_PATH)/RingBuffer.cpp
CXX_MODULES += $(ARDUINO_PATH)/TTYUART.cpp
CXX_MODULES += $(ARDUINO_PATH)/UtilTime.cpp
CXX_MODULES += $(ARDUINO_PATH)/Print.cpp
CXX_MODULES += $(ARDUINO_PATH)/Stream.cpp   
CXX_MODULES += $(ARDUINO_PATH)/WString.cpp
CXX_MODULES += $(ARDUINO_PATH)/WMath.cpp
CXX_MODULES += $(ARDUINO_PATH)/IPAddress.cpp
CXX_MODULES += $(LIBS_PATH)/Wire/Wire.cpp
CXX_MODULES += Singer.cpp

INCS =	-I$(ARDUINO_PATH) \
	-I$(ABS_PATH)/arduino-1.5.3/hardware/arduino/x86/variants/galileo_fab_d\
	-I$(LIBS_PATH)/Wire/

COBJS = $(C_MODULES:.c=.o)
CXXOBJS = $(CXX_MODULES:.cpp=.o)
OBJS = $(CXXOBJS) $(COBJS)

# rules

all: elf strip size
	@echo "Done"

elf: $(BINARY).o $(OBJS)
	$(BIN_PATH)/$(CXX) -o $(BINARY).elf $(BINARY).o $(OBJS) $(LDFLAGS) -lm -lpthread

%.o: %.c
	$(BIN_PATH)/$(CC) $< -o $@ $(INCS) $(CFLAGS)

%.o: %.cpp
	$(BIN_PATH)/$(CXX) $< -o $@ $(INCS) $(CXXFLAGS)

.PHONY: strip size clean flash

strip: $(BINARY).elf
	$(BIN_PATH)/$(STRIP) $(BINARY).elf

size: $(BINARY).elf
	$(BIN_PATH)/$(SIZE) $(BINARY).elf
#@echo "of 262,144 bytes maximum"
clean:
	rm -f $(BINARY).o
	rm -f $(OBJS)
	rm -f *.d
	rm -f *.elf
	rm -f *.hex

# changes in clupload_linux.sh
# replace
# path_to_exe=$1
# fixed_path=${path_to_exe//\\/\/}
# with
# fixed_path=$1

# on GNU/Linux
# sudo make flash
flash: $(BINARY).elf
	@echo "flash"
	bash $(ARDUINO_PATH)/../../tools/izmir/clupload_linux.sh $(ABS_PATH)/arduino-1.5.3/hardware/tools main.elf /dev/ttyACM0
