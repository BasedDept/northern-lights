/**
 * @file arch/riscv/sbi_const.h
 * @brief RISC-V asm
 * @author Anup Patel
 * @date 2024-11-16
 *
 * Copyright (c) 2024 Western Digital Corporation or its affiliates.
 * SPDX-License-Identifier: BSD-2-Clause
 */
#ifndef BOOT_ARCH_RISCV_SBI_CONST_H
#define BOOT_ARCH_RISCV_SBI_CONST_H

/*
 * Some constant macros are used in both assembler and
 * C code.  Therefore we cannot annotate them always with
 * 'UL' and other type specifiers unilaterally.  We
 * use the following macros to deal with this.
 *
 * Similarly, _AT() will cast an expression with a type in C, but
 * leave it unchanged in asm.
 */

/* clang-format off */

#ifdef __ASSEMBLER__
#define _AC(X,Y)	X
#define _AT(T,X)	X
#else
#define __AC(X,Y)	(X##Y)
#define _AC(X,Y)	__AC(X,Y)
#define _AT(T,X)	((T)(X))
#endif

#define _UL(x)		(_AC(x, UL))
#define _ULL(x)		(_AC(x, ULL))

#define _BITUL(x)	(_UL(1) << (x))
#define _BITULL(x)	(_ULL(1) << (x))

#define UL(x)		(_UL(x))
#define ULL(x)		(_ULL(x))

#define __STR(s)	#s
#define STRINGIFY(s)	__STR(s)

/* clang-format on */

#endif
