; a2_template.asm
; CSC 230 - Summer 2018
; 
; Some starter code for Assignment 2. You do not have
; to use this code if you'd rather start from scratch.
;
; B. Bird - 06/09/2018

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                        Constants and Definitions                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Stack pointer and SREG registers (in data space)
.equ SPH_DS = 0x5E
.equ SPL_DS = 0x5D
.equ SREG_DS = 0x5F

; Initial address (16-bit) for the stack pointer
.equ STACK_INIT = 0x21FF

; Port and data direction register definitions (taken from AVR Studio; note that m2560def.inc does not give the data space address of PORTB)
.equ DDRB_DS = 0x24
.equ PORTB_DS = 0x25
.equ DDRL_DS = 0x10A
.equ PORTL_DS = 0x10B

; Definitions for the analog/digital converter (ADC)
.equ ADCSRA_DS	= 0x7A ; Control and Status Register A
.equ ADCSRB_DS	= 0x7B ; Control and Status Register B
.equ ADMUX_DS	= 0x7C ; Multiplexer Register
.equ ADCL_DS	= 0x78 ; Output register (high bits)
.equ ADCH_DS	= 0x79 ; Output register (low bits)
; Definitions for button values from the ADC
; Some boards may use the values in option B
; The code below used less than comparisons so option A should work for both
; Option A (v 1.1)
;.equ ADC_BTN_RIGHT = 0x032
;.equ ADC_BTN_UP = 0x0FA
;.equ ADC_BTN_DOWN = 0x1C2
;.equ ADC_BTN_LEFT = 0x28A
;.equ ADC_BTN_SELECT = 0x352
; Option B (v 1.0)
.equ ADC_BTN_RIGHT = 0x032
.equ ADC_BTN_UP = 0x0C3
.equ ADC_BTN_DOWN = 0x17C
.equ ADC_BTN_LEFT = 0x22B
.equ ADC_BTN_SELECT = 0x316


; Definitions of the special register addresses for timer 0 (in data space)
.equ GTCCR_DS = 0x43
.equ OCR0A_DS = 0x47
.equ OCR0B_DS = 0x48
.equ TCCR0A_DS = 0x44
.equ TCCR0B_DS = 0x45
.equ TCNT0_DS  = 0x46
.equ TIFR0_DS  = 0x35
.equ TIMSK0_DS = 0x6E

; Definitions of the special register addresses for timer 1 (in data space)
.equ TCCR1A_DS = 0x80
.equ TCCR1B_DS = 0x81
.equ TCCR1C_DS = 0x82
.equ TCNT1H_DS = 0x85
.equ TCNT1L_DS = 0x84
.equ TIFR1_DS  = 0x36
.equ TIMSK1_DS = 0x6F

; Definitions of the special register addresses for timer 2 (in data space)
.equ ASSR_DS = 0xB6
.equ OCR2A_DS = 0xB3
.equ OCR2B_DS = 0xB4
.equ TCCR2A_DS = 0xB0
.equ TCCR2B_DS = 0xB1
.equ TCNT2_DS  = 0xB2
.equ TIFR2_DS  = 0x37
.equ TIMSK2_DS = 0x70

.cseg
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                          Reset/Interrupt Vectors                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.org 0x0000 ; RESET vector
	jmp main_begin
	
.org 0x001e
	jmp TIMER2_OVERFLOW_ISR
	
; Add interrupt handlers for timer interrupts here. See Section 14 (page 101) of the datasheet for addresses.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                               Main Program                                  ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; According to the datasheet, the last interrupt vector has address 0x0070, so the first
; "unreserved" location is 0x0074
.org 0x0074
main_begin:
	
	ldi r20,1;ADC judge mode--regular
	ldi r21,1;ADC judge delay--1 second
	; Initialize the stack
	ldi r16, high(STACK_INIT)
	sts SPH_DS, r16
	ldi r16, low(STACK_INIT)
	sts SPL_DS, r16
	
	ldi r16,0
	sts SELECT_BUTTON_COUNTER, r16
	; Set up the ADC
	; Set up ADCSRA (ADEN = 1, ADPS2:ADPS0 = 111 for divisor of 128)
	ldi	r16, 0x87
	sts	ADCSRA_DS, r16
	; Set up ADCSRB (all bits 0)
	ldi	r16, 0x00
	sts	ADCSRB_DS, r16
	; Set up ADMUX (MUX4:MUX0 = 00000, ADLAR = 0, REFS1:REFS0 = 1)
	ldi	r16, 0x40
	sts	ADMUX_DS, r16
	;;;;;;;;;;;;;;;;;;;;;
	
	ldi r16, 0xff
	sts DDRB_DS,r16
	sts DDRL_DS,r16
	
	ldi r16, 0
	sts OVERFLOW_INTERRUPT_COUNTER, r16
	sts STEP_COUNTER, r16
	
	call TIMER2_SETUP
	sei
