	.eqv	.fp_reg_offset, .regs_saved*4 - 4

	.syntax	unified
	.text
	.align	2
	.arm
	.global explode
	
	@ Accepts a pointer to a string and a delimeter
	@ returns a pointer to a buffer of pointers.
	@ Each pointer points to a buffer. These buffers
	@ hold the strings between the delimeters. Returns
	@ null if something went wrong.
explode:
	@ v1 is the delimeter passed in
	@ v2 is the pointer to the buffer of buffers
	@ v3 is the current location in it
	@ v4 is the current size (in bytes)

	push 	{ v1, v2, v3, v4, fp, lr }
	.set	.regs_saved, 6
	add	fp, sp, .fp_reg_offset

	sub	sp, 8
	.set	.in_offset, .fp_reg_offset + 4

	@ save arguments	
	str	a1, [fp, -.in_offset]
	mov	v1, a2

	@ allocate initial buffer
	mov	v4, 4*4
	mov	a1, 4*4 @ enough space for 4 strings.
	bl	malloc

	@ return nothing if out of memory.
	cmp	r0, 0
	beq	.explode_return_nothing

	@ save buffer pointers
	mov	v2, r0
	mov	v3, v2

.explode_loop:
	add	a1, fp, -.in_offset
	mov	a2, v1
	bl	explode_once

	@ explode_once returns 0 if there was an error
	@ or it hit the end.
	cmp	r0, 0
	beq	.last_explode

	@ store the exploded pointer into the buffer
	str	r0, [v3], 4

	@ double the size of the buffer if we've reached the end
	sub	r1, v3, v2
	cmp	r1, v4
	bne	.explode_loop
	
	@fall throught
.double_buffer:
	mov	a1, v2
	mov	a2, 2  @ double buffer size
	mul	a2, v4
	bl	realloc
	
	@ cleanup and return nothing if we get an out of memory error.
	cmp	r0, 0
	beq	.cleanup_buffer

	@ update buffer pointers and size
	mov	v2, r0
	add	v3, v2, v4
	lsl	v4, v4, 1  @ multiply current size by two
	b	.explode_loop

	
	@ v1 is the delimeter passed in
	@ v2 is the pointer to the buffer of buffers
	@ v3 is the current location in it
	@ v4 is the current size (in bytes)
.cleanup_buffer:
	@ first free every buffer in the buffer.
	cmp	v2, v3
	beq	.end_loop
	ldr	a1, [v3, -4]!
	bl	free
	b	.cleanup_buffer
.end_loop:
	@ and then free the buffer of buffers
	mov	a1, v2
	bl	free

	@ fall through	
.explode_return_nothing:
	mov	r0, 0
	b	.explode_end

.last_explode:
	@ make sure it actually read the
	@ entire input string by checking that
	@ the buffer points to a null character.
	ldr	r0, [fp, -.in_offset]
	ldrb	r0, [r0]
	cmp	r0, 0
	bne	.cleanup_buffer @ free everything and return null if there was an error.

	@ put a null pointer into the last cell of the buffer of buffers.
	mov	r0, 0
	str	r0, [v3]

	@ return the buffer of buffers/
	mov	r0, v2

	@ fall through.
.explode_end:
	sub	sp, fp, .fp_reg_offset
	pop 	{ v1, v2, v3, v4, fp, pc }


	@ Accepts a pointer to a string pointer and a delimeter
	@ character. It advanced the string pointer until it 
	@ no longer points to a delimeter. It then takes
	@ all the characters up til the next instance of the
	@ delimeter and puts that into a c string. It then
	@ returns the c string and advances the string pointer
	@ to point to the next character.
explode_once:
	@ v1 is the pointer to a string pointer
	@ v2 is the delimeter character
	@ v3 is the number of characters that we
	@ return in the returned string.
	@ v4 is the pointer to the returned string.
	push 	{ v1, v2, v3, v4, fp, lr }
	.set .regs_saved, 6
	add	fp, sp, .fp_reg_offset
	@ sub	sp, 4 @ align on 8 byte boundary	

	@ save function arguments to registers
	mov	v1, a1
	mov	v2, a2

	bl	advance_past

	@ see how many characters to return
	ldr	a1, [v1]
	mov	a2, v2	
	bl	look_ahead

	@ return a null string if there is nothing left
	cmp	r0, 0
	beq	.explode_once_return_nothing
	@ save result
	mov	v3, r0
	@ add one for null character
	add	r0, 1
	bl	malloc
	
	@ return nothing if we run out of memory
	cmp	r0, 0
	beq	.explode_once_return_nothing
	
	@ save string pointer to register
	mov	v4, r0

	@ copy the contents from the buffer
	ldr	a1, [v1]
	mov	a2, v4
	mov	a3, v3
	bl	copy

	@ put null pointer into last character
	mov	r0, 0
	strb	r0, [v4, +v3]

	@ move the buffer pointer forwards.
	ldr	r0, [v1]
	add	r0, v3
	str	r0, [v1]

	@ return the buffer
	mov	r0, v4
	@ fall-through
.explode_once_end:
	sub	sp, fp, .fp_reg_offset
	pop	{ v1, v2, v3, v4, fp, pc }

.explode_once_return_nothing:
	mov	r0, 0
	b	.explode_end

@ this function accepts two arguments. a pointer to a string pointer
@ and a character. It will advance the string pointer past all
@ instances of that character. Returns nothing
advance_past:
	@ r0 is the pointer to the string pointer
	@ r1 is the character to advance past
	@ r2 is the current location in the string
	@ r3 is the current character at r2

	ldr	r2, [r0]

	@ load first character of string.
	ldrb	r3, [r2]
.advance_past_loop:
	@ stop if it points to a null pointer
	@ because we've reached the end of the string
	cmp	r3, 0
	beq	.advance_past_end

	@ stop if it points to a character that isn't r1
	cmp	r3, r1
	bne	.advance_past_end

	@ increment our location in the string and get next character.
	ldrb	r3, [r2, 1]!
	b	.advance_past_loop
.advance_past_end:
	
	@ save new location
	str	r2, [r0]
	bx	lr

@ accepts two arguments: a pointer to a string and a character to search
@ for. It returns the number of characters before the first instance
@ of that character or null.
look_ahead:
	@ r0 is the pointer to the string
	@ r1 is the character to search for
	@ r2 is the current location in the string
	@ r3 is the current character in the string
	mov	r2, r0
	ldrb	r3, [r2]
	@ fall through
.look_ahead_loop:
	cmp	r3, 0
	beq	.look_ahead_end
	cmp	r3, r1
	beq	.look_ahead_end
	ldrb	r3, [r2, 1]!
	b	.look_ahead_loop
.look_ahead_end:
	sub	r0, r2, r0
	bx	lr

@ accepts three arguments. The first argument is a pointer to string a.
@ the second points to string b. The third is the number of characters to
@ copy from a to b. Returns nothing.
copy:
	@ r0 is a
	@ r1 is b
	@ r2 is number of characters to copy
	@ r3 is the current character being copied
	cmp	r2, 0
	beq	.copy_end
	ldrb	r3, [r0], 1
	strb	r3, [r1], 1
	sub	r2, 1
	b	copy
.copy_end:
	bx	lr
