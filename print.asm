
print: 
    pusha
    

start_printing:
    mov al,[bx]
    cmp al,0
    je done_printing

    mov ah, 0x0e
    int 0x10

    ;add bx,1 ; also valid
    inc bx
    jmp start_printing 

done_printing:
    popa
    ret

print_ln:
   

    call print

    pusha
    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10
    
    popa
    ret

print_nl:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10
    
    popa
    ret