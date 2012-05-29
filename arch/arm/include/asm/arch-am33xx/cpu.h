/*
 * cpu.h
 *
 * AM33xx specific header file
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

#ifndef _AM33XX_CPU_H
#define _AM33XX_CPU_H

#if !(defined(__KERNEL_STRICT_NAMES) || defined(__ASSEMBLY__))
#include <asm/types.h>
#endif /* !(__KERNEL_STRICT_NAMES || __ASSEMBLY__) */

#include <asm/arch/hardware.h>

#define BIT(x)				(1 << x)
#define CL_BIT(x)			(0 << x)

/* Timer register bits */
#define TCLR_ST				BIT(0)	/* Start=1 Stop=0 */
#define TCLR_AR				BIT(1)	/* Auto reload */
#define TCLR_PRE			BIT(5)	/* Pre-scaler enable */
#define TCLR_PTV_SHIFT			(2)	/* Pre-scaler shift value */
#define TCLR_PRE_DISABLE		CL_BIT(5) /* Pre-scalar disable */

/* device type */
#define DEVICE_MASK			(BIT(8) | BIT(9) | BIT(10))
#define TST_DEVICE			0x0
#define EMU_DEVICE			0x1
#define HS_DEVICE			0x2
#define GP_DEVICE			0x3

/* cpu-id for AM33XX family */
#define AM335X				0xB944
#define DEVICE_ID			0x44E10600

/* This gives the status of the boot mode pins on the evm */
#define SYSBOOT_MASK			(BIT(0) | BIT(1) | BIT(2)\
					| BIT(3) | BIT(4))

/* Reset control */
#ifdef CONFIG_AM33XX
#define PRM_RSTCTRL			0x44E00F00
#endif
#define PRM_RSTCTRL_RESET		0x01

#ifndef __KERNEL_STRICT_NAMES
#ifndef __ASSEMBLY__
/* Encapsulating core pll registers */
struct cm_wkuppll {
	unsigned int wkclkstctrl;	/* offset 0x00 */
	unsigned int wkctrlclkctrl;	/* offset 0x04 */
	unsigned int resv1[1];
	unsigned int wkl4wkclkctrl;	/* offset 0x0c */
	unsigned int resv2[4];
	unsigned int idlestdpllmpu;	/* offset 0x20 */
	unsigned int resv3[2];
	unsigned int clkseldpllmpu;	/* offset 0x2c */
	unsigned int resv4[1];
	unsigned int idlestdpllddr;	/* offset 0x34 */
	unsigned int resv5[2];
	unsigned int clkseldpllddr;	/* offset 0x40 */
	unsigned int resv6[4];
	unsigned int clkseldplldisp;	/* offset 0x54 */
	unsigned int resv7[1];
	unsigned int idlestdpllcore;	/* offset 0x5c */
	unsigned int resv8[2];
	unsigned int clkseldpllcore;	/* offset 0x68 */
	unsigned int resv9[1];
	unsigned int idlestdpllper;	/* offset 0x70 */
	unsigned int resv10[3];
	unsigned int divm4dpllcore;	/* offset 0x80 */
	unsigned int divm5dpllcore;	/* offset 0x84 */
	unsigned int clkmoddpllmpu;	/* offset 0x88 */
	unsigned int clkmoddpllper;	/* offset 0x8c */
	unsigned int clkmoddpllcore;	/* offset 0x90 */
	unsigned int clkmoddpllddr;	/* offset 0x94 */
	unsigned int clkmoddplldisp;	/* offset 0x98 */
	unsigned int clkseldpllper;	/* offset 0x9c */
	unsigned int divm2dpllddr;	/* offset 0xA0 */
	unsigned int divm2dplldisp;	/* offset 0xA4 */
	unsigned int divm2dpllmpu;	/* offset 0xA8 */
	unsigned int divm2dpllper;	/* offset 0xAC */
	unsigned int resv11[1];
	unsigned int wkup_uart0ctrl;	/* offset 0xB4 */
	unsigned int wkup_i2c0ctrl;	/* offset 0xB8 */
	unsigned int resv12[7];
	unsigned int divm6dpllcore;	/* offset 0xD8 */
};

