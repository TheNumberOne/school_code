	.text
	.align	2
	.global	main
	.syntax unified
	.arm
main:
	push	{fp, lr}
	add	fp, sp, 4
	
	ldr	r0, =.hello
	bl	printf

	mov	r0, 0
	sub	sp, fp, 4
	pop	{fp, pc}

.hello: .asciz "Hello World!\n"
