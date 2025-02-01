; gdt.asm
; since 0.0.2
; This file provides the definition for the Global Descriptor
; Table (GDT), which provides a bridge between 16-bit Real mode and
; 32-bit Protected mode.
;
; Copyright (c) 2025 Israfil Argos
; This source code is under the AGPLv3.

; We're still in 16-bit mode at this point.
bits 16

; gdt_structure
; since 0.0.2
; The structure for Cobalt's Global Descriptor table, with all segments
; defined.
gdt_structure:
    ; The null descriptor. This is never referenced, and contains
    ; exactly 8 bytes of nothing.
    dq 0

    ; Kernel code descriptor.
    dw 0xFFFF ; The possible size of the segment (64KB).
    dw 0      ; A piece of the descriptor base.
    db 0
    ; The permissions of the segment.
    ;   (1)  valid descriptor 1b
    ;   (00) ring 0           2b
    ;   (1)  code segment     1b
    ;   (1)  executable       1b
    ;   (0)  nonconforming    1b
    ;   (1)  readable         1b
    ;   (1)  accessed         1b
    db 10011010b
    ; Granularity flags for the segment.
    ;   (11) 4kb granularity  2b
    ;   (00) 32-bit segment   2b
    ;   (11) long-mode        2b
    ;   (11) reserved         2b
    db 11001111b
    db 0         ; The rest of the descriptor base address.

    ; Kernel data descriptor.
    dw 0xFFFF ; The possible size of the segment (64KB).
    dw 0      ; A piece of the descriptor base.
    db 0
    ; The permissions of the segment.
    ;   (1)  valid descriptor 1b
    ;   (00) ring 0           2b
    ;   (1)  data segment     1b
    ;   (0)  nonexecutable    1b
    ;   (0)  nonconforming    1b
    ;   (1)  writeable        1b
    ;   (1)  accessed         1b
    db 10010011b
    ; Granularity flags for the segment. Same as kernel code segment.
    db 11001111b
    db 0         ; The rest of the descriptor base address.
gdt_structure_end:

; gdt
; since 0.0.2
; A pointer to the GDT structure for use in loading said structure
; into memory.
gdt:
    dw gdt_structure_end - gdt_structure - 1
    dq gdt_structure

; install_gdt
; since 0.0.2
; Install the GDT. Interrupts must have been disabled before this
; function is called.
; params:
;       none
install_gdt:
    lgdt [gdt]
    ret