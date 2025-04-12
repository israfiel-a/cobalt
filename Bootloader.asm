[bits 16]
org 0x7C00

; Jump to the entrypoint, skipping all the definitions in between here
; and there.
jmp BootEntry

;
; boot_message
; Since 0.1.0
; The message displayed during boot, while the operating system is launching.
;
boot_message: db "CobaltOS now booting... :)", 0

;
; SetDisplayMode
; Since 0.1.0
; Set the display mode of the screen, for the display of diagnostic 
; information and/or a greeting.
;
; Arguments:
;   al: The video mode to set to.
;
SetDisplayMode:
    xor ah, ah
    int 0x10
    ret

;
; SetCursorMode
; Since 0.1.0
; Set the display mode of the cursor, where the cursor has 7 scan lines.
;
; Arguments:
;   cx: The cursor mode.
;
SetCursorMode:
    mov ah, 0x01
    int 0x10
    ret

;
; SetCursorPosition
; Since 0.1.0
; Set the cursor's position.
;
; Arguments:
;   dx: Cursor position (dh row, dl col).
;
SetCursorPosition:
    mov ah, 0x02
    int 0x10
    ret

;
; PutString
; Since 0.1.0
; Put a string at the given location.
;
; Arguments:
;   si: The string to output.
;   bh: The page number to output on.
;   dx: Initial cursor position (dh row, dl col).
;
PutString:
    mov cx, 0x1
    call SetCursorPosition ; Set cursor to initial start.
    .PutCharacter:
        lodsb
        or al, al ; Check if this byte is 0.
        jz .Finish
        mov ah, 0x0A
        int 0x10

        ; Move the cursor to the right.
        inc dl
        call SetCursorPosition
        jmp .PutCharacter
    .Finish:
        ret

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

    mov al, 0x03 ; 720x400 text mode
    call SetDisplayMode

    mov cx, 0x0706 ; Invisible cursor.
    call SetCursorMode

    mov si, boot_message
    xor bh, bh
    ; Cursor position at (11,28).
    mov dx, 0x0B1C
    call PutString

    hlt

times 510-($-$$) db 0x00 ; Pad the program with zeros up until the final byte.
dw 0x0AA55               ; Set the final two bytes to the signature BIOS expects.