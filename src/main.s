	.eqv	.fp_reg_offset, .regs_saved*4 - 4
	.syntax	unified
	.text
	.align	2
	.global	main
	.arm
	.align	2
main:
	push	{v1, fp, lr}
	.set	.regs_saved, 3
	add	fp, sp, .fp_reg_offset
	sub	sp, 4	

	ldr	a1, =.file_name
	bl	read_file
	bl	puts
	

	ldr	a1, =.string_to_explode 
	mov	a2, ' @ space character 
	bl	explode

	mov	v1, r0

.loop:
	ldr	a1, =.explode_output
	ldr	a2, [v1], 4
	cmp	a2, 0
	beq	.end_loop
	bl	printf
	b	.loop
.end_loop:

	mov	r0, 0
	sub	sp, fp, .fp_reg_offset
	pop	{v1, fp, pc}

.hello: .asciz "Hello World!\n"
.file_name: .asciz "testfile.txt"
.string_to_explode: .asciz "hello world again. how are you?"
.explode_output: .asciz "%s\n"
