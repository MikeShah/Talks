	.file	"static.cpp"
	.text
.Ltext0:
	.data
	.align 32
	.type	_ZL17lookup_factorials, @object
	.size	_ZL17lookup_factorials, 80
_ZL17lookup_factorials:
	.quad	1
	.quad	2
	.quad	6
	.quad	24
	.quad	120
	.quad	720
	.quad	5040
	.quad	40320
	.quad	362880
	.quad	3628800
	.section	.rodata
.LC0:
	.string	"int main(int, char**)"
.LC1:
	.string	"static.cpp"
	.align 8
.LC2:
	.string	"lookup_factorials[5] == 720 && \"compile-time check\""
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.file 1 "static.cpp"
	.loc 1 10 33
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	.loc 1 12 3
	movq	40+_ZL17lookup_factorials(%rip), %rax
	cmpq	$720, %rax
	je	.L2
	.loc 1 12 3 is_stmt 0 discriminator 1
	leaq	.LC0(%rip), %rcx
	movl	$12, %edx
	leaq	.LC1(%rip), %rsi
	leaq	.LC2(%rip), %rdi
	call	__assert_fail@PLT
.L2:
	.loc 1 14 12 is_stmt 1
	movl	$0, %eax
	.loc 1 15 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
.Letext0:
	.file 2 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h"
	.file 3 "<built-in>"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x124
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF6
	.byte	0x4
	.long	.LASF7
	.long	.LASF8
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.string	"std"
	.byte	0x3
	.byte	0
	.long	0x4b
	.uleb128 0x3
	.long	.LASF0
	.byte	0x2
	.value	0x11e
	.byte	0x41
	.uleb128 0x4
	.byte	0x2
	.value	0x11e
	.byte	0x41
	.long	0x38
	.byte	0
	.uleb128 0x5
	.long	.LASF9
	.byte	0x2
	.value	0x120
	.byte	0xb
	.long	0x6b
	.uleb128 0x3
	.long	.LASF0
	.byte	0x2
	.value	0x122
	.byte	0x41
	.uleb128 0x4
	.byte	0x2
	.value	0x122
	.byte	0x41
	.long	0x58
	.byte	0
	.uleb128 0x6
	.long	0x82
	.long	0x7b
	.uleb128 0x7
	.long	0x7b
	.byte	0x9
	.byte	0
	.uleb128 0x8
	.byte	0x8
	.byte	0x7
	.long	.LASF1
	.uleb128 0x8
	.byte	0x8
	.byte	0x5
	.long	.LASF2
	.uleb128 0x9
	.long	.LASF10
	.byte	0x1
	.byte	0x4
	.byte	0x12
	.long	0x6b
	.uleb128 0x9
	.byte	0x3
	.quad	_ZL17lookup_factorials
	.uleb128 0xa
	.long	.LASF11
	.byte	0x1
	.byte	0xa
	.byte	0x5
	.long	0xf3
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.long	0xf3
	.uleb128 0xb
	.long	.LASF3
	.byte	0x1
	.byte	0xa
	.byte	0xe
	.long	0xf3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xb
	.long	.LASF4
	.byte	0x1
	.byte	0xa
	.byte	0x1a
	.long	0xfa
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xc
	.long	.LASF12
	.long	0x122
	.uleb128 0x9
	.byte	0x3
	.quad	.LC0
	.byte	0
	.uleb128 0xd
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0xe
	.byte	0x8
	.long	0x100
	.uleb128 0xe
	.byte	0x8
	.long	0x106
	.uleb128 0x8
	.byte	0x1
	.byte	0x6
	.long	.LASF5
	.uleb128 0xf
	.long	0x106
	.uleb128 0x6
	.long	0x10d
	.long	0x122
	.uleb128 0x7
	.long	0x7b
	.byte	0x15
	.byte	0
	.uleb128 0xf
	.long	0x112
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x39
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x39
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x89
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x3a
	.byte	0
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x18
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x39
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x6c
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF1:
	.string	"long unsigned int"
.LASF9:
	.string	"__gnu_cxx"
.LASF4:
	.string	"argv"
.LASF8:
	.string	"/home/mike/Talks/2023/2023_corecpp"
.LASF6:
	.string	"GNU C++17 10.3.0 -mtune=generic -march=x86-64 -g -std=c++2a -fasynchronous-unwind-tables -fstack-protector-strong"
.LASF3:
	.string	"argc"
.LASF12:
	.string	"__PRETTY_FUNCTION__"
.LASF5:
	.string	"char"
.LASF7:
	.string	"static.cpp"
.LASF11:
	.string	"main"
.LASF0:
	.string	"__cxx11"
.LASF10:
	.string	"lookup_factorials"
.LASF2:
	.string	"long long int"
	.ident	"GCC: (Ubuntu 10.3.0-1ubuntu1~18.04~1) 10.3.0"
	.section	.note.GNU-stack,"",@progbits
