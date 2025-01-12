; bootloader.asm
; since: 0.0.1
; The bootloader for Cobalt OS. This, beyond doing very basic setup, 
; loads the kernel into memory and allows that to finish setup.
;
; Copyright (c) 2025 Israfil Argos
; This source code is under the AGPLv3.

; The signature to tell our BIOS that this is a bootable sector.
; In order for the bootloader to, well, boot, this is required.
org 0x7C00 ; Start on the 0x7C00 boundary.
bits 16    ; Emit 16-bit code.

; Jump to the program's entrypoint.
jmp main

%include "utilities/put.asm"
%include "utilities/gdt.asm"

; main
; since: 0.0.1
; The entrypoint of the bootloader. This zeros the registers,
; prints the load message, and loads the kernel into memory.
; params:
;       none
main:
    ; Set the video mode to VGA textual at a resolution of 720x400
    ; and the standard 16 color pallete.
    xor ah, ah
    mov al, 0x03
    int 0x10

    ; Hide the cursor.
    mov ah, 0x01
    mov cx, 0x2607
    int 0x10

    ; Set the cursor's position to the 11th row and 29th column on the
    ; first page. This centers the CobaltOS text.
    mov ah, 0x02
    mov bh, 0x00
    mov dh, 0x0B
    mov dl, 0x1D
    int 0x10

    ; Output the "booting now" string.
    mov si, startup_message
    call puts

    ; Switch off interrupts permanently--only NMI are allowed past Real
    ; mode.
    cli

    ; Zero out needed registers.
    xor ax, ax
    mov ds, ax
    mov es, ax

    ; Setup the stack.
    mov ax, 0x7E00
    mov ss, ax
    mov sp, 0xFFFF

    call install_gdt

    ; Enter Protected mode by flipped the enable flag within
    ; control register zero.
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; We are now in protected mode!

    hlt

; startup_message
; since: 0.0.1
; The message displayed when Cobalt starts to boot in earnest.
startup_message: db "CobaltOS now loading :)", NULTERM

times 510-($-$$) db 0 ; Pad the program with zeros up until the final byte.
dw 0x0AA55            ; Set the final two bytes to the signature BIOS expects.