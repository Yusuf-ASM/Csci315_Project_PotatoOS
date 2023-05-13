nasm test.asm -f bin -o test.bin 
xxd test.bin
qemu-system-x86_64 test.bin