/*
 * LCD_1602A.h
 *
 *  Created on: Jul 28, 2019
 *      Author: asere
 */

#ifndef LCD2_LCD_1602A_H_
#define LCD2_LCD_1602A_H_

#define LCD_DATA_OUT_PORT 	PORTC
#define LCD_CONT_OUT_PORT 	PORTC
#define LCD_DATA_PORT_DIR	DDRC
#define LCD_CONT_PORT_DIR	DDRC
#define LCD_DATA_IN_PORT	PINC

#define LCD_D7		PC0
#define LCD_D6		PC1
#define LCD_D5		PC2
#define LCD_D4		PC3
#define LCD_EN		PC4
#define LCD_RW		PC5
#define LCD_RS		PC6
/// internal defines
#define LINE_BIT_POS 6
#define ADD_COMMAND 0b10000000
//	LCD_Wait_For_Busy();
#define WRINS_CHK(c)				\
do {								\
	LCD_Wait_For_Busy();			\
	LCD_WriteInst((c&0xF0)>>4);				\
	LCD_WriteInst(c&0x0F);					\
} while(0)
#define WRINS_NOCHK(c)				\
do {								\
	LCD_WriteInst((c&0xF0)>>4);				\
	LCD_WriteInst(c&0x0F);					\
} while(0)
#define WRINS_ONCE(c)				\
do {								\
	LCD_WriteInst(c);				\
} while(0)

#define LCD_Clear()	\
do{					\
	WRINS_CHK(0x01);	\
	_delay_ms(2);	\
}while(0)

#define LCD_First_Line()	\
do{							\
	WRINS_CHK(0x80);		\
	_delay_ms(1);			\
}while(0)
#define LCD_Seond_Line()	\
do{							\
	WRINS_CHK(0xC0);			\
	_delay_ms(1);			\
}while(0)
#define LCD_Cmd(x)			\
do{							\
	WRINS_CHK(x);			\
	_delay_ms(1);			\
}while(0)
#define LCD_Decrement_Cursor() LCD_Cmd(0x04)
#define LCD_Increment_Cursor() LCD_Cmd(0x05)
#define LCD_Shift_Display_Right() LCD_Cmd(0x06)
#define LCD_Shift_Display_Left() LCD_Cmd(0x07)
#define LCD_Shift_Right() LCD_Cmd(0x1C)
#define LCD_Shift_Left() LCD_Cmd(0x18)
// Initializes the LCD (See LCD struct)

// [Internal use only] Write instruction byte to the LCD
void LCD_WriteInst ( unsigned char c );
void LCD_Wait_For_Busy(void);
void LCD_Init(void);
void LCD_putc ( char c ) ;
void LCD_putNum(uint32_t number);
// Prints a string on the LCD that is allocated on the program memory
void LCD_putrs ( const char *a );
void SendLCD_CGRAM_ADD(uint8_t Address);
void SendLCD_DDRAM_ADD(uint8_t Address);
void LCD_GotoXY(uint8_t column,uint8_t line);
#endif /* LCD2_LCD_1602A_H_ */
