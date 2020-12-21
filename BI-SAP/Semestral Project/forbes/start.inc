starting_screen:
start1:
        ldi     r30, low(2*retez1)       ; dolni bajt bajtove adresy retezce (registr R30 = dolni bajt 16ti bitoveho registru Z)
        ldi     r31, high(2*retez1)      ; horni bajt bajtove adresy retezce (registr R31 = horni bajt 16ti bitoveho registru Z)

                                        ; vysvetlivky:
                                        ;   1) "retez" je navesti (adresa). Pri prekladu se chova jako konstanta - jeji
                                        ;      hodnotou je adresa do pameti programu. Ma 16 bitu.
                                        ;   2) "low" je pseudoinstrukce, ktera z 16ti bitove konstanty vybere nizsi byte,
                                        ;      "high"  je pseudoinstrukce, ktera z 16ti bitove konstanty vybere vyssi byte
                                        ;   3) registr Z se sklada z registru R31:R30

        ldi r24,' '
        ldi r23,' '
        ldi r22,' '
        ldi r21,' '
        ldi r20,' '
        ldi r19,' '
cycle:
        lpm     r16, Z+                 ; nahraj bajt (znak) z retezce do r16, posun pozici v retezci
        jmp posun

checkpoint:
        jmp mince_start

posun:
        cpi r16, 0
        breq konec

        mov     r24,r23
        mov     r23,r22
        mov     r22,r21
        mov     r21,r20
        mov     r20,r19
        mov r19,r16

        ldi r17,7
        call show_char

        mov r16,r20
        ldi r17,6
        call show_char

        mov r16,r21
        ldi r17,5
        call show_char

        mov r16,r22
        ldi r17,4
        call show_char

        mov r16,r23
        ldi r17,3
        call show_char

        mov r16,r24
        ldi r17,2
        call show_char

        ldi     r26,255
        ldi r27,15
        ldi     r28,5
L11: 	dec r26
    	brne L11
        dec r27
        brne L11
        dec r28
        brne L11

        jmp cycle 

konec:
        ldi r25, 0
        jmp empty

empty:
        cpi r25, 6
        breq checkpoint

        mov     r24,r23
        mov     r23,r22
        mov     r22,r21
        mov     r21,r20
        mov     r20,r19
        ldi r19,' '

        mov r16,r19
        ldi r17,7
        call show_char

        mov r16,r20
        ldi r17,6
        call show_char

        mov r16,r21
        ldi r17,5
        call show_char

        mov r16,r22
        ldi r17,4
        call show_char

        mov r16,r23
        ldi r17,3
        call show_char

        mov r16,r24
        ldi r17,2
        call show_char

        ldi     r26,255
        ldi r27,15
        ldi     r28,5
L2:
		dec r26
		brne L2
        dec r27
        brne L2
        dec r28
        brne L2

        inc r25
        jmp empty