/**
 * Encapsulating peripheral functional clocks
 * pll registers
 */
struct cm_perpll {
	unsigned int l4lsclkstctrl;	/* offset 0x00 */
	unsigned int l3sclkstctrl;	/* offset 0x04 */
	unsigned int l4fwclkstctrl;	/* offset 0x08 */
	unsigned int l3clkstctrl;	/* offset 0x0c */
	unsigned int resv1;
	unsigned int cpgmac0clkctrl;	/* offset 0x14 */
	unsigned int resv2[4];
	unsigned int emifclkctrl;	/* offset 0x28 */
	unsigned int ocmcramclkctrl;	/* offset 0x2c */
	unsigned int gpmcclkctrl;	/* offset 0x30 */
	unsigned int resv3[2];
	unsigned int mmc0clkctrl;	/* offset 0x3C */
	unsigned int elmclkctrl;	/* offset 0x40 */
	unsigned int i2c2clkctrl;	/* offset 0x44 */
	unsigned int i2c1clkctrl;	/* offset 0x48 */
	unsigned int spi0clkctrl;	/* offset 0x4C */
	unsigned int spi1clkctrl;	/* offset 0x50 */
	unsigned int resv4[3];
	unsigned int l4lsclkctrl;	/* offset 0x60 */
	unsigned int l4fwclkctrl;	/* offset 0x64 */
	unsigned int resv5[6];
	unsigned int timer2clkctrl;	/* offset 0x80 */
	unsigned int resv6[11];
	unsigned int gpio2clkctrl;	/* offset 0xB0 */
	unsigned int resv7[7];
	unsigned int emiffwclkctrl;	/* offset 0xD0 */
	unsigned int resv8[2];
	unsigned int l3instrclkctrl;	/* offset 0xDC */
	unsigned int l3clkctrl;		/* Offset 0xE0 */
	unsigned int resv9[14];
	unsigned int l4hsclkstctrl;	/* offset 0x11C */
	unsigned int l4hsclkctrl;	/* offset 0x120 */
	unsigned int resv10[8];
	unsigned int cpswclkctrl;	/* offset 0x144 */
};

/* Encapsulating Display pll registers */
struct cm_dpll {
	unsigned int resv1[2];
	unsigned int clktimer2clk;	/* offset 0x08 */
};

/* Watchdog timer registers */
struct wd_timer {
	unsigned int resv1[4];
	unsigned int wdtwdsc;	/* offset 0x010 */
	unsigned int wdtwdst;	/* offset 0x014 */
	unsigned int wdtwisr;	/* offset 0x018 */
	unsigned int wdtwier;	/* offset 0x01C */
	unsigned int wdtwwer;	/* offset 0x020 */
	unsigned int wdtwclr;	/* offset 0x024 */
	unsigned int wdtwcrr;	/* offset 0x028 */
	unsigned int wdtwldr;	/* offset 0x02C */
	unsigned int wdtwtgr;	/* offset 0x030 */
	unsigned int wdtwwps;	/* offset 0x034 */
	unsigned int resv2[3];
	unsigned int wdtwdly;	/* offset 0x044 */
	unsigned int wdtwspr;	/* offset 0x048 */
	unsigned int resv3[1];
	unsigned int wdtwqeoi;	/* offset 0x050 */
	unsigned int wdtwqstar;	/* offset 0x054 */
	unsigned int wdtwqsta;	/* offset 0x058 */
	unsigned int wdtwqens;	/* offset 0x05C */
	unsigned int wdtwqenc;	/* offset 0x060 */
	unsigned int resv4[39];
	unsigned int wdt_unfr;	/* offset 0x100 */
};

/* Timer 32 bit registers */
struct gptimer {
	unsigned int tidr;		/* offset 0x00 */
	unsigned char res1[12];
	unsigned int tiocp_cfg;		/* offset 0x10 */
	unsigned char res2[12];
	unsigned int tier;		/* offset 0x20 */
	unsigned int tistatr;		/* offset 0x24 */
	unsigned int tistat;		/* offset 0x28 */
	unsigned int tisr;		/* offset 0x2c */
	unsigned int tcicr;		/* offset 0x30 */
	unsigned int twer;		/* offset 0x34 */
	unsigned int tclr;		/* offset 0x38 */
	unsigned int tcrr;		/* offset 0x3c */
	unsigned int tldr;		/* offset 0x40 */
	unsigned int ttgr;		/* offset 0x44 */
	unsigned int twpc;		/* offset 0x48 */
	unsigned int tmar;		/* offset 0x4c */
	unsigned int tcar1;		/* offset 0x50 */
	unsigned int tscir;		/* offset 0x54 */
	unsigned int tcar2;		/* offset 0x58 */
};

