/*
 * LCD_1602A.c
 *
 *  Created on: Jul 28, 2019
 *      Author: asere
 */

#include <avr/io.h>
#include "../common.h"
#include <util/delay.h>
#include "LCD_1602A.h"
#include <math.h>

void LCD_Out (uint8_t c );
bool_t Read_Busy_Bit (void );

/*
 * Initialization routine as given in the ST7066U datasheet
 */
void LCD_Init ( void ) {
	//Initializing LCD Port directions as all output initially
	LCD_DATA_PORT_DIR |= (1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7);
	LCD_CONT_PORT_DIR |= (1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN);


    // Give some time to the LCD to start function properly
    _delay_ms(40);

    // Step 1
    // Send reset signal to the LCD
    WRINS_ONCE(0x03); //Function Reset, set to 8 bit initially according to datasheet
    _delay_ms(1); // wait for > 37 us


    // Step 2
    // Set interface data length to 4 bits, number of display lines to 2 and font to 5x8 dots
    WRINS_NOCHK(0x28); // 00101000
    _delay_ms(1); // wait for >37 us

    // Step 3, repease setp 2
    // Set interface data length to 4 bits, number of display lines to 2 and font to 5x8 dots
    WRINS_NOCHK(0x28); // 00101000
    _delay_ms(1); // wait for >37 us

    // Step 4
    // Turn Cursor off - Display On - Blink off
    WRINS_CHK(0x0C);
    _delay_ms(1); // wait for >37 us

    // Step 5
    // Clear Display
    WRINS_CHK(0x01);
    _delay_ms(2); // wait for >1.52 ms

    // Step 6
    // Entry Mode Set
    WRINS_CHK(0x06);
    _delay_ms(1); // wait for >37 us

}
// Write Instruction low byte only
void LCD_WriteInst ( unsigned char c ) {

    LCD_CONT_OUT_PORT &= ~(1 << LCD_RS); // => RS = 0 Instruction
    LCD_CONT_OUT_PORT &= ~(1 << LCD_RW); // => WR = 0 Write operation

    LCD_CONT_OUT_PORT |= (1 << LCD_EN);    // => E = 1
    LCD_Out(c);
    _delay_us(1); // minimum time for Enable Pulse Width Tpw
    LCD_CONT_OUT_PORT &= ~(1 << LCD_EN); // => E = 0

    _delay_us(2); // minimum time between two consecutive EN settings according to the datasheet is 1200 ns

}
// write the low nibble only
void LCD_Out (uint8_t c ) {
		uint8_t DataBits;
		DataBits = 0xF0;
		if(c&0x01)
			DataBits |= (1<<LCD_D4);
		if(c&0x02)
			DataBits |= (1<<LCD_D5);
		if(c&0x04)
			DataBits |= (1<<LCD_D6);
		if(c&0x08)
			DataBits |= (1<<LCD_D7);

		LCD_DATA_OUT_PORT |= (DataBits&0x0F);
		LCD_DATA_OUT_PORT &= (DataBits|0xF0);
}
bool_t Read_Busy_Bit (void ) {
    bool_t c = true;
    uint8_t PIN_Data;
    PIN_Data = PINC;

    c = ( PIN_Data & 0b00000001 )?true:false;
    return c;
}

