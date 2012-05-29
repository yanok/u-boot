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

DECLARE_GLOBAL_DATA_PTR;

struct ddr_regs *ddrregs = (struct ddr_regs *)DDR_PHY_BASE_ADDR;
struct vtp_reg *vtpreg = (struct vtp_reg *)VTP0_CTRL_ADDR;
struct ddr_ctrl *ddrctrl = (struct ddr_ctrl *)DDR_CTRL_ADDR;


int dram_init(void)
{
	/* dram_init must store complete ramsize in gd->ram_size */
	gd->ram_size = get_ram_size(
			(void *)CONFIG_SYS_SDRAM_BASE,
			CONFIG_MAX_RAM_BANK_SIZE);
	return 0;
}

void dram_init_banksize(void)
{
	gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE;
	gd->bd->bi_dram[0].size = gd->ram_size;
}


#ifdef CONFIG_SPL_BUILD
static void config_vtp(void)
{
	writel(readl(&vtpreg->vtp0ctrlreg) | VTP_CTRL_ENABLE,
			&vtpreg->vtp0ctrlreg);
	writel(readl(&vtpreg->vtp0ctrlreg) & (~VTP_CTRL_START_EN),
			&vtpreg->vtp0ctrlreg);
	writel(readl(&vtpreg->vtp0ctrlreg) | VTP_CTRL_START_EN,
			&vtpreg->vtp0ctrlreg);

	/* Poll for READY */
	while ((readl(&vtpreg->vtp0ctrlreg) & VTP_CTRL_READY) !=
			VTP_CTRL_READY)
		;
}

#define DDR3_RATIO		0x40
#define DDR3_CMD_FORCE		0x00
#define DDR3_CMD_DELAY		0x00
#define DDR3_EMIF_READ_LATENCY	0x06
#define DDR3_EMIF_TIM1		0x0888A39B
#define DDR3_EMIF_TIM2		0x26337FDA
#define	DDR3_EMIF_TIM3		0x501F830F
#define DDR3_EMIF_SDCFG		0x61C04AB2
#define DDR3_EMIF_SDREF		0x0000093B
#define DDR3_ZQ_CFG		0x50074BE4
#define DDR3_DLL_LOCK_DIFF	0x1
#define DDR3_RD_DQS		0x3B
#define DDR3_PHY_FIFO_WE	0x100
#define DDR3_INVERT_CLKOUT	0x1
#define DDR3_WR_DQS		0x85
#define DDR3_PHY_WRLVL		0x00
#define DDR3_PHY_GATELVL	0x00
#define DDR3_PHY_WR_DATA	0xC1
#define	DDR3_PHY_RANK0_DELAY	0x01
#define DDR3_PHY_DLL_LOCK_DIFF	0x0
#define DDR3_IOCTRL_VALUE	0x18B

#define	CMD0_CTRL_SLAVE_RATIO_0		(DDR_PHY_BASE_ADDR + 0x01C)
#define	CMD0_INVERT_CLKOUT_0		(DDR_PHY_BASE_ADDR + 0x02C)

#define	CMD1_CTRL_SLAVE_RATIO_0		(DDR_PHY_BASE_ADDR + 0x050)
#define	CMD1_INVERT_CLKOUT_0		(DDR_PHY_BASE_ADDR + 0x060)

#define	CMD2_CTRL_SLAVE_RATIO_0		(DDR_PHY_BASE_ADDR + 0x084)
#define	CMD2_INVERT_CLKOUT_0		(DDR_PHY_BASE_ADDR + 0x094)
static void phy_config_cmd(void)
{
	struct cmd_control cmd;
	cmd.cmd0csratio = DDR3_RATIO;
	cmd.cmd0csforce = CMD_FORCE;
	cmd.cmd0csdelay = CMD_DELAY;
	cmd.cmd0dldiff = DDR3_DLL_LOCK_DIFF;
	cmd.cmd0iclkout = DDR3_INVERT_CLKOUT;

	cmd.cmd1csratio = DDR3_RATIO;
	cmd.cmd1csforce = CMD_FORCE;
	cmd.cmd1csdelay = CMD_DELAY;
	cmd.cmd1dldiff = DDR3_DLL_LOCK_DIFF;
	cmd.cmd1iclkout = DDR3_INVERT_CLKOUT;

	cmd.cmd2csratio = DDR3_RATIO;
	cmd.cmd2csforce = CMD_FORCE;
	cmd.cmd2csdelay = CMD_DELAY;
	cmd.cmd2dldiff = DDR3_DLL_LOCK_DIFF;
	cmd.cmd2iclkout = DDR3_INVERT_CLKOUT;

	config_cmd_ctrl(&cmd);
}

