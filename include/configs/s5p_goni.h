/*
 * Copyright (C) 2009 Samsung Electronics
 * Minkyu Kang <mk7.kang@samsung.com>
 * Kyungmin Park <kyungmin.park@samsung.com>
 *
 * Configuation settings for the SAMSUNG Universal (s5pc100) board.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/* High Level Configuration Options */
#define CONFIG_SAMSUNG		1	/* in a SAMSUNG core */
#define CONFIG_S5P		1	/* which is in a S5P Family */
#define CONFIG_S5PC110		1	/* which is in a S5PC110 */
#define CONFIG_MACH_GONI	1	/* working with Goni */

#include <asm/arch/cpu.h>		/* get chip and board defs */

/*#define DEBUG*/
#define CONFIG_ARCH_CPU_INIT
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

/* input clock of PLL: has 24MHz input clock at S5PC110 */
#define CONFIG_SYS_CLK_FREQ_C110	24000000

/* DRAM Base */
#define CONFIG_SYS_SDRAM_BASE		0x20000000

/* base address for uboot */
#define CFG_UBOOT_BASE_OFFSET		0x3E00000

#define CFG_PHY_UBOOT_BASE			(CONFIG_SYS_SDRAM_BASE + CFG_UBOOT_BASE_OFFSET)
/* Text Base */
#define CONFIG_SYS_TEXT_BASE		0x23E00000

#define CONFIG_SETUP_MEMORY_TAGS	/* 向内核传递内存分布信息 */
#define CONFIG_CMDLINE_TAG			/* 向内核传递命令行参数 */
#define CONFIG_INITRD_TAG

#define CONFIG_CMDLINE_EDITING		/* 命令行编辑和历史命令相关 */
#define CONFIG_AUTO_COMPLETE		/*命令补全*/

/*
 * Size of malloc() pool
 * 1MB = 0x100000, 0x100000 = 1024 * 1024
 */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + (1 << 20))
/*
 * select serial console configuration
 */
#define CONFIG_SERIAL0			1	/* use SERIAL0 */
#define CONFIG_BAUDRATE			115200
#define CONFIG_DEFAULT_CONSOLE	"console=ttySAC0,115200n8\0"

/* PWM 系统计时*/
#define CONFIG_PWM			1
#define CONFIG_SYS_HZ			1000

/* It should define before config_cmd_default.h */
#define CONFIG_SYS_NO_FLASH		1

/* Command definition */
#include <config_cmd_default.h>

#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_MISC
#undef CONFIG_CMD_NFS
#undef CONFIG_CMD_XIMG
#define CONFIG_CMD_CACHE
#define CONFIG_CMD_REGINFO

#define CONFIG_BOOTDELAY		3
#define CONFIG_ZERO_BOOTDELAY_CHECK

/*系统在上电自动执行时所执行的命令对应环境变量中bootcmd的值*/
/*#define CONFIG_BOOTCOMMAND	"tftp 20008000 uImage; bootm 20008000"*/
#define CONFIG_BOOTCOMMAND	"fatload mmc 0:1 20008000 uImage; bootm 20008000"
/*u-boot向Linux内核传递的参数,实际上这个宏值就是环境变量中的bootargs的值*/
/*#define CONFIG_BOOTARGS	"noinitrd console=ttySAC0 root=/dev/nfs rw " \
"nfsroot=192.168.2.200:/home/work/nfs/rootfs,v3,nolock,tcp ip=192.168.2.100 init=/linuxrc"*/
#define CONFIG_BOOTARGS	"noinitrd console=ttySAC0 root=/dev/mmcblk0p2 rw " \
"rootfstype=ext4 rootwait init=/linuxrc"

/* allow to overwrite serial and ethaddr */
/* 写保护设置被关闭，任何人可以重设板子参数*/
#define CONFIG_ENV_OVERWRITE
/*It's important to serial console !
Define this if you want stdin, stdout &/or stderr to be set to usbtty*/
#define CONFIG_SYS_CONSOLE_IS_IN_ENV
#if 0
#define CONFIG_EXTRA_ENV_SETTINGS					\
	"mmcblk=/dev/mmcblk0p2\0" \
	"rootfstype=ext4\0" \
	"bootk=" \
		"fatload mmc 0:1 20008000 uImage;" \
		"bootm 20008000\0" \
	"mmcboot=" \
		"set bootargs noinitrd root=${mmcblk} rw rootfstype=${rootfstype} rootwait init=/linuxrc console=ttySAC0;" \
		"run bootk"
