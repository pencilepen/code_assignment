; a3_template.asm
; CSC 230 - Summer 2018
; 
; Starter code for A3.
;
; B. Bird - 07/01/2018

.include "lcd_function_defs.inc"

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
; "unreserved" location is 0x0072
.org 0x0072
main_begin:
	
;LINE_ONE: .byte 100 -- store a string showing "Time: ......" 

;ADC_buttons_counter: .byte 1	-- store which button pressed
;OVERFLOW_TENTH_COUNTER: .byte 1--  interrupt counter
;OVERFLOW_SECOND_COUNTER: .byte 1--  interrupt counter
;PAUSE_TIMER_STATUS -- whether pause timer: 0- pause ; 1- don't pause 

	; Initialize the stack
	ldi r16, high(STACK_INIT)
	sts SPH_DS, r16
	ldi r16, low(STACK_INIT)
	sts SPL_DS, r16
	
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
	; Initialize the LCD
	call lcd_init

	ldi r16, 0
	sts OVERFLOW_TENTH_COUNTER, r16
	sts OVERFLOW_SECOND_COUNTER, r16
	sts PAUSE_TIMER_STATUS, r16
	sts UP_BUTTON_STATUS, r16
	
	ldi XL, low(LINE_ONE)
	ldi XH, high(LINE_ONE)
	ldi r16,'T'
	st X+, r16
	ldi r16,'i'
	st X+, r16
	ldi r16,'m'
	st X+, r16
	ldi r16,'e'
	st X+, r16
	ldi r16,':'
	st X+, r16
	ldi r16,' '
	st X+, r16
	ldi r16,'0'
	st X+, r16
	ldi r16,'0'
	st X+, r16
	ldi r16,':'
	st X+, r16
	ldi r16,'0'
	st X+, r16
	ldi r16,'0'
	st X+, r16
	ldi r16,'.'
	st X+, r16
	ldi r16,'0'
	st X+, r16
	ldi r16, 0
	st X, r16
	;//////////
	
	ldi XL, low(CURRENT_LAP_START)
	ldi XH, high(CURRENT_LAP_START)
	ldi r16,'0'
	st X+, r16
	ldi r16,'0'
	st X+, r16
	ldi r16,':'
	st X+, r16
	ldi r16,'0'
	st X+, r16
	ldi r16,'0'
	st X+, r16
	ldi r16,'.'
	st X+, r16
	ldi r16,'0'
	st X+, r16
	; Set up the LCD to display starting on row 0, column 0
	ldi r16, 0 ; Row number
	push r16
	ldi r16, 0 ; Column number
	push r16
	call lcd_gotoxy
	pop r16
	pop r16
		
	; Now call lcd_puts to display the string. lcd_puts takes the base address of the string
	; as its argument on the stack (with the high byte pushed first)
	ldi r16, high(LINE_ONE)
	push r16
	ldi r16, low(LINE_ONE)
	push r16
	call lcd_puts
	pop r16
	pop r16
	
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
	push r18; overflow only (tenth)
	push r19;overflow only (second)
	push r20; compute with adc button 
	push XL
	push XH
	push YL
	push YH
;///buttons	
;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;
	push r0
	push r1
	push r2
	push r3
	push r4
	push r5
	push r6
	push r7
	push r8
	push r9
	push r10
	push r11
	push r12
	ldi	r16, low(ADC_BTN_SELECT)
	mov r0,r16
	ldi	r16, high(ADC_BTN_SELECT)
	mov r1,r16
	
	ldi r16,low(ADC_BTN_LEFT)
	mov r2, r16
	ldi r16,high(ADC_BTN_LEFT)
	mov r3, r16
	
	ldi r16,low(ADC_BTN_DOWN)
	mov r4, r16
	ldi r16,high(ADC_BTN_DOWN)
	mov r5, r16
	
	ldi r16,low(ADC_BTN_UP)
	mov r6, r16
	ldi r16,high(ADC_BTN_UP)
	mov r7, r16
	
	ldi r16,low(ADC_BTN_RIGHT)
	mov r8, r16
	ldi r16,high(ADC_BTN_RIGHT)	
	mov r9, r16
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
	lds	r10, ADCL_DS ;output
	lds	r11, ADCH_DS
	
	cp r10,r8
	cpc r11,r9
	brlo right_button
	cp r10,r6
	cpc r11,r7
	brlo up_button
	cp r10, r4
	cpc r11, r5
	brlo down_button
	cp r10,r2
	cpc r11,r3
	brlo left_button
	cp r10, r0
	cpc r11, r1
	brlo select_button
	brsh No_press
