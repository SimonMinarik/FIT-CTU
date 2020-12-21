.cseg           ; nasledujici umistit do pameti programu (implicitni)
; definice pro nas typ procesoru
.include "m169def.inc"
; podprogramy pro praci s displejem
.org 0x1000
.include "print.inc"
.include "start.inc"
.include "mince.inc"
.include "obrazovka.inc"
.org    0       ; zaciname od adresy 0 (implicitni)

 		ldi r16, 0xFF
      	out SPL, r16
      	ldi r16, 0x04
      	out SPH, r16
      ; Inicializace displeje
      	call init_disp

        jmp     start1
retez:  .db     "1AB2C31A2DD21ABC21D3",0    ; retezec zakonceny nulou
retez1:  .db     "VHODTE MINCI",0    ; retezec zakonceny nulou
.org    0x100


        ;...

mince_start:
		ldi r23, 1 ;5kc
		ldi r28, 0 ;10kc
		ldi r29, 0 ;20kc

jmp kc5

start:
      ; Inicializace zasobniku
        ldi     r30, low(2*retez)       ; dolni bajt bajtove adresy retezce (registr R30 = dolni bajt 16ti bitoveho registru Z)
        ldi     r31, high(2*retez)      ; horni bajt bajtove adresy retezce (registr R31 = horni bajt 16ti bitoveho registru Z)
                                        ; vysvetlivky:
                                        ;   1) "retez" je navesti (adresa). Pri prekladu se chova jako konstanta - jeji
                                        ;      hodnotou je adresa do pameti programu. Ma 16 bitu.
                                        ;   2) "low" je pseudoinstrukce, ktera z 16ti bitove konstanty vybere nizsi byte,
                                        ;      "high"  je pseudoinstrukce, ktera z 16ti bitove konstanty vybere vyssi byte
                                        ;   3) registr Z se sklada z registru R31:R30
		in r17, DDRE
		andi r17, 0b11110011
		in r16, PORTE
		ori r16, 0b00001100
		out DDRE, r17
		out PORTE, r16
		ldi r16, 0b00000000
		sts DIDR1, r16
		in r17, DDRB
		andi r17, 0b00101111
		in r16, PORTB
		ori r16, 0b11010000
		out DDRB, r17
		out PORTB, r16
		ldi r24, 1
		ldi r21, 0
		ldi r22, 0
		ldi r25, 50 ;bank
		ldi r26, 3 ;blikanie

reset:
		ldi     r30, low(2*retez)
        ldi     r31, high(2*retez)

controller:
		cpse r21, r24
		jmp cylinder1
		cpse r22, r24
		jmp cylinder2
		jmp cylinder3
cylinder1:
		lpm r16, Z+
		mov r10, r16
		cpi r16, 0
		breq reset
		ldi r17, 2
		call show_char		
cylinder2:
		lpm r16, Z+
		mov r11, r16
		cpi r16, 0
		breq reset
		ldi r17, 4
		call show_char
cylinder3:
		lpm r16, Z+
		mov r12, r16
		cpi r16, 0
		breq reset
		ldi r17, 6
		call show_char

		

		ldi     r18,255
        ldi 	r19,15
        ldi     r20,5
L1: 
		dec r18
    	brne L1
        dec r19
        brne L1
        dec r20
        brne L1


		ldi r16, 0
		ldi r17, 0
		sbic PINB, 4
		ldi r16, 1

		ldi     r18,255
        ldi 	r19,5
        ldi     r20,5
L21: 
		dec r18
    	brne L21
        dec r19
        brne L21
        dec r20
        brne L21

		sbic PINB, 4
		ldi r17, 1

		cpc r16, r17
		breq controller

move_cylinder1:
		cpi r21, 0
		brne move_cylinder2
		ldi r21, 1
		jmp cylinder2
move_cylinder2:
		cpi r22, 0
		brne check_winner
		ldi r22, 1
		jmp cylinder3
check_winner:
		cp r10, r11
		breq check_winner2
		jmp loser
check_winner2:
		cp r11, r12
		breq chicken_dinner

loser:
		ldi r16, 'L'
		ldi r17, 2
		call show_char
		ldi r16, 'O'
		ldi r17, 3
		call show_char
		ldi r16, 'S'
		ldi r17, 4
		call show_char
		ldi r16, 'E'
		ldi r17, 5
		call show_char
		ldi r16, 'R'
		ldi r17, 6
		call show_char
		ldi r16, 0
		cpse r23, r16
		subi r25, -1
		cpse r28, r16
		subi r25, -2
		cpse r29, r16
		subi r25, -4


chicken_dinner:
		ldi r16, 'W'
		ldi r17, 2
		call show_char
		ldi r16, 'I'
		ldi r17, 3
		call show_char
		ldi r16, 'N'
		ldi r17, 4
		call show_char
		ldi r16, 'N'
		ldi r17, 5
		call show_char
		ldi r16, 'E'
		ldi r17, 6
		call show_char
		ldi r16, 'R'
		ldi r17, 7
		call show_char
		
		ldi     r18,255
        ldi 	r19,15
        ldi     r20,5
L3: 
		dec r18
    	brne L3
        dec r19
        brne L3
        dec r20
        brne L3

		call vymaz_displej
		
		ldi     r18,255
        ldi 	r19,15
        ldi     r20,5
L31: 
		dec r18
    	brne L31
        dec r19
        brne L31
        dec r20
        brne L31
		
		dec r26
		breq zisk_kontroler
		jmp chicken_dinner

zisk_kontroler:
		cpi r23, 1
		breq zisk5kc
		cpi r28, 1
		breq zisk10kc
		cpi r29, 1
		breq zisk20kc
zisk5kc:
		subi r25, 3
		ldi r16, '+'
		ldi r17, 2
		call show_char
		ldi r16, '1'
		ldi r17, 3
		call show_char
		ldi r16, '5'
		ldi r17, 4
		call show_char
		ldi r16, ' '
		ldi r17, 5
		call show_char
		ldi r16, 'K'
		ldi r17, 6
		call show_char
		ldi r16, 'C'
		ldi r17, 7
		call show_char

zisk10kc:
		subi r25, 6
		ldi r16, '+'
		ldi r17, 2
		call show_char
		ldi r16, '3'
		ldi r17, 3
		call show_char
		ldi r16, '0'
		ldi r17, 4
		call show_char
		ldi r16, ' '
		ldi r17, 5
		call show_char
		ldi r16, 'K'
		ldi r17, 6
		call show_char
		ldi r16, 'C'
		ldi r17, 7
		call show_char

zisk20kc:
		subi r25, 12
		ldi r16, '+'
		ldi r17, 2
		call show_char
		ldi r16, '6'
		ldi r17, 3
		call show_char
		ldi r16, '0'
		ldi r17, 4
		call show_char
		ldi r16, ' '
		ldi r17, 5
		call show_char
		ldi r16, 'K'
		ldi r17, 6
		call show_char
		ldi r16, 'C'
		ldi r17, 7
		call show_char
		
		

end:    jmp     end
