BITS 16
section .text
global _start
extern kernel_main

_start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x9000
    sti

    call kernel_main

.hang:
    jmp .hang
