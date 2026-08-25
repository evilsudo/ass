global setGdt
global updateSegs
gdtr DW 0 ; For limit storage
     DQ 0 ; For base storage

setGdt:
    MOV   [gdtr], DI
    MOV   [gdtr+2], RSI
    LGDT  [gdtr]
    RET

updateSegs:
    push 0x08
    lea rax, [rel reloadCS]
    push rax
    retfq

reloadCS:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret
