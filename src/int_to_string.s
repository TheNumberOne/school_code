	.eqv	.fp_reg_offset, .regs_saved * 4 - 4

	.syntax	unified
	.text
	.align	2
	.arm
	.global ints_to_string

	@ Converts an array of integers to a string by joining them together.
	@ 
	@ r0/a1: A pointer to an array of integers.
	@ r1/a2: The length of that array.
	@ r2/a3: The delimeter to use between each integer.
	@
	@ Returns a null terminated string of the numbers with the chosen delimeter
	@ between every number. There is no trailing instance of the character added.
ints_to_string:
	@ v1 is current location in the array of integers.
	@ v2 is the location just past the end of the array of integers.
	@ v3 is the delimeter.
	@ v4 contains a pointer to the result.
	@ [fp - .str_pointer] is the current location in the result.
	push	{ v1, v2, v3, v4, fp, lr }
	.set	.regs_saved, 6
	add	fp, sp, .fp_reg_offset

	sub	sp, 8 @ add 4 bytes for str_pointer and keep aligned
	.set	.str_pointer, .fp_reg_offset + 4

	mov	v1, a1
	add	v2, a1, a2, lsl 2
	mov	v3, a3
	bl	ints_length
	bl	malloc
	cmp	r0, 0
	beq	.ints_to_string_return_nothing
	
	mov	v4, r0
	str	r0, [fp, -.str_pointer]

	cmp	v1, v2
	beq	.ints_to_string_end

.ints_to_string_loop:
	add	a1, fp, -.str_pointer
	ldr	a2, [v1], 4
	bl	int_to_string
	
	cmp	v1, v2
	beq	.ints_to_string_end

	@ add delimeter
	ldr	r0, [fp, -.str_pointer]
	strb	v3, [r0], 1
	str	r0, [fp, -.str_pointer]
	b	.ints_to_string_loop
	
.ints_to_string_end:
	@ write null character.
	ldr	r0, [fp, -.str_pointer]
	mov	r1, 0
	strb	r1, [r0]

	mov	r0, v4
	@ fall through
.ints_to_string_return:
	sub	sp, fp, .fp_reg_offset
	pop	{ v1, v2, v3, v4, fp, pc }

.ints_to_string_return_nothing:
	mov	r0, 0
	b	.ints_to_string_return

	@ Parses an integer to a string.
	@
	@ r0/a1: A pointer to a pointer pointing to the location
	@ to write the string representation of the integer. This pointer
	@ is updated to point the location directly after the last byte
	@ written.
	@ r1/a2: The integer to convert to a string.
	.align	2
int_to_string:
	@ v1 stores the pointer to pointer to string
	@ v2 stores the start location in the string
	@ v3 stores the current location of the string
	push	{ v1, v2, fp, lr }
	.set	.regs_saved, 4
	add	fp, sp, .fp_reg_offset
	@ sub	sp, 4 @ align stack pointer
	

	@ add - and negate the number if < 0
	cmp	a2, 0
	bge	.int_to_string_positive
	neg	a2, a2
	ldr	r2, [a1]
	mov	r3, '-
	str	r3, [r2], 1
	str	r2, [a1]
.int_to_string_positive:
	@ v1 is the pointer to pointers
	@ v2 is the integer	
	mov	v1, a1
	mov	v2, a2
	mov	a1, v2
	bl	length_of_int

	@ save end location	
	ldr	r1, [v1]
	add	r0, r1
	str	r0, [v1]

	@ r0 is the current integer
	@ v1 is the current location
	mov	v1, r0
	mov	r0, v2

.int_to_string_loop:
	mov	a2, 10
	bl	__aeabi_idivmod	
	
	add	r1, '0
	strb	r1, [v1, -1]!
	cmp	r0, 0
	bne	.int_to_string_loop
	@ fall through
.int_to_string_end:
	sub	sp, fp, .fp_reg_offset
	pop	{ v1, v2, fp, pc }
	
	@ accepts an integer as input and returns its length.
	.align	2
length_of_int:
	push	{ v1, fp, lr }
	.set	.regs_saved, 3
	add	fp, sp, .fp_reg_offset
	sub	sp, 4

	cmp	r0, 0
	mov	v1, 0
	bge	.length_of_int_loop
	add	v1, 1
	neg	r0, r0

.length_of_int_loop:
	add	v1, 1
	mov	a2, 10
	bl	__aeabi_idiv
	cmp	r0, 0
	bne	.length_of_int_loop
	
	@ fall through
.length_of_int_end:
	mov	r0, v1 

	sub	sp, fp, .fp_reg_offset
	pop	{ v1, fp, pc }

	@ accepts a pointer to an array of integers and the length of that array.
	@ This will return the total string length, including
	@ null pointer, that would hold the result concatenated with one character between every number.
	.align	2
ints_length:
	@ v1 stores the current location in the array of integers.
	@ v2 stores the end location of the array of integers
	@ v3 is the total length so far.

	push	{ v1, v2, v3, fp, lr }
	.set	.regs_saved, 5
	add	fp, sp, .fp_reg_offset
	sub	sp, 4
	
	mov	v1, a1
	add	v2, a1, a2, lsl 2 @ v2 = a1 + (a2 << 2)
	mov	v3, 0

	cmp	v1, v2
	beq	.ints_length_end	

.ints_length_loop:
	@ we add 1 on first iteration for null pointer
	add	v3, 1  @ add 1 for delimeter
	ldr	a1, [v1], 4
	bl	length_of_int
	add	v3, r0
	cmp	v1, v2
	beq	.ints_length_end
	b	.ints_length_loop

.ints_length_end:
	mov	r0, v3
	sub	sp, fp, .fp_reg_offset
	pop	{ v1, v2, v3, fp, pc }
