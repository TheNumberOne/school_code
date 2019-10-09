
	.set	.delimeter, ',
	.set	.explode_delimeter, .delimeter
	.set	.output_delimeter, .delimeter


	.eqv	.fp_reg_offset, .regs_saved*4 - 4
	.syntax	unified
	.text
	.align	2
	.global	main
	.arm
	.align	2
@ first argument is number of params
@ second argument is pointer to param pointers.
main:
	push	{v1, v2, v3, v4, v5, fp, lr}
	.set	.regs_saved, 7
	add	fp, sp, .fp_reg_offset
	sub	sp, 4	

	@ first check num arguments
	cmp	a1, 3
	bne	.usage

	@ save save file to v1
	ldr	v1, [a2, 8]

	@ read file.
	ldr	a1, [a2, 4]
	bl	read_file
	cmp	r0, 0
	beq	.error
	
	mov	v2, r0  @ remember string so we can free it

	mov	a2, .explode_delimeter
	bl	explode

	mov	v4, r0
	mov	r0, v2
	bl	free

	cmp	v4, 0
	beq	.error

	mov	r0, v4
	bl	strings_to_ints

	mov	v2, r0
	mov	v3, r1
	
	@ free string of strings, buffer of buffers, one pointer to rule them all.
	mov	v5, v4
.royal_free_loop:
	ldr	r0, [v5], 4
	cmp	r0, 0
	beq	.royal_free_loop_end
	bl	free
	b	.royal_free_loop
	
.royal_free_loop_end:
	mov	r0, v4
	bl	free

	@ process ints
	cmp	v2, 0
	beq	.error

	mov	r0, v2
	mov	r1, v3
	bl	merge_sort

	mov	r0, v2
	mov	r1, v3
	mov	r2, .output_delimeter

	bl	ints_to_string

	mov	v3, r0
	mov	r0, v2
	bl	free

	cmp	v3, 0
	beq	.error

	mov	r0, v1
	mov	r1, v3
	bl	file_output

	mov	r0, v3
	bl	free
	
	@ and they lived happily ever after
.good_ending:
	mov	r0, 0
	@ fall through
.end:
	sub	sp, fp, .fp_reg_offset
	pop	{v1, v2, v3, v4, v5, fp, pc}

.error:
	mov	r0, -1
	b	.end

.usage:
	ldr	r0, =.usage_str
	bl	printf
	b	.good_ending
	

	.section	.rodata
.usage_str: .asciz "To use call with two file names as arguments.\n"