#define DATA0_RD_DQS_SLAVE_RATIO_0	(DDR_PHY_BASE_ADDR + 0x0C8)
#define	DATA0_WR_DQS_SLAVE_RATIO_0	(DDR_PHY_BASE_ADDR + 0x0DC)
#define	DATA0_FIFO_WE_SLAVE_RATIO_0	(DDR_PHY_BASE_ADDR + 0x108)
#define	DATA0_WR_DATA_SLAVE_RATIO_0	(DDR_PHY_BASE_ADDR + 0x120)
#define DATA1_RD_DQS_SLAVE_RATIO_0	(DDR_PHY_BASE_ADDR + 0x16C)
#define DATA1_WR_DQS_SLAVE_RATIO_0	(DDR_PHY_BASE_ADDR + 0x180)
#define DATA1_FIFO_WE_SLAVE_RATIO_0 	(DDR_PHY_BASE_ADDR + 0x1AC)
#define DATA1_WR_DATA_SLAVE_RATIO_0	(DDR_PHY_BASE_ADDR + 0x1C4)
static void phy_config_data(void)
{
	writel(DDR3_RD_DQS, DATA0_RD_DQS_SLAVE_RATIO_0);
	writel(DDR3_WR_DQS, DATA0_WR_DQS_SLAVE_RATIO_0);
	writel(DDR3_PHY_FIFO_WE, DATA0_FIFO_WE_SLAVE_RATIO_0);
	writel(DDR3_PHY_WR_DATA, DATA0_WR_DATA_SLAVE_RATIO_0);

	writel(DDR3_RD_DQS, DATA1_RD_DQS_SLAVE_RATIO_0);
	writel(DDR3_WR_DQS, DATA1_WR_DQS_SLAVE_RATIO_0);
	writel(DDR3_PHY_FIFO_WE, DATA1_FIFO_WE_SLAVE_RATIO_0);
	writel(DDR3_PHY_WR_DATA, DATA1_WR_DATA_SLAVE_RATIO_0);
}

static void config_emif_ddr3(void)
{
#define EMIF4_0_SDRAM_CONFIG            (EMIF4_0_CFG_BASE + 0x08)
#define EMIF4_0_SDRAM_REF_CTRL          (EMIF4_0_CFG_BASE + 0x10)
#define EMIF4_0_SDRAM_REF_CTRL_SHADOW   (EMIF4_0_CFG_BASE + 0x14)
#define EMIF4_0_SDRAM_TIM_1             (EMIF4_0_CFG_BASE + 0x18)
#define EMIF4_0_SDRAM_TIM_1_SHADOW      (EMIF4_0_CFG_BASE + 0x1C)
#define EMIF4_0_SDRAM_TIM_2             (EMIF4_0_CFG_BASE + 0x20)
#define EMIF4_0_SDRAM_TIM_2_SHADOW      (EMIF4_0_CFG_BASE + 0x24)
#define EMIF4_0_SDRAM_TIM_3             (EMIF4_0_CFG_BASE + 0x28)
#define EMIF4_0_SDRAM_TIM_3_SHADOW      (EMIF4_0_CFG_BASE + 0x2C)
#define EMIF0_0_ZQ_CONFIG		(EMIF4_0_CFG_BASE + 0xC8)
#define EMIF4_0_DDR_PHY_CTRL_1          (EMIF4_0_CFG_BASE + 0xE4)
#define EMIF4_0_DDR_PHY_CTRL_1_SHADOW   (EMIF4_0_CFG_BASE + 0xE8)
#define EMIF4_0_DDR_PHY_CTRL_2          (EMIF4_0_CFG_BASE + 0xEC)
	/*Program EMIF0 CFG Registers*/
	writel(DDR3_EMIF_READ_LATENCY, EMIF4_0_DDR_PHY_CTRL_1);
	writel(DDR3_EMIF_READ_LATENCY, EMIF4_0_DDR_PHY_CTRL_1_SHADOW);
	writel(DDR3_EMIF_READ_LATENCY, EMIF4_0_DDR_PHY_CTRL_2);
	writel(DDR3_EMIF_TIM1, EMIF4_0_SDRAM_TIM_1);
	writel(DDR3_EMIF_TIM1, EMIF4_0_SDRAM_TIM_1_SHADOW);
	writel(DDR3_EMIF_TIM2, EMIF4_0_SDRAM_TIM_2);
	writel(DDR3_EMIF_TIM2, EMIF4_0_SDRAM_TIM_2_SHADOW);
	writel(DDR3_EMIF_TIM3, EMIF4_0_SDRAM_TIM_3);
	writel(DDR3_EMIF_TIM3, EMIF4_0_SDRAM_TIM_3_SHADOW);


	writel(DDR3_EMIF_SDREF, EMIF4_0_SDRAM_REF_CTRL);
	writel(DDR3_EMIF_SDREF, EMIF4_0_SDRAM_REF_CTRL_SHADOW);
	writel(DDR3_ZQ_CFG, EMIF0_0_ZQ_CONFIG);

	writel(DDR3_EMIF_SDCFG, EMIF4_0_SDRAM_CONFIG);

}

void config_ddr(void)
{
	struct ddr_ioctrl ioctrl;

	enable_emif_clocks();

	config_vtp();

	phy_config_cmd();
	phy_config_data();

	/* set IO control registers */
#define DDR3_IOCTRL_VALUE	0x18B
	ioctrl.cmd1ctl = DDR3_IOCTRL_VALUE;
	ioctrl.cmd2ctl = DDR3_IOCTRL_VALUE;
	ioctrl.cmd3ctl = DDR3_IOCTRL_VALUE;
	ioctrl.data1ctl = DDR3_IOCTRL_VALUE;
	ioctrl.data2ctl = DDR3_IOCTRL_VALUE;
	config_io_ctrl(&ioctrl);

	/* IOs set for DDR3 */
#define MDDR_SEL_DDR2		0xefffffff
	writel(readl(ddrctrl) & MDDR_SEL_DDR2, ddrctrl);
	/* CKE controlled by EMIF/DDR_PHY */
#define CKE_NORMAL_OP		0x00000001
	writel(readl(DDR_CKE_CTRL_ADDR) | CKE_NORMAL_OP, DDR_CKE_CTRL_ADDR);

	config_emif_ddr3();
}
#endif
