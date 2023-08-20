;
; AssemblerApplication1.asm
;
; Created: 7/30/2023 1:21:44 PM
; Author : asere
;


; Replace with your application code
; AVR
; [lable:] mnemonic [operands] [;comment]
; 
	; 4 bits -> 0 -> 15
	ldi r16,0xF0
; where? and what?
;   1    2    3    4 
; 1110 1111 0000 0000
;  E  F 0 0
; 00 EF
; flash
; 0 -> 1110 1111 0000 0000
; RAM
; 16 -> 1111 0000
