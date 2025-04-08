[bits 16]
org 0x7C00

; Jump to the entrypoint, skipping all the definitions in between here
; and there.
jmp BootEntry

;
; BootEntry
; Since 0.1.0
; This function is the entrypoint of the bootloader. Think about the __start()
; function in C, which initializes base program data and kicks off program
; launch.
;
; Arguments:
;   N/A
;
BootEntry:
    ; Clear garbage data from the registers.
    xor ax, ax
    xor bx, bx
    xor cx, cx
    xor dx, dx

    hlt

times 510-($-$$) db 0 ; Pad the program with zeros up until the final byte.
dw 0x0AA55            ; Set the final two bytes to the signature BIOS expects.