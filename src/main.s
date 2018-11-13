	.eqv	.fp_reg_offset, .regs_saved*4 - 4
	.syntax	unified
	.text
	.align	2
	.global	main
	.arm
	.align	2
main:
	push	{fp, lr}
	.set	.regs_saved, 2
	add	fp, sp, .fp_reg_offset
	
	ldr	a1, =.file_name
	bl	read_file
	bl	puts

	mov	r0, 0
	sub	sp, fp, .fp_reg_offset
	pop	{fp, pc}

.hello: .asciz "Hello World!\n"
.file_name: .asciz "testfile.txt"
