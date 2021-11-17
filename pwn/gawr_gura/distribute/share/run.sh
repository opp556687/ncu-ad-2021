#!/bin/sh

exec 2>/dev/null
LD_PRELOAD=/home/gawr_gura/libc.so timeout 60 /home/gawr_gura/gawr_gura
