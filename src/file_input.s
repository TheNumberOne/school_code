	.eqv	.fp_reg_offset, .regs_saved*4 - 4

	.text
	.global	main
	.syntax unified
	.arm
	.align	3
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

	.align 2
read_file:
	push {r4, r5, r6, r7, fp, lr}
	.set	.regs_saved, 6
	add	fp, sp, .fp_reg_offset
	
	ldr	a2, =.read_file_flags
	bl	fopen

	cmp 	r0, 0
	bne	.file_opened
	mov	r0, 0
	b	.end

.file_opened:

	file .req v1
	buffer_start 	.req v2
	buffer_current 	.req v3
	buffer_left 	.req v4

	mov	file, r0
	mov	buffer_left, 16
	mov	a1, buffer_left
	bl	malloc

	mov 	buffer_start, r0
	cmp 	buffer_start, 0
	beq 	.close_file
	mov 	buffer_current, buffer_start

.read_into_buffer:
	mov 	a1, buffer_current
	mov	a2, 1
	mov	a3, buffer_left
	mov	a4, file
	bl	fread
	cmp	r0, 0
	beq	.end_of_file
	cmp	r0, -1
	beq	.error_reading_file
	sub	buffer_left, r0
	add	buffer_current, r0
	cmp	buffer_left, 0
	bne	.read_into_buffer

.realloc_buffer:
	mov	a1, buffer_start
	sub	buffer_left, buffer_current, buffer_start
	mov	a2, 2
	mul	a2, buffer_left
	bl	realloc
	cmp 	r0, 0
	beq	.realloc_failed
	mov	buffer_start, r0
	add	buffer_current, buffer_start, buffer_left
	b	.read_into_buffer

.realloc_failed:
	mov	r0, buffer_start
	bl	free
	b	.close_file

.error_reading_file:
	bl	__errno_location
	ldr	a2, [r0]
	ldr	a1, =.error_reading_file_str
	bl	printf
	mov	r0, 0
	b	.close_file

.end_of_file:
	mov	r0, 0
	str	r0, [buffer_current]

.close_file:
	mov	r0, file
	bl	fclose
	mov	r0, buffer_start

.end:
	sub sp, fp, .fp_reg_offset
	pop {r4, r5, r6, r7, fp, pc}
	






.read_file_flags: .asciz "r"
.error_reading_file_str: .asciz "Error reading file: %d\n"
