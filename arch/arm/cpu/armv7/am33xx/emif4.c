/*
 * emif4.c
 *
 * AM33XX emif4 configuration file
 *
 * Copyright (C) 2011, Texas Instruments, Incorporated - http://www.ti.com/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR /PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <common.h>
#include <asm/arch/cpu.h>
#include <asm/arch/ddr_defs.h>
#include <asm/arch/hardware.h>
#include <asm/arch/clock.h>
#include <asm/io.h>
#include <asm/omap_common.h>

DECLARE_GLOBAL_DATA_PTR;

#ifndef CONFIG_SYS_EMIF_PRECALCULATED_TIMING_REGS
u32 *const T_num = (u32 *)AM33XX_SRAM_SCRATCH_EMIF_T_NUM;
u32 *const T_den = (u32 *)AM33XX_SRAM_SCRATCH_EMIF_T_DEN;
u32 *const emif_sizes = (u32 *)AM33XX_SRAM_SCRATCH_EMIF_SIZE;
#endif
