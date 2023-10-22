.INCLUDE <m32adef.inc>

; Replace with your application code
; Interrupt vector table
.ORG 0x000
	JMP init
	; PD2 interrupt
	JMP int0_isr
.ORG 0x030
; initialize the stack pointer
init:
	LDI R16, LOW(RAMEND)
	OUT SPL,R16
	LDI R16, HIGH(RAMEND)
	OUT SPH,R16
	; intialize PORTA as an input
	LDI R16, $00
	OUT DDRA,R16
	; intialize PORTA as input PULL UP
	LDI R16, $FF
	OUT PORTA,R16
	; intialize PORTC0 as an output
	SBI DDRC,0
    
	; configure the int0 pin PD2 as input
	CBI	  DDRD,2
	; configure int1 on falling edge, configure int0 on falling edge
	LDI R16, (1<<ISC11) | (1<<ISC01)
	OUT MCUCR, R16
	; set PD2 as pull up
	SBI   PORTD,2
	; enable int0 interrupt and enable int1 interrupt
	LDI   R16, (1<<int0)
	OUT	  GICR, R16
	; enable global interrupt mask
	LDI   R16, (1<<SREG_I)
	OUT	  SREG,R16


main:
	

	RJMP	main


DELAY:
	LDI  R16,31 ; 1 cycle -> 99
LOOP: ; 6 in last loop
	DEC  R16  ; 1 cycle -> 98
	brne LOOP ; 2 cycle -> 96
	nop
ret ; 4

int0_isr:
	;SEND 0X41 ON UART
	;0B 0100 0001
	;SEND 0 FOR THE START BIT
	CBI PORTC, 0
	CALL DELAY ; 4 cycles

	;SEND BIT(0) 0
	CBI PORTC, 0
	CALL DELAY

	;SEND BIT(1) 1
	SBI PORTC, 0
	CALL DELAY

	;SEND BIT(2) 0
	CBI PORTC, 0
	CALL DELAY
	
	;SEND BIT(3) 0
	CBI PORTC, 0
	CALL DELAY

	
	;SEND BIT(4) 0
	CBI PORTC, 0
	CALL DELAY

	
	;SEND BIT(5) 0
	CBI PORTC, 0
	CALL DELAY

	
	;SEND BIT(6) 0
	CBI PORTC, 0
	CALL DELAY

	
	;SEND BIT(7) 1
	SBI PORTC, 0
	CALL DELAY

	
	;SEND STOP BIT
	SBI PORTC, 0
	CALL DELAY

	RETI