/* UART Registers */
struct uart_sys {
	unsigned int resv1[21];
	unsigned int uartsyscfg;	/* offset 0x54 */
	unsigned int uartsyssts;	/* offset 0x58 */
};

/* VTP Registers */
struct vtp_reg {
	unsigned int vtp0ctrlreg;
};

/* Control Status Register */
struct ctrl_stat {
	unsigned int resv1[16];
	unsigned int statusreg;		/* ofset 0x40 */
};
#endif /* __ASSEMBLY__ */
#endif /* __KERNEL_STRICT_NAMES */

/* Timer register bits */
#define TCLR_ST				BIT(0)		/* Start=1 Stop=0 */
#define TCLR_AR				BIT(1)		/* Auto reload */
#define TCLR_PRE			BIT(5)		/* Pre-scaler enable */
#define TCLR_PTV_SHIFT			(2)		/* Pre-scaler shift value */
#define TCLR_PRE_DISABLE		CL_BIT(5)	/* Pre-scalar disable */

/* Control */
#define CONTROL_STATUS			(CTRL_BASE + 0x40)

/* device type */
#define DEVICE_MASK			(BIT(8) | BIT(9) | BIT(10))
#define TST_DEVICE			0x0
#define EMU_DEVICE			0x1
#define HS_DEVICE			0x2
#define GP_DEVICE			0x3

/* cpu-id for TI81XX family */
#define TI8168				0xb81e
#define AM335X				0xB944

#define DEVICE_ID			(CTRL_BASE + 0x0600)
/* This gives the status of the boot mode pins on the evm */
#define SYSBOOT_MASK			(BIT(0) | BIT(1) | BIT(2) |BIT(3) |BIT(4))

/* Reset control */
#define PRM_RSTCTRL			(PRCM_BASE + 0x0F00)
#define PRM_RSTCTRL_RESET		0x01

/* TI816X specific bits for PRM_DEVICE module */
#define GLOBAL_RST_COLD			BIT(1)

/* Module Offsets */
#define CM_PER				(PRCM_BASE + 0x0)
#define CM_WKUP				(PRCM_BASE + 0x400)
#define CM_DPLL				(PRCM_BASE + 0x500)
#define CM_DEVICE			(PRCM_BASE + 0x0700)
#define CM_RTC				(PRCM_BASE + 0x0800)
#define CM_CEFUSE			(PRCM_BASE + 0x0A00)
#define PRM_DEVICE			(PRCM_BASE + 0x0F00)

/* Register Offsets */
/* Core PLL ADPLLS */
#define CM_CLKSEL_DPLL_CORE		(CM_WKUP + 0x68)
#define CM_CLKMODE_DPLL_CORE		(CM_WKUP + 0x90)

/* Core HSDIV */
#define CM_DIV_M4_DPLL_CORE		(CM_WKUP + 0x80)
#define CM_DIV_M5_DPLL_CORE		(CM_WKUP + 0x84)
#define CM_DIV_M6_DPLL_CORE		(CM_WKUP + 0xD8)
#define CM_IDLEST_DPLL_CORE		(CM_WKUP + 0x5c)

/* Peripheral PLL */
#define CM_CLKSEL_DPLL_PER		(CM_WKUP + 0x9c)
#define CM_CLKMODE_DPLL_PER		(CM_WKUP + 0x8c)
#define CM_DIV_M2_DPLL_PER		(CM_WKUP + 0xAC)
#define CM_IDLEST_DPLL_PER		(CM_WKUP + 0x70)

/* Display PLL */
#define CM_CLKSEL_DPLL_DISP		(CM_WKUP + 0x54)
#define CM_CLKMODE_DPLL_DISP		(CM_WKUP + 0x98)
#define CM_DIV_M2_DPLL_DISP		(CM_WKUP + 0xA4)

