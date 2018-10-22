	.global	main
	.syntax unified
	.arm
	.text
	.align	2
main:
	push	{fp, lr}   @ push return address and old frame pointer onto the stack
	add	fp, sp, 4  @ move frame pointer to point to the first variable put onto the stack by this function
	
	ldr	r0, =prompt_string   @ move the prompt into the first argument to pass
	bl	printf	   @ call printf

	add	sp, fp, -4 @ move stack pointer so only the first two variables on the stack are there.
	pop	{fp, pc}   @ restore the old frame pointer and jump to the return address


	.section	.rodata  @ everything after this is readonly
prompt_string:
	.asciz "Please input two integers separated by a comma: "
