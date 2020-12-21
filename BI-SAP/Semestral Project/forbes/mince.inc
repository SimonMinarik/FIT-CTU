korunkovy_kontroler:
		ldi r16, 0
		ldi r17, 1
		ldi r18, 0
		ldi r19, 1
		ldi r20, 0
		ldi r21, 1

		sbic PINB, 7
		ldi r16, 1
		sbic PINB, 6
		ldi r18, 1
		sbic PINB, 4
		ldi r20, 1

		ldi		r22,255
        ldi 	r30,2
        ldi     r31,2
L111: 
		dec r22
		brne L111
        dec r30
        brne L111
        dec r31
        brne L111

		;sbic PINB, 7
		;ldi r17, 1
		;sbic PINB, 6
		;ldi r19, 1
		;sbic PINB, 4
		;ldi r21, 1
		
		cpse r16, r17
		jmp dole
		cpse r18, r19
		jmp hore
		cpse r20, r21
		jmp enter
		jmp kam
dole:
		cpi r23, 1
		breq set2
		cpi r28, 1
		breq set3
		cpi r29, 1
		breq set1
hore:
		cpi r23, 1
		breq set3
		cpi r28, 1
		breq set1
		cpi r29, 1
		breq set2
set1:
		ldi r23, 1
		ldi r28, 0
		ldi r29, 0
		jmp kam
set2:
		ldi r23, 0
		ldi r28, 1
		ldi r29, 0
		jmp kam
set3:
		ldi r23, 0
		ldi r28, 0
		ldi r29, 1
		jmp kam

enter:
		ldi r16, ' '
		ldi r17, 2
		call show_char
		ldi r16, ' '
		ldi r17, 3
		call show_char
		ldi r16, ' '
		ldi r17, 4
		call show_char
		ldi r16, ' '
		ldi r17, 5
		call show_char
		ldi r16, ' '
		ldi r17, 6
		call show_char
		ldi r16, ' '
		ldi r17, 7
		call show_char
		jmp start
kam:
		cpi r23, 1
		breq kc5
		cpi r28, 1
		breq kc10
		cpi r29, 1
		breq kc20

kc5:
		ldi r16, '5'
		ldi r17, 2
		call show_char
		ldi r16, ' '
		ldi r17, 3
		call show_char
		ldi r16, 'K'
		ldi r17, 4
		call show_char
		ldi r16, 'C'
		ldi r17, 5
		call show_char
		ldi r16, ' '
		ldi r17, 6
		call show_char
		ldi r16, ' '
		ldi r17, 7
		call show_char
		jmp korunkovy_kontroler
kc10:
		ldi r16, '1'
		ldi r17, 2
		call show_char
		ldi r16, '0'
		ldi r17, 3
		call show_char
		ldi r16, ' '
		ldi r17, 4
		call show_char
		ldi r16, 'K'
		ldi r17, 5
		call show_char
		ldi r16, 'C'
		ldi r17, 6
		call show_char
		ldi r16, ' '
		ldi r17, 7
		call show_char
		jmp korunkovy_kontroler
kc20:
		ldi r16, '2'
		ldi r17, 2
		call show_char
		ldi r16, '0'
		ldi r17, 3
		call show_char
		ldi r16, ' '
		ldi r17, 4
		call show_char
		ldi r16, 'K'
		ldi r17, 5
		call show_char
		ldi r16, 'C'
		ldi r17, 6
		call show_char
		ldi r16, ' '
		ldi r17, 7
		call show_char
		jmp korunkovy_kontroler
