; a20.asm
; since 0.0.3
; This file provides logic to enable the A20 address line 
; of the CPU. This allows all memory to be accessed properly.
;
; Copyright (c) 2025 Israfil Argos
; This source code is under the AGPLv3.

bits 16 ; Still in Real Mode at this point.

; enable_a20
; Blindly enable the A20 line on the CPU. Checking this to make sure
; it's necessary first is always recommended but I simply cannot be
; bothered. This does some heavy fuckery with registers.
; params:
;   none
enable_a20:
    ; Disable the keyboard.
    call wait_for_input
    mov al, 0xAD
    out 0x64, al
    ; Ask for output.
    call wait_for_input
    mov al, 0xD0
    out 0x64, al
    ; Read given output.
    call wait_for_output
    in al, 0x60
    push eax
    ; Demand writing to the output port.
    call wait_for_input
    mov al, 0xD1
    out 0x64, al
    call wait_for_input

    ; Activate gate A20.
    pop eax
    or al, 2
    out 0x60, al
    ; Reactivate the keyboard.
    call wait_for_input
    mov al, 0xAE
    out 0x64, al
    call wait_for_input

    ret

; wait_for_input
; Wait for the keyboard buffer to be properly empty. The A20 line is 
; routed through the keyboard controller because...uh...compatibility.
; params:
;   none
wait_for_input:
        in al, 0x64
        test al, 1
        jnz wait_for_input
        ret

; wait_for_output
; Wait for the keyboard to have provided something of use to us.
; params:
;   none
wait_for_output:
    in al, 0x64
    test al, 1
    jz wait_for_output
    ret