stop:
	rjmp stop
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
TIMER2_SETUP:
	push r16
	
	ldi r16, 0x0000
	sts TCCR2A_DS, r16
	ldi r16, 0x06
	sts TCCR2B_DS,r16
	ldi r16, 0x01
	sts TIMSK2_DS, r16
	sts TIFR2_DS, r16
	
	pop r16
	ret
	
TIMER2_OVERFLOW_ISR:
	push r16
	push r17
	push r18
	push r19
	;push r20
	;push r21
	push r22
	push r23
	push r24
	push r25
	push r26
	push r27
	push r28
	push r29
	push r30
	push r31
	push r0
	push r1
	lds r16, SREG_DS ; Load the value of SREG into r16
	push r16 ; Push SREG onto the stack
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;stack finish
	;ADC
	ldi	r30, low(ADC_BTN_SELECT)
	ldi	r31, high(ADC_BTN_SELECT)
	
	ldi r28,low(ADC_BTN_LEFT)
	ldi r29,high(ADC_BTN_LEFT)
	
	ldi r26,low(ADC_BTN_DOWN)
	ldi r27,high(ADC_BTN_DOWN)
	
	ldi r24,low(ADC_BTN_UP)
	ldi r25,high(ADC_BTN_UP)
	
	ldi r22,low(ADC_BTN_RIGHT)
	ldi r23,high(ADC_BTN_RIGHT)
	
button_test_loop:
	; Start an ADC conversion
	; Set the ADSC bit to 1 in the ADCSRA register to start a conversion
	lds	r16, ADCSRA_DS
	ori	r16, 0x40
	sts	ADCSRA_DS, r16
	; Wait for the conversion to finish
wait_for_adc:
	lds		r16, ADCSRA_DS
	andi	r16, 0x40
	brne	wait_for_adc
	; Load the ADC result into the X pair (r1:r0). Note that r1 and r0 are defined above.
	lds	r0, ADCL_DS ;output
	lds	r1, ADCH_DS
;;;;;;button judge
	cp r0,r22;right
	cpc r1,r23
	brlo right_button
	cp r0,r24;up
	cpc r1,r25
	brlo up_button
	cp r0,r26;down
	cpc r1,r27
	brlo down_button
	cp r0,r28;left
	cpc r1,r29
	brlo left_button
	cp r0,r30;select
	cpc r1,r31
	brlo select_button
	brsh ADC_judge_delay
;Set button to special value
right_button:
	ldi r20,1;Regular mode
	rjmp ADC_judge_delay
left_button:
	ldi r20,2;INverted mode
	rjmp ADC_judge_delay
up_button:
	ldi r21,2;delay 0.25 second
	rjmp ADC_judge_delay
down_button:
	ldi r21,1;delay 1 second
	rjmp ADC_judge_delay
select_button:
	lds r16,SELECT_BUTTON_COUNTER
	ldi r23, 0x01
	eor r16, r23
	sts SELECT_BUTTON_COUNTER, r16
	rjmp ADC_judge_delay
	;;;;;;;;;;;
ADC_judge_delay:
	cpi r21,1
	breq Delay_1_second;jump to delay 1 second 
	brne Delay_quarter_second;otherwise to delay 0.25 second 
;;;;;;;;;;;;;;;;;
Delay_1_second:
	lds  r16, OVERFLOW_INTERRUPT_COUNTER
	inc r16
	cpi r16, 244;1 second
	brne out_of_branch_t2
	clr r16
	cpi r20,1
	breq Regular_Mode
	brne out_of_branch_IM
	
Delay_quarter_second:
	lds  r16, OVERFLOW_INTERRUPT_COUNTER
	inc r16
	cpi r16, 61;0.25 secnond
	brne out_of_branch_t2
	clr r16
	cpi r20,1
	breq Regular_Mode
	brne out_of_branch_IM
out_of_branch_t2:
	rjmp timer2_isr_done
out_of_branch_IM:
	rjmp Inverted_Mode
;;;;;;;;;;;;;;;;;;
;LEDs_Mode:
	;PORTB_DS	PORTL_DS
