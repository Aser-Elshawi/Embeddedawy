;
; Led_ON_OFF.asm
;
; Created: 8/20/2023 1:13:10 PM
; Author : asere
;


; Replace with your application code
init:
	 ; INITIALIZATION SP
	LDI R16,$08
	OUT $3E,R16
	LDI R16,$2A
	OUT $3D,R16
	; set portA0 direction to output
	 SBI $1A,0 ; DDRA <- 0b0000-0001  Set as output for PORTA0
start:
	SBI $1B,0 ; PORTA <- 0b0000-0001  Set PIN0 in PORTA as 5V

	CALL DELAY
	CBI $1B,0 ;PORTA <- 0b0000-0000  clear PIN0 in PORTA as 0V
	CALL DELAY
    rjmp start  ;this is my comment

; subroutine
DELAY:
	LDI R18, 8
loop0:
	
	LDI R16, 255 ; initialize the register
loop1:
;Creating a loop2 
	LDI R17, 255 ; initialize the register
loop2:
	DEC R17   ; decrement R16 = R16 - 1 
	BRNE loop2 ; branch if not equal zero to loop (conditional branching)
; End of loop2
	DEC R16   ; decrement R16 = R16 - 1 
	BRNE loop1 ; branch if not equal zero to loop (conditional branching)
	DEC R18
	BRNE loop0;
; End of loop1
	RET