/* DDR PLL */
#define CM_CLKSEL_DPLL_DDR		(CM_WKUP + 0x40)
#define CM_CLKMODE_DPLL_DDR		(CM_WKUP + 0x94)
#define CM_DIV_M2_DPLL_DDR		(CM_WKUP + 0xA0)
#define CM_IDLEST_DPLL_DDR		(CM_WKUP + 0x34)

/* MPU PLL */
#define CM_CLKSEL_DPLL_MPU		(CM_WKUP + 0x2c)
#define CM_CLKMODE_DPLL_MPU		(CM_WKUP + 0x88)
#define CM_DIV_M2_DPLL_MPU		(CM_WKUP + 0xA8)
#define CM_IDLEST_DPLL_MPU		(CM_WKUP + 0x20)

/* TIMER Clock Source Select */
#define CLKSEL_TIMER2_CLK		(CM_DPLL + 0x8)

/* Interconnect clocks */
#define CM_PER_L4LS_CLKCTRL		(CM_PER + 0x60)	/* EMIF */
#define CM_PER_L4FW_CLKCTRL		(CM_PER + 0x64)	/* EMIF FW */
#define CM_PER_L3_CLKCTRL		(CM_PER + 0xE0)	/* OCMC RAM */
#define CM_PER_L3_INSTR_CLKCTRL		(CM_PER + 0xDC)
#define CM_PER_L4HS_CLKCTRL		(CM_PER + 0x120)
#define CM_WKUP_L4WKUP_CLKCTRL		(CM_WKUP + 0x0c)/* UART0 */

/* Domain Wake UP */
#define CM_WKUP_CLKSTCTRL		(CM_WKUP + 0)	/* UART0 */
#define CM_PER_L4LS_CLKSTCTRL		(CM_PER + 0x0)	/* TIMER2 */
#define CM_PER_L3_CLKSTCTRL		(CM_PER + 0x0c)	/* EMIF */
#define CM_PER_L4FW_CLKSTCTRL		(CM_PER + 0x08)	/* EMIF FW */
#define CM_PER_L3S_CLKSTCTRL		(CM_PER + 0x4)
#define CM_PER_L4HS_CLKSTCTRL		(CM_PER + 0x011c)
#define CM_CEFUSE_CLKSTCTRL		(CM_CEFUSE + 0x0)

/* Module Enable Registers */
#define CM_PER_TIMER2_CLKCTRL		(CM_PER + 0x80)	/* Timer2 */
#define CM_WKUP_UART0_CLKCTRL		(CM_WKUP + 0xB4)/* UART0 */
#define CM_WKUP_CONTROL_CLKCTRL		(CM_WKUP + 0x4)	/* Control Module */
#define CM_PER_EMIF_CLKCTRL		(CM_PER + 0x28)	/* EMIF */
#define CM_PER_EMIF_FW_CLKCTRL		(CM_PER + 0xD0)	/* EMIF FW */
#define CM_PER_GPMC_CLKCTRL		(CM_PER + 0x30)	/* GPMC */
#define CM_PER_ELM_CLKCTRL		(CM_PER + 0x40)	/* ELM */
#define CM_PER_SPI0_CLKCTRL		(CM_PER + 0x4c) /* SPI0 */
#define CM_PER_SPI1_CLKCTRL		(CM_PER + 0x50) /* SPI1 */
#define CM_WKUP_I2C0_CLKCTRL		(CM_WKUP + 0xB8) /* I2C0 */
#define CM_PER_CPGMAC0_CLKCTRL		(CM_PER + 0x14)	/* Ethernet */
#define CM_PER_CPSW_CLKSTCTRL		(CM_PER + 0x144)/* Ethernet */
#define CM_PER_OCMCRAM_CLKCTRL		(CM_PER	+ 0x2C) /* OCMC RAM */
#define CM_PER_GPIO2_CLKCTRL		(CM_PER + 0xB0) /* GPIO2 */
#define CM_PER_UART3_CLKCTRL		(CM_PER + 0x74) /* UART3 */
#define CM_PER_I2C1_CLKCTRL		(CM_PER + 0x48) /* I2C1 */
#define CM_PER_I2C2_CLKCTRL		(CM_PER + 0x44) /* I2C2 */
#define CM_WKUP_GPIO0_CLKCTRL		(CM_WKUP + 0x8) /* GPIO0 */
#define CM_RTC_RTC_CLKCTRL		(CM_RTC + 0x0) /* RTC */