// Wait for Busy flag to change to zero
void LCD_Wait_For_Busy ( void ) {
	bool_t busyFlag = true;

	do{

	// Change LCD port direction to input
		// first insure pull up is no set by clearing the port
		LCD_DATA_OUT_PORT &= ~((1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7));
		asm("nop");
		LCD_DATA_PORT_DIR &= ~((1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7));

	_delay_us(2);

	LCD_CONT_OUT_PORT &= ~(1 << LCD_RS); // => RS = 0 Instruction
    LCD_CONT_OUT_PORT |= (1 << LCD_RW); // Read operation (Set RW)


    LCD_CONT_OUT_PORT |= (1 << LCD_EN);    // => E = 1
    _delay_us(1);

    LCD_CONT_OUT_PORT &= ~(1 << LCD_EN); // => E = 0
    asm("nop");
    busyFlag = Read_Busy_Bit();
    LCD_CONT_OUT_PORT &= ~(1 << LCD_RW); // Write operation (Set RW)



    // Read the second nibble
    _delay_us(2); // min time between two writes or reads
    LCD_CONT_OUT_PORT &= ~(1 << LCD_RS); // => RS = 0 Instruction
    LCD_CONT_OUT_PORT |= (1 << LCD_RW); // Read operation (Set RW)

    LCD_CONT_OUT_PORT |= (1 << LCD_EN);    // => E = 1
    _delay_us(1);
    // don't read the data this time
    LCD_CONT_OUT_PORT &= ~(1 << LCD_EN); // => E = 0

    LCD_CONT_OUT_PORT &= ~(1 << LCD_RW); // Reset RW PIN
    LCD_CONT_OUT_PORT &= ~(1 << LCD_RS); // Reset RS PIN


    LCD_DATA_PORT_DIR |= (1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7);
    _delay_us(2);
	}while(busyFlag);

}


// Write Data to LCD
void LCD_putc ( char c ) {

	// wait for Busy flag to clear
	LCD_Wait_For_Busy();
	// Start write data into DDRAM current address
	_delay_us(2);
	LCD_CONT_OUT_PORT |= (1 << LCD_RS);   // => RS = 1
	LCD_CONT_OUT_PORT &= ~(1 << LCD_RW); // => WR = 0 Write operation (clear RW)
	LCD_Out((c & 0xF0) >> 4);    //Data transfer

	LCD_CONT_OUT_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_CONT_OUT_PORT &= ~(1 << LCD_EN);
	_delay_us(2); // wait between two consecutive writes

	LCD_Out(c & 0x0F);
	LCD_CONT_OUT_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_CONT_OUT_PORT &= ~(1 << LCD_EN);

	_delay_us(2);
    LCD_CONT_OUT_PORT &= ~(1 << LCD_RW); // Reset RW PIN
    LCD_CONT_OUT_PORT &= ~(1 << LCD_RS); // Reset RS PIN
	//LCD_Out(0xFF); // reset out port pins
}
void LCD_putNum(uint32_t number){
	char str[6];
	uint8_t i;
	uint8_t numOfDigits=0;
	str[5] = '\0';
	////
	for(i=0;i<5;i++)
	{
		if(number < (pow(10,i+1)))
		{
			str[i+1]='\0';
			numOfDigits = i+1;
			break;
		}
		//str[i] = ((number % (uint32_t)pow(10,i+1))/((uint32_t)pow(10,i)))+48;
	}
	for(i=numOfDigits;i>0;i--){
		LCD_putc((char)((number % (uint32_t)(pow(10,i)+0.5))/((uint32_t)pow(10,i-1)))+48);
	}
	//LCD_putrs(str);
}
// Send string to the LCD
void LCD_putrs ( const char *a ) {

    for ( int i = 0; a[i] != '\0'; ++i ) {
    	if(a[i] == '\n')
    		LCD_Seond_Line();
    	else
    		LCD_putc(a[i]);
    }

}
// Set DDRAM Address, 7 bit address only
void SendLCD_DDRAM_ADD(uint8_t Address){
	uint8_t command;
	uint8_t code = 0;
	code |= (1<<7); // this is the code to write in the DDRAM address space in the LCD
	command = code | Address;
	WRINS_CHK(command);
}
// the CGRAM address is only 5 bits, other bits will be ignored
void SendLCD_CGRAM_ADD(uint8_t Address){
	uint8_t command;
	uint8_t code = 0;
	Address &= ~(3<<6);
	code |= (1<<6); // this is the code to write in the CGRAM address space in the LCD
	command = code | Address;
	WRINS_CHK(command);
}
// column (0 till 16)
//line: line number    (0 for first line, 1 for second line)
void LCD_GotoXY(uint8_t column,uint8_t line){
	uint8_t position = 0x00;
	position |= ((0x01&line)<<LINE_BIT_POS);
	if(column < 16){
		position+= column;
	}
	LCD_Cmd((position|ADD_COMMAND));
}
