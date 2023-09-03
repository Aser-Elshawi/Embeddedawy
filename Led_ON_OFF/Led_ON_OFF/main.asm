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
	LDI R16,$5F
	OUT $3D,R16
start:
	LDI R17,4
	LDI R16,$55
loop:
	INC R16
	PUSH R16
	DEC R17
	BRNE loop
	LDI R17,4
loop2:
	POP R0
	DEC R17
	BRNE loop2

    rjmp start  ;this is my comment

