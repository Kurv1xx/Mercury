BITS 16
ORG 0x7C00

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    mov si, msg
    call print

    mov bx, 0x1000
    mov dh, 4
    mov dl, 0
    call disk_load

    jmp 0x0000:0x1000

print:
    mov ah, 0x0E
.next:
    lodsb
    test al, al
    jz .done
    int 0x10
    jmp .next
.done:
    ret

disk_load:
    mov ah, 0x02
    mov al, dh
    mov ch, 0
    mov cl, 2
    mov dh, 0
    int 0x13
    jc $
    ret

msg db "Bootloader online", 0

times 510-($-$$) db 0
dw 0xAA55
