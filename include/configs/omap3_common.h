/*
 * (C) Copyright 2012
 * Texas Instruments Incorporated.
 * Tom Rini <trini@ti.com>
 *
 * TI OMAP3 (and AM/DM related parts) common configuration settings
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_OMAP3_COMMON_H
#define __CONFIG_OMAP3_COMMON_H

/*
 * A TI OMAP3 (or similar) core
 */
#define CONFIG_OMAP
#define CONFIG_OMAP34XX

/* Get CPU defs */
#include <asm/arch/cpu.h>
#include <asm/arch/omap3.h>

/* Display CPU and Board Info */
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

/* Clock Defines */
#ifndef V_OSCK
#define V_OSCK			26000000	/* Clock output from T2 */
#endif
#ifndef V_SCLK
#define V_SCLK			(V_OSCK >> 1)
#endif

/* no support for IRQs */
#undef CONFIG_USE_IRQ

/* Portions of the init sequence that we want */
#define CONFIG_MISC_INIT_R

/* Enable support for both device trees and ATAGS */
#define CONFIG_OF_LIBFDT
#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_REVISION_TAG

/*
 * A minimum size of malloc() pool.  There are two common large users here.
 * One of which is 'saveenv' which requires a pool of the size of the
 * environment (CONFIG_ENV_SIZE).  A second user is UBI which requires
 * at least 512KiB.  We default to 1MB worth of pool.  These can be
 * overridden by the board if needed.
 */
#ifndef CONFIG_ENV_SIZE
#define CONFIG_ENV_SIZE			(128 << 10)
#endif
#ifndef CONFIG_SYS_MALLOC_LEN
#define CONFIG_SYS_MALLOC_LEN		(1024 << 10)
#endif

/*
 * Default serial port configuration is an NS16550-compatible UART.
 * Boards can override this as needed with CONFIG_SERIAL_MULTI
 */
#ifndef CONFIG_SERIAL_MULTI
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		48000000
#define CONFIG_SYS_BAUDRATE_TABLE	{4800, 9600, 19200, 38400, 57600,\
					115200}
#endif

/*
 * I2C support.  We default to standard speed but allow boards to specify
 * fast or high-speed.
 * */
#define CONFIG_CMD_I2C
#define CONFIG_HARD_I2C	
#ifndef CONFIG_SYS_I2C_SPEED
#define CONFIG_SYS_I2C_SPEED		100000
#endif
#define CONFIG_DRIVER_OMAP34XX_I2C

/* MMC */
#define CONFIG_CMD_MMC
#if defined(CONFIG_CMD_MMC)
#define CONFIG_GENERIC_MMC
#define CONFIG_MMC
#define CONFIG_OMAP_HSMMC
#define CONFIG_DOS_PARTITION
#endif

/*
 * Default NAND information.
 */
#if defined(CONFIG_CMD_NAND)
#define CONFIG_SYS_NO_FLASH
#define CONFIG_SYS_NAND_QUIET_TEST
#define CONFIG_NAND_OMAP_GPMC
#define CONFIG_SYS_NAND_ADDR		NAND_BASE
#define CONFIG_SYS_NAND_BASE		NAND_BASE
#define GPMC_NAND_ECC_LP_x16_LAYOUT
/* At most, one NAND device will be supported. */
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#endif

/*
 * Environmnet
 */
#define CONFIG_ENV_OVERWRITE	/* Allow to overwrite serial and ethaddr */

#endif /* __CONFIG_OMAP3_COMMON_H */