#define CM_PER_MMC0_CLKCTRL     	(CM_PER + 0x3C)
#define CM_PER_MMC1_CLKCTRL     	(CM_PER + 0xF4)
#define CM_PER_MMC2_CLKCTRL     	(CM_PER + 0xF8)

/* PRCM */
#define CM_DPLL_OFFSET			(PRCM_BASE + 0x0300)


#define CM_ALWON_WDTIMER_CLKCTRL	(PRCM_BASE + 0x158C)
#define CM_ALWON_SPI_CLKCTRL		(PRCM_BASE + 0x1590)
#define CM_ALWON_CONTROL_CLKCTRL	(PRCM_BASE + 0x15C4)

#define CM_ALWON_L3_SLOW_CLKSTCTRL	(PRCM_BASE + 0x1400)

#define CM_ALWON_GPIO_0_CLKCTRL		(PRCM_BASE + 0x155c)
#define CM_ALWON_GPIO_0_OPTFCLKEN_DBCLK (PRCM_BASE + 0x155c)

/* Ethernet */
#define CM_ETHERNET_CLKSTCTRL		(PRCM_BASE + 0x1404)
#define CM_ALWON_ETHERNET_0_CLKCTRL	(PRCM_BASE + 0x15D4)
#define CM_ALWON_ETHERNET_1_CLKCTRL	(PRCM_BASE + 0x15D8)

/* UARTs */
#define CM_ALWON_UART_0_CLKCTRL		(PRCM_BASE + 0x1550)
#define CM_ALWON_UART_1_CLKCTRL		(PRCM_BASE + 0x1554)
#define CM_ALWON_UART_2_CLKCTRL		(PRCM_BASE + 0x1558)

/* I2C */
/* Note: In ti814x I2C0 and I2C2 have common clk control */
#define CM_ALWON_I2C_0_CLKCTRL		(PRCM_BASE + 0x1564)

#define DEFAULT_UART_BASE		UART0_BASE
/* UART registers */
/*TODO:Move to a new file */
#define UART_SYSCFG			(DEFAULT_UART_BASE + 0x54)
#define UART_SYSSTS			(DEFAULT_UART_BASE + 0x58)
#define UART_LCR			(DEFAULT_UART_BASE + 0x0C)
#define UART_EFR			(DEFAULT_UART_BASE + 0x08)
#define UART_MCR			(DEFAULT_UART_BASE + 0x10)
#define UART_SCR			(DEFAULT_UART_BASE + 0x40)
#define UART_TCR			(DEFAULT_UART_BASE + 0x18)
#define UART_FCR			(DEFAULT_UART_BASE + 0x08)
#define UART_DLL			(DEFAULT_UART_BASE + 0x00)
#define UART_DLH			(DEFAULT_UART_BASE + 0x04)
#define UART_MDR			(DEFAULT_UART_BASE + 0x20)

/*DMM & EMIF4 MMR Declaration*/
/*TODO: Move to a new file */
#define DMM_LISA_MAP__0			(DMM_BASE + 0x40)
#define DMM_LISA_MAP__1			(DMM_BASE + 0x44)
#define DMM_LISA_MAP__2			(DMM_BASE + 0x48)
#define DMM_LISA_MAP__3			(DMM_BASE + 0x4C)
#define DMM_PAT_BASE_ADDR		(DMM_BASE + 0x460)

