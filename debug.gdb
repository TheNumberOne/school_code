# extremely inspired by https://stackoverflow.com/a/51310791
set sysroot /usr/arm-linux-gnueabi
file final_project
target remote localhost:1111
break main
continue
layout asm
layout regs
