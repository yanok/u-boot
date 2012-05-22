/*
 * DMM programming
 *
 * (C) Copyright 2010-2012
 * Texas Instruments, <www.ti.com>
 *
 * Aneesh V <aneesh@ti.com>
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

#include <common.h>
#include <asm/emif.h>
#include <asm/arch/clocks.h>
#include <asm/arch/sys_proto.h>
#include <asm/omap_common.h>
#include <asm/utils.h>

void dmm_init(u32 base)
{
	const struct dmm_lisa_map_regs *lisa_map_regs;

#ifdef CONFIG_SYS_EMIF_PRECALCULATED_TIMING_REGS
	emif_get_dmm_regs(&lisa_map_regs);
#else
	u32 emif1_size, emif2_size, mapped_size, section_map = 0;
	u32 section_cnt, sys_addr;
	struct dmm_lisa_map_regs lis_map_regs_calculated = {0};

	mapped_size = 0;
	section_cnt = 3;
	sys_addr = CONFIG_SYS_SDRAM_BASE;
	emif1_size = emif_sizes[0];
	emif2_size = emif_sizes[1];
	debug("emif1_size 0x%x emif2_size 0x%x\n", emif1_size, emif2_size);

	if (!emif1_size && !emif2_size)
		return;

	/* symmetric interleaved section */
	if (emif1_size && emif2_size) {
		mapped_size = min(emif1_size, emif2_size);
		section_map = DMM_LISA_MAP_INTERLEAVED_BASE_VAL;
		section_map |= 0 << EMIF_SDRC_ADDR_SHIFT;
		/* only MSB */
		section_map |= (sys_addr >> 24) <<
				EMIF_SYS_ADDR_SHIFT;
		section_map |= get_dmm_section_size_map(mapped_size * 2)
				<< EMIF_SYS_SIZE_SHIFT;
		lis_map_regs_calculated.dmm_lisa_map_3 = section_map;
		emif1_size -= mapped_size;
		emif2_size -= mapped_size;
		sys_addr += (mapped_size * 2);
		section_cnt--;
	}

	/*
	 * Single EMIF section(we can have a maximum of 1 single EMIF
	 * section- either EMIF1 or EMIF2 or none, but not both)
	 */
	if (emif1_size) {
		section_map = DMM_LISA_MAP_EMIF1_ONLY_BASE_VAL;
		section_map |= get_dmm_section_size_map(emif1_size)
				<< EMIF_SYS_SIZE_SHIFT;
		/* only MSB */
		section_map |= (mapped_size >> 24) <<
				EMIF_SDRC_ADDR_SHIFT;
		/* only MSB */
		section_map |= (sys_addr >> 24) << EMIF_SYS_ADDR_SHIFT;
		section_cnt--;
	}
	if (emif2_size) {
		section_map = DMM_LISA_MAP_EMIF2_ONLY_BASE_VAL;
		section_map |= get_dmm_section_size_map(emif2_size) <<
				EMIF_SYS_SIZE_SHIFT;
		/* only MSB */
		section_map |= mapped_size >> 24 << EMIF_SDRC_ADDR_SHIFT;
		/* only MSB */
		section_map |= sys_addr >> 24 << EMIF_SYS_ADDR_SHIFT;
		section_cnt--;
	}

	if (section_cnt == 2) {
		/* Only 1 section - either symmetric or single EMIF */
		lis_map_regs_calculated.dmm_lisa_map_3 = section_map;
		lis_map_regs_calculated.dmm_lisa_map_2 = 0;
		lis_map_regs_calculated.dmm_lisa_map_1 = 0;
	} else {
		/* 2 sections - 1 symmetric, 1 single EMIF */
		lis_map_regs_calculated.dmm_lisa_map_2 = section_map;
		lis_map_regs_calculated.dmm_lisa_map_1 = 0;
	}

	/* TRAP for invalid TILER mappings in section 0 */
	lis_map_regs_calculated.dmm_lisa_map_0 = DMM_LISA_MAP_0_INVAL_ADDR_TRAP;

	lisa_map_regs = &lis_map_regs_calculated;
#endif
	struct dmm_lisa_map_regs *hw_lisa_map_regs =
	    (struct dmm_lisa_map_regs *)base;

	writel(0, &hw_lisa_map_regs->dmm_lisa_map_3);
	writel(0, &hw_lisa_map_regs->dmm_lisa_map_2);
	writel(0, &hw_lisa_map_regs->dmm_lisa_map_1);
	writel(0, &hw_lisa_map_regs->dmm_lisa_map_0);

	writel(lisa_map_regs->dmm_lisa_map_3,
		&hw_lisa_map_regs->dmm_lisa_map_3);
	writel(lisa_map_regs->dmm_lisa_map_2,
		&hw_lisa_map_regs->dmm_lisa_map_2);
	writel(lisa_map_regs->dmm_lisa_map_1,
		&hw_lisa_map_regs->dmm_lisa_map_1);
	writel(lisa_map_regs->dmm_lisa_map_0,
		&hw_lisa_map_regs->dmm_lisa_map_0);

	if (omap_revision() >= OMAP4460_ES1_0) {
		hw_lisa_map_regs =
		    (struct dmm_lisa_map_regs *)MA_BASE;

		writel(lisa_map_regs->dmm_lisa_map_3,
			&hw_lisa_map_regs->dmm_lisa_map_3);
		writel(lisa_map_regs->dmm_lisa_map_2,
			&hw_lisa_map_regs->dmm_lisa_map_2);
		writel(lisa_map_regs->dmm_lisa_map_1,
			&hw_lisa_map_regs->dmm_lisa_map_1);
		writel(lisa_map_regs->dmm_lisa_map_0,
			&hw_lisa_map_regs->dmm_lisa_map_0);
	}
}
