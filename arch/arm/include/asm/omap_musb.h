/*
 * Board data structure for musb gadget on OMAPs
 *
 * Copyright (C) 2012, Ilya Yanok <ilya.yanok@gmail.com>
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

#ifndef __ASM_ARM_OMAP_MUSB_H
#define __ASM_ARM_OMAP_MUSB_H

extern struct musb_platform_ops musb_dsps_ops;

struct omap_musb_board_data {
	void (*set_phy_power)(u8 on);
};
#endif /* __ASM_ARM_OMAP_MUSB_H */
