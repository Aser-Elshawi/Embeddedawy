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

	LDI	R16, 6
	LDI R17, 0
	call USART_Init

main:
	
	ldi	R16, 'A'
	call USART_Transmit
	

	RJMP	main

USART_Init:
; Set baud rate
	out UBRRH, r17
	out UBRRL, r16
; Enable receiver and transmitter
	ldi r16, (1<<RXEN)|(1<<TXEN)
	out UCSRB,r16
; Set frame format: 8data, 2stop bit
	ldi r16, (1<<URSEL)|(1<<USBS)|(1<<UCSZ1)|(1<<UCSZ0)
	out UCSRC,r16
	ret
; write the send byte to R16
USART_Transmit:
; Wait for empty transmit buffer
	sbis UCSRA,UDRE
	rjmp USART_Transmit
; Put data (r16) into buffer, sends the data
	out UDR,r16
ret
	
DELAY:
	LDI  R16,31 ; 1 cycle -> 99
LOOP: ; 6 in last loop
	DEC  R16  ; 1 cycle -> 98
	brne LOOP ; 2 cycle -> 96
	nop
ret ; 4

int0_isr:
	nop
	RETI