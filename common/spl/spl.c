/*
 * (C) Copyright 2010
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
#include <spl.h>
#include <asm/u-boot.h>
#include <nand.h>
#include <fat.h>
#include <version.h>
#include <i2c.h>
#include <image.h>
#include <malloc.h>
#include <linux/compiler.h>

DECLARE_GLOBAL_DATA_PTR;

#ifndef CONFIG_SYS_UBOOT_START
#define CONFIG_SYS_UBOOT_START	CFG_PHY_UBOOT_BASE
#endif
#ifndef CONFIG_SYS_MONITOR_LEN
#define CONFIG_SYS_MONITOR_LEN	(200 * 1024)
#endif

struct spl_image_info spl_image;

__weak void __noreturn jump_to_image_no_args(struct spl_image_info *spl_image)
{
	typedef void __noreturn (*image_entry_noargs_t)(void);
	image_entry_noargs_t image_entry =
			(image_entry_noargs_t) spl_image->entry_point;

	uart_puts("image entry point: ");
	debug_reg(spl_image->entry_point);
	image_entry();
}

void board_init_r(gd_t *dummy1, ulong dummy2)
{
	u32 boot_device;
	int ret=-1;

	uart_puts("\r\nU-Boot SPL " PLAIN_VERSION " (" U_BOOT_DATE " - " \
			U_BOOT_TIME ")\r\n");

#ifdef CONFIG_SYS_SPL_MALLOC_START
	mem_malloc_init(CONFIG_SYS_SPL_MALLOC_START,
			CONFIG_SYS_SPL_MALLOC_SIZE);
#endif

#ifndef CONFIG_PPC
	/*
	 * timer_init() does not exist on PPC systems. The timer is initialized
	 * and enabled (decrementer) in interrupt_init() here.
	 
	timer_init();*/
#endif

#ifdef CONFIG_SPL_BOARD_INIT
	spl_board_init();
#endif

	boot_device = spl_boot_device();
	uart_puts("boot device - ");
	debug_reg(boot_device);
	switch (boot_device) {
#ifdef CONFIG_SPL_MMC_SUPPORT
	case BOOT_DEVICE_MMC0:
	case BOOT_DEVICE_MMC2:
		ret=spl_mmc_load_image();
		break;
#endif
#ifdef CONFIG_SPL_NAND_SUPPORT
	case BOOT_DEVICE_NAND:
		//ret=spl_nand_load_image();
		ret=-1;
		uart_puts("Boot Device:nand\r\n");
		break;
#endif
	default:
		uart_puts("SPL: Un-supported Boot Device\r\n");
		ret=-1;
	}

	if(ret)
	{
		uart_puts("hang()\r\n");
		while(1);
	}
	else
		uart_puts("Jumping to U-Boot\r\n");
	
	spl_image.entry_point = CONFIG_SYS_UBOOT_START;
	jump_to_image_no_args(&spl_image);
}
