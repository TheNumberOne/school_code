	.eqv	.fp_reg_offset, .regs_saved*4 - 4
	.syntax	unified
	.text
	.align	2
	.global	main
	.arm
	.align	2
main:
	push	{v1, v2, fp, lr}
	.set	.regs_saved, 4
	add	fp, sp, .fp_reg_offset
	@sub	sp, 4	

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

	ldr	r0, =.number_str
	bl	string_to_int
	mov	r1, r0
	ldr	r0, =.number_output
	bl	printf

	ldr	a1, =.numbers_str
	mov	a2, ' @
	bl	explode
	bl	strings_to_ints
	
	mov	v1, r0
	add	v2, r0, r1, lsl 2 @ v2 = r0 + (r1 << 2)
	bl	merge_sort
.numbers_loop:
	cmp	v1, v2
	beq	.end_numbers_loop
	ldr	a1, =.number_output
	ldr	a2, [v1], 4
	bl	printf
	b	.numbers_loop

.end_numbers_loop:

	mov	r0, 0
	sub	sp, fp, .fp_reg_offset
	pop	{v1, v2, fp, pc}

.hello: .asciz "Hello World!\n"
.file_name: .asciz "testfile.txt"
.string_to_explode: .asciz "hello world again. how are you?"
.explode_output: .asciz "%s\n"
.number_str: .asciz "12345"
.number_output: .asciz "Parsed: %d\n"
.numbers_str: .asciz "45 4t356 24    456 2 1 0  2 4 5  "
