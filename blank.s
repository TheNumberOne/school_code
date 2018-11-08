	.text
	.align	2
	.global	main
	.syntax unified
	.arm
main:
	str	fp, [sp, #-4]!
	add	fp, sp, #0

	ldr	fp, [sp], #4
	bx	lr