#define EMIF_MOD_ID_REV			(EMIF4_0_CFG_BASE + 0x0)
#define EMIF4_0_SDRAM_STATUS            (EMIF4_0_CFG_BASE + 0x04)
#define EMIF4_0_SDRAM_CONFIG            (EMIF4_0_CFG_BASE + 0x08)
#define EMIF4_0_SDRAM_CONFIG2           (EMIF4_0_CFG_BASE + 0x0C)
#define EMIF4_0_SDRAM_REF_CTRL          (EMIF4_0_CFG_BASE + 0x10)
#define EMIF4_0_SDRAM_REF_CTRL_SHADOW   (EMIF4_0_CFG_BASE + 0x14)
#define EMIF4_0_SDRAM_TIM_1             (EMIF4_0_CFG_BASE + 0x18)
#define EMIF4_0_SDRAM_TIM_1_SHADOW      (EMIF4_0_CFG_BASE + 0x1C)
#define EMIF4_0_SDRAM_TIM_2             (EMIF4_0_CFG_BASE + 0x20)
#define EMIF4_0_SDRAM_TIM_2_SHADOW      (EMIF4_0_CFG_BASE + 0x24)
#define EMIF4_0_SDRAM_TIM_3             (EMIF4_0_CFG_BASE + 0x28)
#define EMIF4_0_SDRAM_TIM_3_SHADOW      (EMIF4_0_CFG_BASE + 0x2C)
#define EMIF0_0_SDRAM_MGMT_CTRL         (EMIF4_0_CFG_BASE + 0x38)
#define EMIF0_0_SDRAM_MGMT_CTRL_SHD     (EMIF4_0_CFG_BASE + 0x3C)
#define EMIF0_0_ZQ_CONFIG		(EMIF4_0_CFG_BASE + 0xC8)
#define EMIF_RDWR_LVL_RMP_CTRL_REG	(EMIF4_0_CFG_BASE + 0xD8)
#define EMIF_RDWR_LVL_CTRL_REG		(EMIF4_0_CFG_BASE + 0xDC)
#define EMIF4_0_DDR_PHY_CTRL_1          (EMIF4_0_CFG_BASE + 0xE4)
#define EMIF4_0_DDR_PHY_CTRL_1_SHADOW   (EMIF4_0_CFG_BASE + 0xE8)
#define EMIF4_0_DDR_PHY_CTRL_2          (EMIF4_0_CFG_BASE + 0xEC)
#define EMIF4_0_IODFT_TLGC              (EMIF4_0_CFG_BASE + 0x60)

#define EMIF4_1_SDRAM_CONFIG		(EMIF4_1_CFG_BASE + 0x08)
#define EMIF4_1_SDRAM_CONFIG2		(EMIF4_1_CFG_BASE + 0x0C)
#define EMIF4_1_SDRAM_REF_CTRL		(EMIF4_1_CFG_BASE + 0x10)
#define EMIF4_1_SDRAM_REF_CTRL_SHADOW	(EMIF4_1_CFG_BASE + 0x14)
#define EMIF4_1_SDRAM_TIM_1		(EMIF4_1_CFG_BASE + 0x18)
#define EMIF4_1_SDRAM_TIM_1_SHADOW	(EMIF4_1_CFG_BASE + 0x1C)
#define EMIF4_1_SDRAM_TIM_2		(EMIF4_1_CFG_BASE + 0x20)
#define EMIF4_1_SDRAM_TIM_2_SHADOW	(EMIF4_1_CFG_BASE + 0x24)
#define EMIF4_1_SDRAM_TIM_3		(EMIF4_1_CFG_BASE + 0x28)
#define EMIF4_1_SDRAM_TIM_3_SHADOW	(EMIF4_1_CFG_BASE + 0x2C)
#define EMIF4_1_DDR_PHY_CTRL_1		(EMIF4_1_CFG_BASE + 0xE4)
#define EMIF4_1_DDR_PHY_CTRL_1_SHADOW	(EMIF4_1_CFG_BASE + 0xE8)
#define EMIF4_1_IODFT_TLGC		(EMIF4_1_CFG_BASE + 0x60)

#define VTP0_CTRL_REG			0x44E10E0C
#define VTP1_CTRL_REG			0x48140E10

/*EMIF4 PRCM Defintion*/
#define CM_DEFAULT_L3_FAST_CLKSTCTRL	(PRCM_BASE + 0x0508)
#define CM_DEFAULT_EMIF_0_CLKCTRL	(PRCM_BASE + 0x0520)
#define CM_DEFAULT_EMIF_1_CLKCTRL	(PRCM_BASE + 0x0524)
#define CM_DEFAULT_DMM_CLKCTRL		(PRCM_BASE + 0x0528)
#define CM_DEFAULT_FW_CLKCTRL		(PRCM_BASE + 0x052C)

