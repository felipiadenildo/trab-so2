	.file	"rt0.c"
	.code16gcc
	.text
	.globl	_start
	.type	_start, @function
_start:
.LFB0:
	.cfi_startproc
#APP
# 35 "rt0.c" 1
	        xorw %ax, %ax                ;        movw %ax, %ds                ;        movw %ax, %es                ;        movw %ax, %fs                ;        movw %ax, %gs                ;        movw %ax, %ss                ;        mov $__END_STACK__, %sp     ;        call main                     ; loop5:                              ;        hlt                           ;        jmp loop5                    
# 0 "" 2
#NO_APP
	nop
	ud2
	.cfi_endproc
.LFE0:
	.size	_start, .-_start
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
