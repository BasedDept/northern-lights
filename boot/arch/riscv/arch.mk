# arch.mk
# Boot stub makefile (riscv)
# Author: George Witt
# Date: 2024-02-24
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: BSD-2-Clause

CFLAGS_ARCH= -fno-pie -fno-pic -mcmodel=medany
ADAFLAGS_ARCH= -fno-pie -fno-pic -mcmodel=medany
OBJS_ARCH= arch/$(TARGET_ARCH)/head.o \
           arch/$(TARGET_ARCH)/crt0.o \
           arch/$(TARGET_ARCH)/payload.o \
           arch/$(TARGET_ARCH)/diag.o \
           arch/$(TARGET_ARCH)/riscv.o \
           arch/$(TARGET_ARCH)/riscv_sbi.o

arch/$(TARGET_ARCH)/head.o: arch/$(TARGET_ARCH)/head.S
arch/$(TARGET_ARCH)/crt0.o: arch/$(TARGET_ARCH)/crt0.c
arch/$(TARGET_ARCH)/payload.o: arch/$(TARGET_ARCH)/payload.S
arch/$(TARGET_ARCH)/riscv_sbi.o: arch/$(TARGET_ARCH)/riscv_sbi.c
arch/$(TARGET_ARCH)/riscv.o: arch/$(TARGET_ARCH)/riscv.c
arch/$(TARGET_ARCH)/diag.o: arch/$(TARGET_ARCH)/diag.c