Regular_Mode:
	ldi r19,0
	lds r17, STEP_COUNTER;initial value 0
	lds r22, SELECT_BUTTON_COUNTER
	cpi r22,0x01
	breq pause_regular
	
	inc r17 
pause_regular:	
	cpi r17,1
	breq step_0
	cpi r17,2
	breq step_1
	cpi r17,3
	breq step_2
	cpi r17,4
	breq step_3
	cpi r17,5
	breq step_4
	cpi r17,6
	breq step_5
	cpi r17,7
	breq step_4
	cpi r17,8
	breq step_3
	cpi r17,9
	breq step_2
	cpi r17,10
	breq step_1
	brne step_chang

step_0:
	ldi r18,0x02;pin 52 - PB, bit 1
	sts PORTB_DS,r18
	sts PORTL_DS,r19
	rjmp timer2_isr_done
step_1:
	ldi  r18, 0x08; pin 50 - PB, bit 3
	sts PORTB_DS, r18
	sts PORTL_DS,r19
	rjmp timer2_isr_done
step_2:
	ldi r18, 0x02; pin 48 - PL, bit 1
	sts PORTL_DS,r18
	sts PORTB_DS,r19
	rjmp timer2_isr_done
step_3:
	ldi r18,0x08;pin 46 - PL, bit 3
	sts PORTL_DS,r18
	sts PORTB_DS,r19
	rjmp timer2_isr_done
step_4:
	ldi r18, 0x20; pin 44 - PL, bit 5
	sts PORTL_DS,r18
	sts PORTB_DS,r19
	rjmp timer2_isr_done
step_5:
	ldi r18, 0x80; pin 42 - PL, bit 7
	sts PORTL_DS,r18
	sts PORTB_DS,r19
	rjmp timer2_isr_done
step_chang:
	clr r17
	rjmp step_0

Inverted_Mode:
	ldi r19, 0xff
	lds r17,STEP_COUNTER;initial value 0
	lds r22, SELECT_BUTTON_COUNTER
	cpi r22, 0x01
	breq pause_inverted
	
	inc r17
pause_inverted:
	cpi r17,1
	breq In_step_0
	cpi r17,2
	breq In_step_1
	cpi r17,3
	breq In_step_2
	cpi r17,4
	breq In_step_3
	cpi r17,5
	breq In_step_4
	cpi r17,6
	breq In_step_5
	cpi r17,7
	breq In_step_4
	cpi r17,8
	breq In_step_3
	cpi r17,9
	breq In_step_2
	cpi r17,10
	breq In_step_1
	brne In_step_change
	
In_step_0:
	ldi r18, 0xfd; pin 52 off - PB, bit 1
	sts PORTB_DS,r18
	sts PORTL_DS,r19
	rjmp timer2_isr_done
In_step_1:
	ldi r18, 0xf7; pin 50 off - PB, bit 3
	sts PORTB_DS, r18
	sts PORTL_DS, r19
	rjmp timer2_isr_done
In_step_2:
	ldi r18, 0xfd; pin 48 off - PL,bit 1
	sts PORTL_DS,r18
	sts PORTB_DS,r19
	rjmp timer2_isr_done
In_step_3:
	ldi r18, 0xf7; pin 46 off - PL, bit 3
	sts PORTL_DS, r18
	sts PORTB_DS, r19
	rjmp timer2_isr_done
In_step_4:
	ldi r18, 0xdf; pin 44 off - PL,bit 5
	sts PORTL_DS, r18
	sts PORTB_DS, r19
	rjmp timer2_isr_done
In_step_5:
	ldi r18, 0x7f; pin 42 off - PL, bit 7
	sts PORTL_DS, r18
	sts PORTB_DS,r19
	rjmp timer2_isr_done
In_step_change:
	clr r17
	rjmp In_step_0
	
timer2_isr_done:
	sts OVERFLOW_INTERRUPT_COUNTER, r16
	sts STEP_COUNTER, r17
	pop r16 ; Pop SREG into r16
	sts SREG_DS, r16
	pop r1
	pop r0
	pop r31
	pop r30
	pop r29
	pop r28
	pop r27
	pop r26
	pop r25
	pop r24
	pop r23
	pop r22
	;pop r21
	;pop r20
	pop r19
	pop r18
	pop r17
	pop r16
	lds r17,STEP_COUNTER
	reti
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                               Data Section                                  ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.dseg
.org 0x200
; Put variables and data arrays here...
OVERFLOW_INTERRUPT_COUNTER: .byte 1;value 0
STEP_COUNTER: .byte 1; value 0
SELECT_BUTTON_COUNTER: .byte 1
