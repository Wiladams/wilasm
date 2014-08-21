code
signed_divide 
; effectively zero a4 as top bit will be shifted out later 
	ANDS    a4, a1, #&80000000 
	RSBMI   a1, a1, #0 
	EORS    ip, a4, a2, ASR #32 
; ip bit 31 = sign of result 
; ip bit 30 = sign of a2 
	RSBCS   a2, a2, #0

; central part is identical code to udiv 
; (without MOV a4, #0 which comes for free as part of signed 
; entry sequence) 
	MOVS    a3, a1 
	BEQ     divide_by_zero
just_l 
; justification stage shifts 1 bit at a time 
	CMP     a3, a2, LSR #1 
	MOVLS   a3, a3, LSL #1 
; NB: LSL #1 is always OK if LS succeeds 
	BLO     s_loop

div_l
	CMP     a2, a3 
	ADC     a4, a4, a4 
	SUBCS   a2, a2, a3

	TEQ     a3, a1 
	MOVNE   a3, a3, LSR #1

	BNE     s_loop2 
	MOV     a1, a4
	MOVS    ip, ip, ASL #1 
	RSBCS   a1, a1, #0 
	RSBMI   a2, a2, #0

	MOV		pc, lr