down_button:
	ldi r16, 0
	sts UP_BUTTON_STATUS, r16
	jmp down_button_countine
No_press:
	ldi r16, 0
	sts UP_BUTTON_STATUS, r16
	jmp timer2_isr_start
left_button:
	ldi r16, 0
	sts UP_BUTTON_STATUS, r16
	jmp left_button_continue
select_button:
	ldi r16, 0
	sts UP_BUTTON_STATUS, r16
	jmp select_button_continue
;//button ends
;jump to button's effect
right_button:
	ldi r16, 0
	sts UP_BUTTON_STATUS, r16
	jmp timer2_isr_start
	
up_button:
	lds r16, UP_BUTTON_STATUS
	cpi r16, 0
	brne up_button_useless
	ldi r16, 1
	sts UP_BUTTON_STATUS, r16
	jmp up_button_countinue
	
up_button_useless:
	jmp timer2_isr_start
	
up_button_countinue:
;showing LAST_LAP_START <- CURRENT_LAP_START
	ldi YL, low(LAST_LAP_START)
	ldi YH, high(LAST_LAP_START)
	ldi XL, low(CURRENT_LAP_START)
	ldi XH, high(CURRENT_LAP_START)
	
lap_time_copy_loop3:
	ld r16, X+
	mov r17, r16
	st Y+, r17
	cpi r16, 0
	brne lap_time_copy_loop3
	
;//////////////////////////////
;
;//////////////////////////////	
	
	ldi r16, 1 ; Row number
	push r16
	ldi r16, 0 ; Column number
	push r16
	call lcd_gotoxy
	pop r16
	pop r16
		
	; Now call lcd_puts to display the string. lcd_puts takes the base address of the string
	; as its argument on the stack (with the high byte pushed first)
	ldi r16, high(LAST_LAP_START)
	push r16
	ldi r16, low(LAST_LAP_START)
	push r16
	call lcd_puts
	pop r16
	pop r16

	
	ldi r16, 1 ; Row number
	push r16
	ldi r16, 9 ; Column number
	push r16
	call lcd_gotoxy
	pop r16
	pop r16
	
	ldi r16, high(LAST_LAP_END)
	push r16
	ldi r16, low(LAST_LAP_END)
	push r16
	call lcd_puts
	pop r16
	pop r16
;/////////////////////////////////
;showing CURRENT_LAP_START <- LAST_LAP_END
	ldi XL, low(LAST_LAP_END)
	ldi XH, high(LAST_LAP_END)
	ldi YL, low(CURRENT_LAP_START)
	ldi YH, high(CURRENT_LAP_START)
	
lap_time_copy_loop5:
	ld r16, X+
	mov r17, r16
	st Y+, r17
	cpi r16, 0
	brne lap_time_copy_loop5	
	
	jmp timer2_isr_start
	
down_button_countine:

	ldi XL, low(CURRENT_LAP_START)
	ldi XH, high(CURRENT_LAP_START)
	ld r16,X
	ldi r16, '0'
	st X+, r16
	
	ld r16,X
	ldi r16, '0'
	st X+, r16
	
	ld r16, X
	ldi r16,':'
	st X+, r16
	
	ld r16, X
	ldi r16, '0'
	st X+, r16
	
	ld r16,X
	ldi r16, '0'
	st X+, r16
	
	ld r16, X
	ldi r16, '.'
	st X+, r16
	
	ld r16, X
	ldi r16, '0'
	st X+, r16
	ldi r16, 0
	st X, r16
	
	call lcd_init
	
	; Set up the LCD to display starting on row 0, column 0
	ldi r16, 0 ; Row number
	push r16
	ldi r16, 0 ; Column number
	push r16
	call lcd_gotoxy
	pop r16
	pop r16
	
	; Now call lcd_puts to display the string. lcd_puts takes the base address of the string
	; as its argument on the stack (with the high byte pushed first)
	ldi r16, high(LINE_ONE)
	push r16
	ldi r16, low(LINE_ONE)
	push r16
	call lcd_puts
	pop r16
	pop r16
	
	jmp timer2_isr_start
select_button_continue:; Start/ stop timer
	ldi r20, 0x01
	lds r16, PAUSE_TIMER_STATUS
	eor r16, r20
	sts PAUSE_TIMER_STATUS, r16
	jmp timer2_isr_start
	
	
