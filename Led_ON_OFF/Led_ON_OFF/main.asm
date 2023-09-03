;
; Led_ON_OFF.asm
;
; Created: 8/20/2023 1:13:10 PM
; Author : asere
;


; Replace with your application code
init:
	 SBI $1A,0 ; DDRA <- 0b0000-0001  Set as output for PORTA0
start:
	SBI $1B,0 ; PORTA <- 0b0000-0001  Set PIN0 in PORTA as 5V

;Creating a loop1 
LDI R16, 255 ; initialize the register
loop11:
;Creating a loop2 
LDI R17, 255 ; initialize the register
loop22:
	DEC R17   ; decrement R16 = R16 - 1 
	BRNE loop22 ; branch if not equal zero to loop (conditional branching)
; End of loop2
	DEC R16   ; decrement R16 = R16 - 1 
	BRNE loop11 ; branch if not equal zero to loop (conditional branching)
; End of loop1

	CBI $1B,0 ;PORTA <- 0b0000-0000  clear PIN0 in PORTA as 0V

;Creating a loop1 
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
; End of loop1
    rjmp start  ;this is my comment

