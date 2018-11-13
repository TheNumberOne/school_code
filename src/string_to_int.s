	.eqv	.fp_reg_offset, .regs_saved*4 - 4

	.syntax	unified
	.text
	.align	2
	.arm
	.global string_to_int
	.global strings_to_ints

@ accepts a null terminated array of strings as input.
@ Allocates an array of integers of the same size and
@ parses each string. Returns a pointer to the array
@ and the number of elements.
strings_to_ints:
	@ v1 holds a pointer to a location in the array
	@ of strings. v2 holds a pointer to the start of
	@ the returned int array. v3 holds the current location
	@ in that array.
	push 	{ v1, v2, v3, fp, lr }
	.set 	.regs_saved, 5
	add	fp, sp, .fp_reg_offset
	sub	sp, 4  @ keep the stack double word aligned

	mov	v1, a1

	@ first count the number of elements in the strings
	@ r0 is the current position in the string array
	@ r1 is the current string pointer
	ldr	r1, [r0]
.length_loop:
	cmp	r1, 0
	beq	.length_loop_end
	ldr	r1, [r0, 4]!
	b	.length_loop
.length_loop_end:
	@ subtract the initial position to get the total length.
	sub	r0, v1

	bl	malloc
	@ return null if out of memory
	cmp	r0, 0
	beq	.return_null

	mov	v2, r0
	mov	v3, r0

.parse_loop:
	ldr	a1, [v1], 4
	cmp	a1, 0
	beq	.return_ints
	bl	string_to_int
	str	r0, [v3], 4
	b	.parse_loop

.return_ints:
	mov	r0, v2
	sub	r1, v3, v2 @ subtract endpoings of array
	lsr	r1, r1, 2  @ r1 >>= 2. Divides by 4.
	@ fall through
.return:
	sub	sp, fp, .fp_reg_offset
	pop	{ v1, v2, v4, fp, pc }
.return_null:
	mov	r0, 0
	mov	r1, 0
	b	.return

	.align 2
@ accepts a single argument,
@ a pointer to a string.
@ This parses the string into an integer.
@ if the string can't be parsed, returns -1.
string_to_int:
	@ r0 is the integer currently being parsed
	@ r1 is the pointer to the string
	@ r2 is the current character
	mov	r1, a1
	mov	r0, 0
.loop:
	ldrb	r2, [r1], 1

	@ stop at the end of the string
	cmp	r2, 0
	beq	.end

	@ make sure it's a valid number
	cmp	r2, '0
	blt	.invalid
	cmp	r2, '9
	bgt	.invalid

	@ r0 = 10 * r0 + (r3 - '0')
	mov	r3, 10
	mul	r0, r3
	sub	r2, '0
	add	r0, r2
	b	.loop

.invalid:
	mov	r0, -1
.end:
	bx	lr
