	.file	"main.c"
	.code16gcc
	.text
	.section	.rodata
.LC0:
	.string	"help"
.LC1:
	.string	"try more"
.LC2:
	.string	"quit"
.LC3:
	.string	"impossible"
.LC4:
	.string	"not found"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$16, %esp
	movl	$0, 12(%esp)
	call	clear
.L6:
	leal	7(%esp), %eax
	movl	%eax, %ecx
	call	read
	leal	7(%esp), %eax
	movl	$.LC0, %edx
	movl	%eax, %ecx
	call	compare
	testl	%eax, %eax
	je	.L2
	movl	$.LC1, %ecx
	call	print
	movl	$nl, %ecx
	call	print
	jmp	.L3
.L2:
	leal	7(%esp), %eax
	movl	$.LC2, %edx
	movl	%eax, %ecx
	call	compare
	testl	%eax, %eax
	je	.L4
	movl	$.LC3, %ecx
	call	print
	movl	$nl, %ecx
	call	print
	jmp	.L3
.L4:
	movl	$.LC4, %ecx
	call	print
	movl	$nl, %ecx
	call	print
.L3:
	addl	$1, 12(%esp)
	cmpl	$12, 12(%esp)
	jne	.L6
	call	clear
	movl	$0, 12(%esp)
	jmp	.L6
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
