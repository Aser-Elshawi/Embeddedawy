MAKE := make

# Makefile for building an AVR project for the ATmega32

# Target MCU
MCU = atmega32

# Compiler flags
CFLAGS = -mmcu=$(MCU) -Os


# Compiler and linker commands
CC = avr-gcc
OBJCOPY = avr-objcopy

# Source and target files
TARGET = OS1
SRC = $(TARGET).c
OBJ = $(TARGET).o
ELF = $(TARGET).elf
HEX = $(TARGET).hex

	
all: $(HEX)

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $(ELF) $(HEX)

# Rule to create elf file from object file
$(ELF): $(OBJ)
	$(CC) $(CFLAGS) -o $(ELF) $(OBJ)

# Rule to create object file from C source file
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)
	
	
# Clean up generated files
clean:
	rm -f $(OBJ) $(ELF) $(HEX)

# Phony targets
.PHONY: all clean