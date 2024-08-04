#define F_CPU 12000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>

#define BIT_SET(REG,POS)	REG |= (1<<POS) 
#define BIT_CLR(REG,POS) 	REG &= ~(1<<POS)
#define BIT_FLIP(REG,POS)   REG ^= (1<<POS)
#define FLIP20 50
#define FLIP40 25

volatile uint8_t OS_Counter;

void timer1Init(void);
void task_init(void);
void task1_20ms(void);
void task2_40ms(void);
int main(void){
	// Initialize the timer
	timer1Init();
	task_init();
	while(1){
		if(OS_Counter % 20 == 0){
			task1_20ms();
		}
		if(OS_Counter % 40 == 0){
			task2_40ms();
		}
	}
}

void timer1Init(void){
	TCCR1B |= (1 << WGM12); // Set Timer1 to CTC mode
	
	// 12 Mhz clock, 1 msecond = 12,000,000 cycles / 1000 (millisecond) = 12,000
	// Prescalar 8: 12,000 / 8 = 1,500
	OCR1A = 1500 - 1; // 1499
	
	// Enable the interrupt of OCR1A
	TIMSK |= (1<<  OCIE1A);
	
	// set the prescalar to 8
	TCCR1B |= (1<<CS11) ;
	
	
	sei();
	
}


// this interrupt will fire every ~1 ms (500hz)
ISR(TIMER1_COMPA_vect){
	OS_Counter++;
	if(OS_Counter >= 200){
		OS_Counter = 0;
	}
}

void task_init(void){
	// set PINB0 as output
	DDRB |= (1<< PINB0);
	DDRB |= (1<< PINB2);
	// clear PINB0
	PORTB &= ~(1<<PINB0);
	PORTB |= (1<<PINB1);
}

void task1_20ms(void){
	static int counter;
	
	if (counter >= FLIP20){
		BIT_FLIP(PORTB,1);
		counter = 0;
	}
		
	counter ++;
	
}
void task2_40ms(void){
	static int counter;
	
	if (counter >= FLIP40){
		BIT_FLIP(PORTB,0);
		counter = 0;
	}
		
	counter ++;
	
}