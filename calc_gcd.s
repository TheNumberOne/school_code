	.global	main
	.syntax unified
	.arm
	.text
	.align	2
main:
	push	{fp, lr}   @ push return address and old frame pointer onto the stack
	add	fp, sp, 4  @ move frame pointer to point to the first variable put onto the stack by this function
	
	add	sp, fp, -4 @ move stack pointer so only the first two variables on the stack are there.
	pop	{fp, pc}   @ restore the old frame pointer and jump to the return address
