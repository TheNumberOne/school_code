	.eqv	.fp_reg_offset, 4*.regs_saved - 4

	.syntax	unified
	.text
	.align	2
	.arm
	.global merge_sort

@ takes as input a pointer to an integer array and the length of the
@ array. Sorts the array and returns nothing.
merge_sort:
	push	{ fp, lr }
	.set	.regs_saved, 2


	pop	{ fp, lr }
