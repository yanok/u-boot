/*
 * sys_proto.h
 *
 * System information header
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

#ifndef _SYS_PROTO_H_
#define _SYS_PROTO_H_

#include <asm/omap_common.h>

#define BOARD_REV_ID	0x0

u32 get_cpu_rev(void);
u32 get_sysboot_value(void);

#ifdef CONFIG_DISPLAY_CPUINFO
int print_cpuinfo(void);
#endif

u32 get_device_type(void);
void setup_clocks_for_console(void);

/*
 * This is used to verify if the configuration header
 * was executed by Romcode prior to control of transfer
 * to the bootloader. SPL is responsible for saving and
 * passing this to the u-boot.
 */
extern struct omap_boot_parameters boot_params;

static inline u8 uboot_loaded_by_spl(void)
{
	/*
	 * u-boot can be running from sdram either because of configuration
	 * Header or by SPL. If because of CH, then the romcode sets the
	 * CHSETTINGS executed bit to true in the boot parameter structure that
	 * it passes to the bootloader.This parameter is stored in the ch_flags
	 * variable by both SPL and u-boot.Check out for CHSETTINGS, which is a
	 * mandatory section if CH is present.
	 */
	if ((boot_params.ch_flags) & (CH_FLAGS_CHSETTINGS))
		return 0;
	else
		return running_from_sdram();
}

/*
 * The basic hardware init of OMAP(s_init()) can happen in 4
 * different contexts:
 *  1. SPL running from SRAM
 *  2. U-Boot running from FLASH
 *  3. Non-XIP U-Boot loaded to SDRAM by SPL
 *  4. Non-XIP U-Boot loaded to SDRAM by ROM code using the
 *     Configuration Header feature
 *
 * This function finds this context.
 * Defining as inline may help in compiling out unused functions in SPL
 */
static inline u32 omap_hw_init_context(void)
{
#ifdef CONFIG_SPL_BUILD
	return OMAP_INIT_CONTEXT_SPL;
#else
	if (uboot_loaded_by_spl())
		return OMAP_INIT_CONTEXT_UBOOT_AFTER_SPL;
	else if (running_from_sdram())
		return OMAP_INIT_CONTEXT_UBOOT_AFTER_CH;
	else
		return OMAP_INIT_CONTEXT_UBOOT_FROM_NOR;
#endif
}
#endif
