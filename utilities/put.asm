; put.asm
; since 0.0.2
; This file provides functions to output characters and strings
; to the text buffer.
;
; Copyright (c) 2025 Israfil Argos
; This source code is under the AGPLv3.

; NEWLINE
; since: 0.0.1
; A newline/carriage return combo.
%define NEWLINE 0x0D, 0x0A

; NULTERM
; since: 0.0.1
; A null terminator for a string.
%define NULTERM 0x00

; ENDLINE
; since: 0.0.1
; A line end sequence; newline and then string terminator.
%define ENDLINE NEWLINE, NULTERM

; putc
; since 0.0.2
; Output a character to the screen.
; params:
;       al: The character to output.
putc:
    mov ah, 0x0E
    xor bh, bh
    int 0x10
    ret

; puts
; since: 0.0.1
; Display a string on the screen.
; params:
;       si: The string to print.
puts:
    .loop:
        lodsb     ; Load character from SI.
        or al, al ; Check if this byte is NUL (0).
        jz .done
        call putc

        jmp .loop
    .done:
        ret