/* Smartreflex Registers */
#define TI816X_SMRT_SCALE_ADDR		(CTRL_BASE + 0x06A0)
#define TI816X_SMRT_OPP_SVT_ADDR	(CTRL_BASE + 0x06A8)
#define TI816X_SMRT_OPP_HVT_ADDR	(CTRL_BASE + 0x06AC)


/* ALWON PRCM */
#define CM_ALWON_OCMC_0_CLKSTCTRL	CM_PER_L3_CLKSTCTRL
#define CM_ALWON_OCMC_0_CLKCTRL		CM_PER_OCMCRAM_CLKCTRL

#define CM_ALWON_GPMC_CLKCTRL		CM_PER_GPMC_CLKCTRL

#define SRAM0_SIZE			(0x1B400) /* 109 KB */
#define SRAM_GPMC_STACK_SIZE		(0x40)

/* GPMC related */
#define GPMC_CONFIG_CS0			(0x60)
#define GPMC_CONFIG_CS0_BASE		(GPMC_BASE + GPMC_CONFIG_CS0)
#define GPMC_CONFIG1			(0x00)
#define GPMC_CONFIG2			(0x04)
#define GPMC_CONFIG3			(0x08)
#define GPMC_CONFIG4			(0x0C)
#define GPMC_CONFIG5			(0x10)
#define GPMC_CONFIG6			(0x14)
#define GPMC_CONFIG7			(0x18)

/* PAD configuration register offsets and values for gpmc address
 * lines a12 - a26
 */
#define GPMC_A12			(CTRL_BASE + 0x8c0) /* LCD_DATA8 */
#define GPMC_A13			(CTRL_BASE + 0x8c4) /* LCD_DATA9 */
#define GPMC_A14			(CTRL_BASE + 0x8c8) /* LCD_DATA10 */
#define GPMC_A15			(CTRL_BASE + 0x8cc) /* LCD_DATA11 */
#define GPMC_A16			(CTRL_BASE + 0x8d0) /* LCD_DATA12 */
#define GPMC_A17			(CTRL_BASE + 0x8d4) /* LCD_DATA13 */
#define GPMC_A18			(CTRL_BASE + 0x8d8) /* LCD_DATA14 */
#define GPMC_A19			(CTRL_BASE + 0x8dc) /* LCD_DATA15 */
#define GPMC_A20			(CTRL_BASE + 0x850) /* GPMC_A4 */
#define GPMC_A21			(CTRL_BASE + 0x854) /* GPMC_A5 */
#define GPMC_A22			(CTRL_BASE + 0x858) /* GPMC_A6 */

/* DDR offsets */
#define	DDR_PHY_BASE_ADDR		0x44E12000
#define	DDR_IO_CTRL			0x44E10E04
#define	DDR_CKE_CTRL			0x44E1131C
#define	CONTROL_BASE_ADDR		0x44E10000

#define	DDR_CMD0_IOCTRL			(CONTROL_BASE_ADDR + 0x1404)
#define	DDR_CMD1_IOCTRL			(CONTROL_BASE_ADDR + 0x1408)
#define	DDR_CMD2_IOCTRL			(CONTROL_BASE_ADDR + 0x140C)
#define	DDR_DATA0_IOCTRL		(CONTROL_BASE_ADDR + 0x1440)
#define	DDR_DATA1_IOCTRL		(CONTROL_BASE_ADDR + 0x1444)

#define	CMD0_CTRL_SLAVE_RATIO_0		(DDR_PHY_BASE_ADDR + 0x01C)
#define	CMD0_CTRL_SLAVE_FORCE_0		(DDR_PHY_BASE_ADDR + 0x020)
#define	CMD0_CTRL_SLAVE_DELAY_0		(DDR_PHY_BASE_ADDR + 0x024)
#define	CMD0_DLL_LOCK_DIFF_0		(DDR_PHY_BASE_ADDR + 0x028)
#define	CMD0_INVERT_CLKOUT_0		(DDR_PHY_BASE_ADDR + 0x02C)