#else
#define CONFIG_EXTRA_ENV_SETTINGS					\
	"bootk=" \
		"tftp 20008000 uImage;" \
		"bootm 20008000\0" \
	"nfsboot=" \
		"set bootargs noinitrd console=ttySAC0 root=/dev/nfs rw nfsroot=192.168.2.200:/mnt/qiang/work/nfs/rootfs,v3,nolock,tcp ip=192.168.2.100 init=/linuxrc;" \
		"run bootk"
#endif

#define CONFIG_IDENT_STRING		" for Goni"

/* Miscellaneous configurable options */
#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_SYS_HUSH_PARSER		/* use "hush" command parser	*/
#define CONFIG_SYS_PROMPT	"Goni # "
#define CONFIG_SYS_CBSIZE	256	/* Console I/O Buffer Size */
#define CONFIG_SYS_PBSIZE	384	/* Print Buffer Size */
#define CONFIG_SYS_MAXARGS	16	/* max number of command args */
/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
/* memtest works on */
#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_SDRAM_BASE + 0x3E00000	)	/* 62 MB in DRAM	*/

#define CONFIG_SYS_LOAD_ADDR		CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_LOAD_ADDR + CFG_UBOOT_BASE_OFFSET)

/* Goni has 2 banks of DRAM, but swap the bank */
#define CONFIG_NR_DRAM_BANKS	2
#define SDRAM_BANK_SIZE			0x20000000	/* 512 MB */
#define PHYS_SDRAM_1				CONFIG_SYS_SDRAM_BASE	/* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE		SDRAM_BANK_SIZE
#define PHYS_SDRAM_2				(CONFIG_SYS_SDRAM_BASE + SDRAM_BANK_SIZE) /* SDRAM Bank #2 */
#define PHYS_SDRAM_2_SIZE		SDRAM_BANK_SIZE

#define CONFIG_SYS_MONITOR_BASE		0x00000000
#define CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 256 kB for Monitor    预分配u-boot程序空间*/

/* FLASH and environment organization */
#define CONFIG_ENV_IS_IN_MMC		1
#define CONFIG_SYS_MMC_ENV_DEV		0
#define CONFIG_ENV_SIZE				(8 << 10)	/* 8 KB */
#define RESERVE_BLOCK_SIZE			(512)  
#define BL1_SIZE						(16 << 10) /*16 K reserved for BL1*/  
#define CONFIG_ENV_OFFSET			(RESERVE_BLOCK_SIZE + BL1_SIZE)

#define CONFIG_SYS_CACHELINE_SIZE       64


#undef CONFIG_USE_IRQ

#define CONFIG_TQ210_IIC_PM_CHIP

#ifndef CONFIG_SPL_BUILD 
/* SD/MMC configuration */
#define CONFIG_GENERIC_MMC
#define CONFIG_MMC
#define CONFIG_SDHCI
#define CONFIG_S5P_SDHCI
#define CONFIG_CMD_MMC

/*fat read/write*/
#define CONFIG_CMD_FAT
#define CONFIG_FS_FAT
#define CONFIG_FAT_WRITE
#define CONFIG_DOS_PARTITION
#define CONFIG_SUPPORT_VFAT

#define CONFIG_CMD_EXT4
#define CONFIG_CMD_EXT4_WRITE

/*
 * Ethernet Contoller driver
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_DRIVER_DM9000		1
#define CONFIG_DM9000_BASE		0x88000000
#define DM9000_IO			CONFIG_DM9000_BASE
#define DM9000_DATA			(CONFIG_DM9000_BASE + 0x4)
/*#define CONFIG_DM9000_DEBUG*/

#define CONFIG_CMD_PING

#define CONFIG_ETHADDR      00:40:5c:26:0a:5b 
#define CONFIG_NETMASK      255.255.255.0  
#define CONFIG_IPADDR       192.168.2.100  
#define CONFIG_SERVERIP     192.168.2.200  
#define CONFIG_GATEWAYIP    192.168.2.1  
#endif /* CONFIG_CMD_NET */

#endif


/*
 * SPL Settings
 */
#define CONFIG_SPL
#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_BOOT
#define CONFIG_SPL_MMC_SUPPORT