left_button_continue:;Clear timer
	ldi r16, 0
	sts PAUSE_TIMER_STATUS, r16
	
	ldi XL, low(LINE_ONE)
	ldi XH, high(LINE_ONE)
	ldi r16,'T'
	st X+, r16
	ldi r16,'i'
	st X+, r16
	ldi r16,'m'
	st X+, r16
	ldi r16,'e'
	st X+, r16
	ldi r16,':'
	st X+, r16
	ldi r16,' '
	st X+, r16
	ldi r16,'0'
	st X+, r16
	ldi r16,'0'
	st X+, r16
	ldi r16,':'
	st X+, r16
	ldi r16,'0'
	st X+, r16
	ldi r16,'0'
	st X+, r16
	ldi r16,'.'
	st X+, r16
	ldi r16,'0'
	st X+, r16
	ldi r16, 0
	st X, r16
	
	ldi r16, 0 ; Row number
	push r16
	ldi r16, 0 ; Column number
	push r16
	call lcd_gotoxy
	pop r16
	pop r16
	
	ldi r16, high(LINE_ONE)
	push r16
	ldi r16, low(LINE_ONE)
	push r16
	call lcd_puts
	pop r16
	pop r16
	jmp timer2_isr_start

;;;;;////////////////////////
;/////////////////////////////////////////////////
;///////////////////////////////////////////////////
timer2_isr_start:
;Lap timing:;;;;;
	lds r16, PAUSE_TIMER_STATUS
	cpi r16, 0;pause
	brne TIMEING_NOT_PAUSING
;//////////LAST_LAP_END <- CURRENT_LAP_START	
;	ldi YL, low(LAST_LAP_START)
;	ldi YH, high(LAST_LAP_START)
;	ldi XL, low(CURRENT_LAP_START)
;	ldi XH, high(CURRENT_LAP_START)
;	
;lap_time_copy_loop3:
;	ld r16, X+
;	mov r17, r16
;	st Y+, r17
;	cpi r16, 0
;	brne lap_time_copy_loop3
;////////////////////////CURRENT_LAP_START <- LAST_LAP_END
;	ldi YL, low(CURRENT_LAP_START)
;	ldi YH, high(CURRENT_LAP_START)
;	ldi XL, low(LAST_LAP_END)
;	ldi XH, high(LAST_LAP_END)
;	
;lap_time_copy_loop4:
;	ld r16, X+
;	mov r17, r16
;	st Y+, r17
;	cpi r16, 0
;	brne lap_time_copy_loop4
	
	jmp timer2_isr_done
TIMEING_NOT_PAUSING:
	lds r19, OVERFLOW_TENTH_COUNTER
	inc r19
	lds r18, OVERFLOW_SECOND_COUNTER
	inc r18
;///////////////////////////////////
;timer2 interrupts
;one tenth
	cpi r19,24
	brne ONE_SECOND
	clr r19
	ldi r16, 0 ; Row number
	push r16
	ldi r16, 0 ; Column number
	push r16
	call lcd_gotoxy
	pop r16
	pop r16
	
	; Call REVERSE_STRING to copy LINE_ONE into LINE_TWO in reverse.
	ldi XL, low(LINE_ONE)
	ldi XH, high(LINE_ONE)
	
	;call test_function to change number
	call tenth_test_function
	; Display
	ldi r16, high(LINE_ONE)
	push r16
	ldi r16, low(LINE_ONE)
	push r16
	call lcd_puts
	pop r16
	pop r16
	
ONE_SECOND:
	cpi r18,248
	brne timer2_isr_done
	clr r18
	
	ldi r16, 0 ; Row number
	push r16
	ldi r16, 0 ; Column number
	push r16
	call lcd_gotoxy
	pop r16
	pop r16

	ldi XL, low(LINE_ONE)
	ldi XH, high(LINE_ONE)
	call test_function; change number at 12th LCD (low second)
	
	ldi r16, high(LINE_ONE)
	push r16
	ldi r16, low(LINE_ONE)
	push r16
	call lcd_puts
	pop r16
	pop r16
	
	;;;;;;;;;;;;;;;;;
timer2_isr_done:
	ldi XL, low(LINE_ONE)
	ldi XH, high(LINE_ONE)
	ldi YL, low(LAST_LAP_END)
	ldi YH, high(LAST_LAP_END)
	ldi r17, 0
lap_time_copy_loop1:	
	ld r16, X+
	inc r17
	cpi r17, 6
	brlo lap_time_copy_loop1
