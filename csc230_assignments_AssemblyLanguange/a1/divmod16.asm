;
; csc225 assi q2.asm
;
; Created: 2018/5/31 0:24:54
; Author : Xu Wamg
;


; Replace with your application code
; divmod16.asm
; CSC 230 - Summer 2018
;
; Starter code for assignment 1
;
; B. Bird - 05/13/2018

.cseg
.org 0

	; Initialization code
	; Do not move or change these instructions or the registers they refer to. 
	; You may change the data values being loaded.
	; The default values set A = 0x3412 and B = 0x0003
	ldi r16, 0x47 ; Low byte of operand A
	ldi r17, 0xcd ; High byte of operand A
	ldi r18, 0x57 ; Low byte of operand B
	ldi r19, 0x68 ; High byte of operand B
	
	; Your task: Perform the integer division operation A/B and store the result in data memory. 
	; Store the 2 byte quotient in DIV1:DIV0 and store the 2 byte remainder in MOD1:MOD0.
	
	
	; ... Your code here ...
	clr r20
	clr r21
	mov r22,r16
	mov r23,r17
	;///////////if A<B or A=B
	cp r17,r19
	brlo end
	breq LOW_B
	rjmp normal_stat
;/////////////////////
	LOW_B:
		cp r16,r18
		brlo end
		breq A_Equals_B

;////////////////// A>B
normal_stat:
	clr r0
	ldi r24,0x01
	loop: 
		sub r22,r18
		sbc r23,r19
		add r20,r24
		adc r21,r0

		cpi r23,0
		breq lowBits
		cp r23,r19
		brsh loop
		brlo end
	lowbits:
		cp r22,r18
		brsh loop
		rjmp end

	A_Equals_B:            ;A=B
		ldi r20,0x01
		clr r21
		clr r22
		clr r23
	end:                  
		sts DIV0,r20
		sts DIV1,r21
		sts MOD0,r22
		sts MOD1,r23
	
	
	; End of program (do not change the next two lines)
stop:
	rjmp stop
	
; Do not move or modify any code below this line. You may add extra variables if needed.
; The .dseg directive indicates that the following directives should apply to data memory
.dseg 
.org 0x200 ; Start assembling at address 0x200 of data memory (addresses less than 0x200 refer to registers and ports)

DIV0:	.byte 1 ; Bits  7...0 of the quotient
DIV1:	.byte 1 ; Bits 15...8 of the quotient
MOD0:	.byte 1 ; Bits  7...0 of the remainder
MOD1:	.byte 1 ; Bits 15...8 of the remainder
