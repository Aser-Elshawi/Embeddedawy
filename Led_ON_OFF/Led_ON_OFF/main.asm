;
; Led_ON_OFF.asm
;
; Created: 8/20/2023 1:13:10 PM
; Author : asere
;

.INCLUDE <m32adef.inc>

; Replace with your application code
; Interrupt vector table
.ORG 0x000
	JMP init
	; PD2 interrupt
	JMP int0_isr
	; PD3 interrupt
	JMP int1_isr

.DB 0x55, 0x55
.ORG 0x050
; initialize the stack pointer
init:
	LDI R16, LOW(RAMEND)
	OUT SPL,R16
	LDI R16, HIGH(RAMEND)
	OUT SPH,R16
	; intialize PORTB0 as an output
	SBI DDRB,  0
	; intialize PORTB1 as an output
	SBI DDRB,  1
	; configure the int0 pin PD2 as input
	CBI	  DDRD,2
	; configure the int0 pin PD2 as input
	CBI	  DDRD,3
	; configure int1 on falling edge, configure int0 on falling edge
	LDI R16, (1<<ISC11) | (1<<ISC01)
	OUT MCUCR, R16
	; set PD2 as pull up
	SBI   PORTD,2
	; set PD3 as pull up
	SBI   PORTD,3
	; enable int0 interrupt and enable int1 interrupt
	LDI   R16, (1<<int0) | (1<<int1)
	OUT	  GICR, R16
	; enable global interrupt mask
	LDI   R16, (1<<SREG_I)
	OUT	  SREG,R16

main:
	;add the Blinking LED application
	JMP	  main

; interrupt service routine
int0_isr:
	; execute the interrupt service routine
	; instructions
	; instructions
	SBI PORTB, 0
	CBI PORTB, 1
	RETI

int1_isr:
	; execute the interrupt service routine
	; instructions
	; instructions
	SBI PORTB, 1
	CBI PORTB, 0
	RETI