#define CONFIG_SPL_TEXT_BASE 			0xD0020010
#define CONFIG_SPL_STACK					0xD0037D80

#ifndef CONFIG_SPL_BUILD 
#define CONFIG_SKIP_LOWLEVEL_INIT 
#endif

#define DMC0_MEMCONFIG_0		0x20E01323	/*MemConfig0	256MB config, 8 banks,Mapping Method[12:15]0:linear, 1:linterleaved, 2:Mixed*/
#define DMC0_MEMCONFIG_1		0x40F01323	/*MemConfig1*/
#define DMC0_TIMINGA_REF		0x00000618	/*TimingAref	7.8us*133MHz=1038(0x40E), 100MHz=780(0x30C), 20MHz=156(0x9C), 10MHz=78(0x4E)*/
#define DMC0_TIMING_ROW		0x28233287	/*TimingRow	for @200MHz*/
#define DMC0_TIMING_DATA		0x23240304	/*TimingData	CL=3*/
#define DMC0_TIMING_PWR		0x09C80232	/*TimingPower*/

#define DMC1_MEMCONTROL		0x00202400	/*MemControl	BL=4, 2 chip, DDR2 type, dynamic self refresh, force precharge, dynamic power down off*/
#define DMC1_MEMCONFIG_0		0x40C01323	/*MemConfig0	512MB config, 8 banks,Mapping Method[12:15]0:linear, 1:linterleaved, 2:Mixed*/
#define DMC1_MEMCONFIG_1		0x00E01323	/*MemConfig1*/
#define DMC1_TIMINGA_REF		0x00000618	/*TimingAref	7.8us*133MHz=1038(0x40E), 100MHz=780(0x30C), 20MHz=156(0x9C), 10MHz=78(0x4*/
#define DMC1_TIMING_ROW		0x28233289	/*TimingRow	for @200MHz*/
#define DMC1_TIMING_DATA		0x23240304	/*TimingData	CL=3*/
#define DMC1_TIMING_PWR		0x08280232	/*TimingPower*/

#define UART_UBRDIV_VAL						34
#define UART_UDIVSLOT_VAL					0xDDDD

#define APLL_LOCKTIME_VAL					0x2cf
/* Set AFC value */
#define AFC_ON								0x00000000
#define AFC_OFF								0x10000010

#define APLL_MDIV							0x7d
#define APLL_PDIV							0x3
#define APLL_SDIV							0x1

#define MPLL_MDIV							0x29b
#define MPLL_PDIV							0xc
#define MPLL_SDIV							0x1

#define EPLL_MDIV							0x60
#define EPLL_PDIV							0x6
#define EPLL_SDIV							0x2

#define VPLL_MDIV							0x6c
#define VPLL_PDIV							0x6
#define VPLL_SDIV							0x3

#define set_pll(mdiv, pdiv, sdiv)	(1<<31 | mdiv<<16 | pdiv<<8 | sdiv)

#define APLL_VAL							set_pll(APLL_MDIV,APLL_PDIV,APLL_SDIV)
#define MPLL_VAL							set_pll(MPLL_MDIV,MPLL_PDIV,MPLL_SDIV)
#define EPLL_VAL							set_pll(EPLL_MDIV,EPLL_PDIV,EPLL_SDIV)
#define VPLL_VAL							set_pll(VPLL_MDIV,VPLL_PDIV,VPLL_SDIV)

/* CLK_DIV0 */
#define APLL_RATIO							0
#define A2M_RATIO							4
#define HCLK_MSYS_RATIO						8
#define PCLK_MSYS_RATIO						12
#define HCLK_DSYS_RATIO						16
#define PCLK_DSYS_RATIO						20
#define HCLK_PSYS_RATIO						24
#define PCLK_PSYS_RATIO						28

#define CLK_DIV0_MASK						0x7fffffff

#define CLK_DIV0_VAL						((0<<APLL_RATIO)|(4<<A2M_RATIO)|(4<<HCLK_MSYS_RATIO)|(1<<PCLK_MSYS_RATIO)\
												|(3<<HCLK_DSYS_RATIO)|(1<<PCLK_DSYS_RATIO)|(4<<HCLK_PSYS_RATIO)|(1<<PCLK_PSYS_RATIO))

#endif	/* __CONFIG_H */
