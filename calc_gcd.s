	.global	main
	.syntax unified
	.arm
	.text
	.align	2
main:
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	mov	r3, #0
	mov	r0, r3
	add	sp, fp, #0
	ldr	fp, [sp], #4
	bx	lr
