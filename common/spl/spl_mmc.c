/*
 * (C) Copyright 2010
 * Texas Instruments, <www.ti.com>
 *
 * Aneesh V <aneesh@ti.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <spl.h>
#include <asm/u-boot.h>
#include <mmc.h>
#include <version.h>
#include <image.h>

DECLARE_GLOBAL_DATA_PTR;

typedef u32(*copy_sd_mmc_to_mem)
(u32 channel, u32 start_block, u16 block_size, u32 *trg, u32 init);

int spl_mmc_load_image(void)
{
	ulong ch;

	ch = *(volatile u32 *)(0xD0037488);
	copy_sd_mmc_to_mem copy_bl2 =
	    (copy_sd_mmc_to_mem) (*(u32 *) (0xD0037F98));

	//print ch
	uart_puts("ch=");
	debug_reg(ch);

	u32 ret;
	if (ch == 0xEB000000) {
		ret = copy_bl2(0, 49, 1024, CFG_PHY_UBOOT_BASE, 0);
	}
	else if (ch == 0xEB200000) {
		ret = copy_bl2(2, 49, 1024, CFG_PHY_UBOOT_BASE, 0);
	}
	else{
		//
		uart_puts("ch error\r\n");
		return -1;
	}

	if (ret == 0){
		//
		uart_puts("copy error\r\n");
		return -1;
	}
	else
		return 0;
}
