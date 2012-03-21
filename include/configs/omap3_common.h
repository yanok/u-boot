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

#endif /* __CONFIG_OMAP3_COMMON_H */
