MAKE := make
clean:
	rm -fd OS1.o
	rm -fd OS1.elf
	rm -fd OS1.hex
	
all: OS1.hex

OS1.hex: OS1.elf
	avr-objcopy -O ihex -R .eeprom OS1.elf OS1.hex

OS1.elf: OS1.o
	avr-gcc  -o OS1.elf OS1.o
	
OS1.o: OS1.c
	avr-gcc -mmcu=atmega32 -Os -c OS1.c -o OS1.o