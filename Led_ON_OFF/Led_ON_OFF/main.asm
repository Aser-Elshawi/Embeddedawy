;
; Led_ON_OFF.asm
;
; Created: 8/20/2023 1:13:10 PM
; Author : asere
;


; Replace with your application code
init:
    sbi $17,0  ; DDB0 -> 1, Set PORTB0 as an output
	sbi $18,0  ; PORTB0 -> 1, Set PORTB0 to 5V
start:  ; while(1)
	nop
    rjmp start  ;this is my comment