lap_time_copy_loop2:
	ld r16, X+
	mov r17, r16
	st Y+, r17
	cpi r16, 0
	brne lap_time_copy_loop2
	
	;;;;;;;;;;;//////////////
	sts OVERFLOW_TENTH_COUNTER, r19
	sts OVERFLOW_SECOND_COUNTER, r18
	

	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop r7
	pop r6
	pop r5
	pop r4
	pop r3
	pop r2
	pop r1
	pop r0
	
	pop YH
	pop YL
	pop XH
	pop XL
	pop r20
	pop r19
	pop r18
	pop r17
	pop r16
	reti
	;//////////////////////////end TIMER2_OVERFLOW_ISR
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;test_function displays tenth number				;;
;;;													;;	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

test_function:; change number of timer
	push r16
	push r17
	push XL
	push XH
	
	ldi r17, 0
test_function_loop:	
	ld r16, X+
	inc r17
	cpi r17, 10
	brlo test_function_loop
	
	ld r16, X;column 10
	cpi r16, '9'
	breq To_be_zero
	
	inc r16
	st X, r16
	jmp test_function_end
	
To_be_zero:
	call column_nine_function
	ldi r16, '0'
	st X, r16

test_function_end:	
	
	pop XH
	pop XL
	pop r17
	pop r16
	ret
;///////////////////////////////////////////column 9
column_nine_function:
	push r16
	push r17
	push XL
	push XH
	
	ldi XL, low(LINE_ONE)
	ldi XH, high(LINE_ONE)
	ldi r17, 0
column_nine_loop:	
	ld r16, X+
	inc r17
	cpi r17, 9
	brlo column_nine_loop
	
	ld r16, X;column 9
	cpi r16, '5'
	breq column_nine_be_zero
	
	inc r16
	st X, r16
	jmp column_nine_end
	
column_nine_be_zero:
	call column_seven_function
	ldi r16, '0'
	st X, r16

column_nine_end:	
	
	pop XH
	pop XL
	pop r17
	pop r16
	ret
;/////////////////////////////////////////column 7
column_seven_function:
	push r16
	push r17
	push XL
	push XH
	
	ldi XL, low(LINE_ONE)
	ldi XH, high(LINE_ONE)
	ldi r17, 0
column_seven_loop:	
	ld r16, X+
	inc r17
	cpi r17, 7
	brlo column_seven_loop
	
	ld r16, X;column 7
	cpi r16, '9'
	breq column_seven_be_zero
	
	inc r16
	st X, r16
	jmp column_seven_end
	
column_seven_be_zero:
	call column_six_function
	ldi r16, '0'
	st X, r16

column_seven_end:	
	
	pop XH
	pop XL
	pop r17
	pop r16
	ret
;///////////////////////////////////////column 6
column_six_function:
	push r16
	push r17
	push XL
	push XH
	
	ldi XL, low(LINE_ONE)
	ldi XH, high(LINE_ONE)
	ldi r17, 0
column_six_loop:	
	ld r16, X+
	inc r17
	cpi r17, 6
	brlo column_six_loop
	
	ld r16, X;column 6
	cpi r16, '9'
	breq column_six_be_zero
	
	inc r16
	st X, r16
	jmp column_six_end
	
column_six_be_zero:
	;call 
	ldi r16, '0'
	st X, r16

column_six_end:	
	
	pop XH
	pop XL
	pop r17
	pop r16
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
tenth_test_function:; change number of tenth-timer
	push r16
	push r17
	push XL
	push XH
	
	ldi r17, 0
tenth_test_function_loop:	
	ld r16, X+
	inc r17
	cpi r17, 12
	brlo tenth_test_function_loop
	
	ld r16, X;column 12
	cpi r16, '9'
	breq tenth_To_be_zero
	
	inc r16
	st X, r16
	jmp tenth_test_function_end
	
tenth_To_be_zero:
	ldi r16, '0'
	st X, r16

tenth_test_function_end:	

	pop XH
	pop XL
	pop r17
	pop r16
	ret
;;;;;;;;;;;;;;;;; timer's functions end

	
; Include LCD library code
.include "lcd_function_code.asm"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                               Data Section                                  ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.dseg
; Note that no .org 0x200 statement should be present
; Put variables and data arrays here...
LINE_ONE: .byte 100
LINE_TWO: .byte 10
LAST_LAP_START: .byte 10
LAST_LAP_END: .byte 10
CURRENT_LAP_START: .byte 10
ADC_buttons_counter: .byte 1	
OVERFLOW_TENTH_COUNTER: .byte 1
OVERFLOW_SECOND_COUNTER: .byte 1
PAUSE_TIMER_STATUS: .byte 1
UP_BUTTON_STATUS: .byte 1
;      6 7   9 10  12
;Time: M M : S S . T