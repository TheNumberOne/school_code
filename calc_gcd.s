@ Device: Rasberry Pi Model B v1.2
@ OS: Regular raspberry pi installation (not lite or retro)
@ gcc --version: gcc (Raspbian 6.3.0-18+rpi1+deb9u1) 6.3.0 20170516
@ uname -a: Linux raspberrypi 4.14.71-v7+ #1145 SMP Fri Sep 21 15:38:35 BST 2018 armv7l GNU/Linux
	.global	main
	.syntax unified
	.arm
	.text
	.align	2
main:
	push	{fp, lr}   @ push return address and old frame pointer onto the stack
	add	fp, sp, 4  @ move frame pointer to point to the first variable put onto the stack by this function

	ldr	r0, =.prompt_string   @ move the prompt into the first argument to pass
	bl	printf	   @ call printf

	.set	.a, -8
	.set	.b, -12
	sub	sp, sp, 8  @ add 8 bytes to the stack for user input
	ldr	r0, =.scan_string  @ first argument
	add	r1, fp, .a @ pointer to location to store first input
	add	r2, fp, .b @ pointer to location to store second input
	bl	scanf

	cmp	r0, 2      @ make sure that both integers were read without problem
	beq	.no_error

	ldr	r0, =.error_string
	bl	printf	
	b	end


.no_error:
	ldr	r0, [fp, .a] @ first argument
	ldr	r1, [fp, .b] @ second argument to gcd
	bl	gcd

	@ display result
	mov	r3, r0 @ move result to r3
	ldr	r1, [fp, .a] @ move arguments to r1 and r2
	ldr	r2, [fp, .b]
	ldr	r0, =.result_string
	bl	printf

.end:
	add	sp, fp, -4 @ move stack pointer so only the first two variables on the stack are there.
	pop	{fp, pc}   @ restore the old frame pointer and jump to the return address


	.section	.rodata  @ everything after this is readonly
.prompt_string:
	.asciz "Please input two integers separated by a comma: "
.scan_string:
	.asciz " %u , %u"  @ spaces added because scanf matches a space with an arbitrary amount of whitespace (including 0)
.error_string:
	.asciz "Invalid input\n"
.result_string:
	.asciz "gcd(%u, %u) = %u\n"



	.text
	.align	2
gcd:
	@ r0 = n1, r1 = n2
	push	{fp, lr}
	add	fp, sp, 4
	
	cmp r1, 0  @ does n2 == 0?
	beq	.else
	
	@ n2 != 0
	push	{r1} @ remember n2
	bl 	__aeabi_uidivmod @ puts r0 / r1 into r0 and r0 % r1 into r1

	pop	{r0} @ move n2 into first argument
	bl	gcd
	@ we would normally have to jump to the end but we don't need to because the else branch is empty.
.else:
	@ we don't need to do anything here because n1 is already in r0

	add	sp, fp, -4
	pop	{fp, pc}
