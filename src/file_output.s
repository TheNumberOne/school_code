	.eqv	.fp_reg_offset, 4 * .regs_saved - 4

	.arm
	.syntax	unified
	.global	file_output
	.text
	.align	2
@ Takes two parameters. The first parameter is a file name.
@ The second parameter is a string to write. This appends to the
@ file.
file_output:
	push	{ v1, fp, lr }
	.set	.regs_saved, 3
	add	fp, sp, .fp_reg_offset
	sub	sp, 4 @ align stack

	mov	v1, a2
	ldr	a2, =.write_file_flags
	bl	fopen
	cmp	r0, 0
	beq	.error_opening_file

	mov	a2, r0
	mov	a1, v1
	mov	v1, a2
	bl	fputs
	cmp	r0, 0
	blt	.error_writing_file

	mov	r0, v1
	bl	fclose
	cmp 	r0, 0
	bne	.error_closing_file
	
	@ fall through
.end:
	sub	sp, fp, .fp_reg_offset
	pop	{ v1, fp, pc }

.error_opening_file:
	ldr	r0, =.error_opening_str
	bl	printf
	b	.end

.error_writing_file:
	ldr	r0, =.error_writing_str
	bl	printf
	b	.end

.error_closing_file:
	ldr	r0, =.error_closing_str
	bl	printf
	b	.end

	.section	.rodata
.write_file_flags: .asciz "w"
.error_opening_str: .asciz "There was an error opening a file.\n"
.error_writing_str: .asciz "There was an error writing to the file.\n"
.error_closing_str: .asciz "There was an error closing the file.\n"
