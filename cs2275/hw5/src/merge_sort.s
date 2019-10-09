	.eqv	.fp_reg_offset, 4*.regs_saved - 4

	.syntax	unified
	.text
	.align	2
	.arm
	.global merge_sort

	@ Sorts an array of integers using merge sort.
	@
	@ r0/a1: A pointer to an array of intgers
	@ r1/a2: The length of the array.
	@
	@ Returns r0/a1. The array is sorted.
merge_sort:
	push	{ v1, v2, v3, fp, lr }
	.set	.regs_saved, 5
	add	fp, sp, .fp_reg_offset
	sub	sp, 4	

	@ the array is automatically sorted if it is 1 length or less.
	cmp	a2, 1
	ble	.merge_sort_end
	
	@ v1 = pointer to start of array.
	@ v2 = pointer to middle
	@ v3 = pointer to end
	mov	v1, a1

	@ left shift by two because each integer is 4 bytes.
	add	v3, a1, a2, lsl 2

	@ right shift to divide by two to get middle index.
	lsr	v2, a2, 1

	@ left shift by two again because each integer is 4 bytes
	add	v2, a1, v2, lsl 2

	mov	a1, v1
	sub	a2, v2, v1
	lsr	a2, 2
	bl	merge_sort

	mov	a1, v2
	sub	a2, v3, v2
	lsr	a2, 2
	bl	merge_sort

	@ would probably be better to use the same array to do all the merging
	@ instead of allocating a new one each time.
	mov	a1, v1
	mov	a2, v2
	mov	a3, v3
	bl	merge

.merge_sort_end:
	mov	r0, v1

	sub	sp, fp, .fp_reg_offset
	pop	{ v1, v2, v3, fp, pc }

	@ Performs the merge portion of merge sort.
	@
	@ Would probably improve performance to not allocate an
	@ array for each merge but to instead pass one in.
	@
	@ r0/a1: A pointer to the start of the area to merge
	@ r1/a2: A pointer to the start of the second area to merge/end of first area.
	@ r2/a3: A pointer to the end of the second area to merge.
merge:
	push	{ v1, v2, v3, v4, v5, fp, lr }
	.set	.regs_saved, 7
	add	fp, sp, .fp_reg_offset
	sub	sp, 4  @ keep double word aligned

	mov	v1, a1
	mov	v2, a2
	mov	v3, a3

	@ first create buffer to merge into
	sub	r0, v3, v1
	bl	malloc
	cmp	r0, 0
	beq	.merge_end

	@ r1 points at current location in copy buffer
	@ r2 points at current location in first half of input
	@ r3 points at current location in second half of input
	mov	r1, r0
	mov	r2, v1
	mov	r3, v2

	@ loop through and merge into copy buffer.
.merge_loop:
	@ jump to faster loops if one input half is empty
	cmp	r2, v2
	beq	.first_gone

	cmp	r3, v3
	beq	.second_gone

	@ compare the two front elements being merged
	ldr	v4, [r2]
	ldr	v5, [r3]
	cmp	v4, v5

	bgt	.second_smaller
.first_smaller:
	str	v4, [r1], 4
	add	r2, 4
	b	.merge_loop
.second_smaller:
	str	v5, [r1], 4
	add	r3, 4
	b	.merge_loop

.first_gone:
	cmp	r3, v3
	beq	.merged
	ldr	v5, [r3], 4
	str	v5, [r1], 4
	b	.first_gone
.second_gone:
	cmp	r2, v2
	beq	.merged
	ldr	v4, [r2], 4
	str	v4, [r1], 4
	b	.second_gone

	@ copy copy buffer back into original array.
.merged:
	mov	r1, r0
.copy_loop:
	cmp	v1, v3
	beq	.copied
	ldr	r2, [r1], 4
	str	r2, [v1], 4
	b	.copy_loop

.copied:
	bl	free

.merge_end:
	sub	sp, fp, .fp_reg_offset
	pop	{ v1, v2, v3, v4, v5, fp, pc }