#define	CMD1_CTRL_SLAVE_RATIO_0		(DDR_PHY_BASE_ADDR + 0x050)
#define	CMD1_CTRL_SLAVE_FORCE_0		(DDR_PHY_BASE_ADDR + 0x054)
#define	CMD1_CTRL_SLAVE_DELAY_0		(DDR_PHY_BASE_ADDR + 0x058)
#define	CMD1_DLL_LOCK_DIFF_0		(DDR_PHY_BASE_ADDR + 0x05C)
#define	CMD1_INVERT_CLKOUT_0		(DDR_PHY_BASE_ADDR + 0x060)

#define	CMD2_CTRL_SLAVE_RATIO_0		(DDR_PHY_BASE_ADDR + 0x084)
#define	CMD2_CTRL_SLAVE_FORCE_0		(DDR_PHY_BASE_ADDR + 0x088)
#define	CMD2_CTRL_SLAVE_DELAY_0		(DDR_PHY_BASE_ADDR + 0x08C)
#define	CMD2_DLL_LOCK_DIFF_0		(DDR_PHY_BASE_ADDR + 0x090)
#define	CMD2_INVERT_CLKOUT_0		(DDR_PHY_BASE_ADDR + 0x094)

#define DATA0_RD_DQS_SLAVE_RATIO_0	(DDR_PHY_BASE_ADDR + 0x0C8)
#define DATA0_RD_DQS_SLAVE_RATIO_1	(DDR_PHY_BASE_ADDR + 0x0CC)
#define	DATA0_WR_DQS_SLAVE_RATIO_0	(DDR_PHY_BASE_ADDR + 0x0DC)

#define	DATA0_WR_DQS_SLAVE_RATIO_1	(DDR_PHY_BASE_ADDR + 0x0E0)
#define	DATA0_WRLVL_INIT_RATIO_0	(DDR_PHY_BASE_ADDR + 0x0F0)

#define	DATA0_WRLVL_INIT_RATIO_1	(DDR_PHY_BASE_ADDR + 0x0F4)
#define DATA0_WRLVL_INIT_MODE_0		(DDR_PHY_BASE_ADDR + 0x0F8)
#define	DATA0_GATELVL_INIT_RATIO_0	(DDR_PHY_BASE_ADDR + 0x0FC)

#define	DATA0_GATELVL_INIT_RATIO_1	(DDR_PHY_BASE_ADDR + 0x100)
#define DATA0_GATELVL_INIT_MODE_0	(DDR_PHY_BASE_ADDR + 0x104)
#define	DATA0_FIFO_WE_SLAVE_RATIO_0	(DDR_PHY_BASE_ADDR + 0x108)

#define	DATA0_FIFO_WE_SLAVE_RATIO_1	(DDR_PHY_BASE_ADDR + 0x10C)
#define	DATA0_WR_DATA_SLAVE_RATIO_0	(DDR_PHY_BASE_ADDR + 0x120)

#define	DATA0_WR_DATA_SLAVE_RATIO_1	(DDR_PHY_BASE_ADDR + 0x124)
#define DATA0_DLL_LOCK_DIFF_0		(DDR_PHY_BASE_ADDR + 0x138)

#define DATA0_RANK0_DELAYS_0		(DDR_PHY_BASE_ADDR + 0x134)
#define DATA1_WRLVL_INIT_MODE_0		(DDR_PHY_BASE_ADDR + 0x19C)
#define DATA1_GATELVL_INIT_MODE_0	(DDR_PHY_BASE_ADDR + 0x1A8)
#define	DATA1_RANK0_DELAYS_0		(DDR_PHY_BASE_ADDR + 0x1D8)
#define DATA1_RD_DQS_SLAVE_RATIO_0	(DDR_PHY_BASE_ADDR + 0x16C)
#define DATA1_WR_DQS_SLAVE_RATIO_0	(DDR_PHY_BASE_ADDR + 0x180)
#define DATA1_FIFO_WE_SLAVE_RATIO_0 	(DDR_PHY_BASE_ADDR + 0x1AC)
#define DATA1_WR_DATA_SLAVE_RATIO_0	(DDR_PHY_BASE_ADDR + 0x1C4)

#endif /* _AM33XX_CPU_H */
