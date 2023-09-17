;
; Led_ON_OFF.asm
;
; Created: 8/20/2023 1:13:10 PM
; Author : asere
;


; Replace with your application code
init:
	 ; INITIALIZATION SP
	LDI R16,$04
	OUT $3E,R16
	LDI R16,$5F
	OUT $3D,R16
	
main:
; Load the SP data(address) into the Y register
	LDI   R29, 0x04
	LDI   R28, 0x5F
;  Read Rn Value
	LDI	  R16, 0x55
;  Write the Value in the SP pointing address
	ST	  Y,R16
; SP -> SP -1 (Increment Stack) Decrement Stack Pointer
	DEC   R28
; Load the X register with the absolute address of the SPL  (X -> SPL)
;	LDI   R27, 0x00
;	LDI   R26, 0x5D
; Load R18 -> (X)
;	ST    X, R28
	OUT   $3D,R28
	LDI   R16,33
	PUSH  R16
	PUSH  R16


