all:
	nasm -f elf64 -o mapleasm.o mapleasm.S
	ld -o mapleasm mapleasm.o
	strip mapleasm
clean:
	rm mapleasm.o
	rm mapleasm
