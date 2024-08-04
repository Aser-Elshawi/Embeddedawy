#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>

#define BIT_SET(REG,POS)	REG |= (1<<POS) 
#define BIT_CLR(REG,POS) 	REG &= ~(1<<POS)
#define BIT_FLIP(REG,POS)   REG ^= (1<<POS)

void timer1Init(void);
int main(void){
	// Initialize the timer
	timer1Init();
	DDRB = 0b11111111;
	PORTB = 0b00000000;
	while(1){
		
	}
}

void timer1Init(void){
	TCCR1B |= (1 << WGM12); // Set Timer1 to CTC mode
	
	// 1 Mhz clock, 1 second = 1000,000 cycles
	// Prescalar 64: 1,000,000 / 64 = 15,625
	OCR1A = 15625 - 1;
	
	// Enable the interrupt of OCR1A
	TIMSK |= (1<<  OCIE1A);
	
	// set the prescalar to 64
	TCCR1B |= (1<<CS11) | (1 << CS10);
	
	
	sei();
	
}

ISR(TIMER1_COMPA_vect){
	BIT_FLIP(PORTB,0);
}