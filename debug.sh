#!/bin/sh
qemu-arm -L /usr/arm-linux-gnueabi -g 1111 final_project &
gdb-multiarch -x debug.gdb
