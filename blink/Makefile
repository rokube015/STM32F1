SHELL = /bin/sh

TARGET_ARCH = -mcpu=cortex-m3 -mtune=cortex-m3 -mthumb
MESSAGES = -fmessage-length=0

STD_LIB_DIR				= ./lib
SYSTEM_DIR  			= ./system
CMSIS_DIR        	= $(SYSTEM_DIR)/CMSIS
DRIVER_INC_DIR   	= $(STD_LIB_DIR)/inc
DRIVER_SRC_DIR   	= $(STD_LIB_DIR)/src

STARTUP_DIR      	= $(SYSTEM_DIR)/startup
INCLUDE_DIR 			= ./inc
SRC_DIR						= ./src
OBJECT_DIR 			 	= ./obj

INCLUDE_DIRS = 	-I ./ \
								-I $(INCLUDE_DIR) \
								-I $(STARTUP_DIR) \
							 	-I $(CMSIS_DIR) 	\
							 	-I $(SYSTEM_DIR) 	\
							 	-I $(DRIVER_INC_DIR) 

MAIN_OUT = bin/main.elf
MAIN_MAP = $(MAIN_OUT:%.elf=%.map)
MAIN_BIN = $(MAIN_OUT:%.elf=%.bin)
MAIN_HEX = $(MAIN_OUT:%.elf=%.hex)
MAIN_DFU = $(MAIN_OUT:%.elf=%.dfu)

MAIN_OBJS = $(sort \
						$(patsubst %.cpp,%.o,$(wildcard *.cpp)) \
						$(patsubst %.c,%.o,$(wildcard *.c)) \
						$(patsubst %.s,%.o,$(wildcard *.s)) \
						$(patsubst %.cpp,%.o,$(wildcard src/*.cpp)) \
						$(patsubst %.c,%.o,$(wildcard src/*.c)) \
						$(patsubst %.s,%.o,$(wildcard src/*.s)) \
						$(patsubst %.c,%.o,$(wildcard $(SYSTEM_DIR)/*.c)) \
						$(patsubst %.c,%.o,$(wildcard $(CMSIS_DIR)/*.c)))

LIB_OBJS = $(sort \
					 $(patsubst %.c,%.o,$(wildcard $(DRIVER_SRC_DIR)/*.c)))

libstm32f1 = ./lib/lib.a


BOARD_OPTS = -DSTM32F10X_MD
FIRMWARE_OPTS = -DUSE_STDPERIPH_DRIVER

WARNINGS	=	-Wall 

WARNINGS_CXX = -Weffc++ $(W_OLD_STYLE_CAST)

CPPFLAGS = $(DEBUG_MACRO)

CC = arm-none-eabi-gcc
COMPILE_OPTS = -fsigned-char $(WARNINGS) $(FIRMWARE_OPTS) $(TARGET_OPTS) $(MESSAGES) $(INCLUDE_DIRS)
CFLAGS = -std=gnu99 $(COMPILE_OPTS) $(BOARD_OPTS) $(FIRMWARE_OPTS)

CXX = arm-none-eabi-g++
CXXFLAGS = -std=gnu++98 $(COMPILE_OPTS) $(WARNINGS_CXX) $(F_NO_EXCEPTIONS)

AS = $(CC) -x assembler-with-cpp -c $(TAGET_ARCH)
ASFLAGS = $(COMPILE_OPTS)

LD = $(CC)
LDFLAGS = -Wl,--gc-sections,-Map=$(MAIN_MAP),-cref -T $(LD_SCRIPT) $(INCLUDE_DIRS) -L $(LIBRARY_DIRS) 

AR = arm-none-eabi-ar
ARFLAGS = cr

OBJCOPY = arm-none-eabi-objcopy
OBJCOPY_BIN_FLAGS = -O binary
OBJCOPY_HEX_FLAGS = -O ihex

LD_SCRIPT = $(SYSTEM_DIR)/stm32_flash.ld
STARTUP_SCRIPT = $(STARTUP_DIR)/startup_stm32f10x_ld.s

#all

.PHONY: all clean clean_lib
all: $(MAIN_BIN) $(MAIN_HEX)

#main
START_UP = $(OBJECT_DIR)/startup.o
$(MAIN_OUT): $(MAIN_OBJS) $(START_UP) $(libstm32f1)
	$(LD) $(LDFLAGS) $(TARGET_ARCH) -o $@ $^

$(MAIN_OBJS): $(wildcard *.h) $(wildcard inc/*.h)

$(MAIN_BIN): $(MAIN_OUT)
	$(OBJCOPY) $(OBJCOPY_BIN_FLAGS) $< $@

$(MAIN_HEX): $(MAIN_OUT)
	$(OBJCOPY) $(OBJCOPY_HEX_FLAGS) $< $@

$(libstm32f1): $(LIB_OBJS)
	$(AR) cr $@ $^

$(START_UP): $(STARTUP_SCRIPT)
	$(AS) -o $@ $^
	
$(OBJECT_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(SYSTEM_DIR)/*.o
	rm -f $(CMSIS_DIR)/*.o
	rm -f ./src/*.o
	rm -f ./obj/*.o

clean_lib:
	rm $(DRIVER_SRC_DIR)/*.o
	rm ./lib/*.a
