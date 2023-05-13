[org 0x7c00]

mov bx, simpleOS
call print


jmp $

%include "print.asm"

simpleOS:
    db 'simpleOS is Loading...', 0


times 510 - ($-$$) db 0; boooooot bits
; db 0x55,0xaa ; also valid
dw 0xaa55 ; Allow us to define 2 byte (litte endian)


