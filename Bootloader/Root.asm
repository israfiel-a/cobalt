[bits 16]
org 0x7C00

; Jump to the entrypoint, skipping all the definitions in between here
; and there.
jmp boot_entry

boot_entry:
    hlt

times 510-($-$$) db 0 ; Pad the program with zeros up until the final byte.
dw 0x0AA55            ; Set the final two bytes to the signature BIOS expects.