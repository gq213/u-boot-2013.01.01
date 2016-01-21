/*
 * (C) Copyright 2009 Samsung Electronics
 * Minkyu Kang <mk7.kang@samsung.com>
 * Heungjun Kim <riverful.kim@samsung.com>
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
 *
 */

#ifndef _S5PC1XX_CPU_H
#define _S5PC1XX_CPU_H

#define S5P_CPU_NAME		"S5P"
#define S5PC1XX_ADDR_BASE	0xE0000000

/* S5PC100 */
#define S5PC100_PRO_ID		0xE0000000
#define S5PC100_CLOCK_BASE	0xE0100000
#define S5PC100_GPIO_BASE	0xE0300000
#define S5PC100_VIC0_BASE	0xE4000000
#define S5PC100_VIC1_BASE	0xE4100000
#define S5PC100_VIC2_BASE	0xE4200000
#define S5PC100_DMC_BASE	0xE6000000
#define S5PC100_SROMC_BASE	0xE7000000
#define S5PC100_ONENAND_BASE	0xE7100000
#define S5PC100_PWMTIMER_BASE	0xEA000000
#define S5PC100_WATCHDOG_BASE	0xEA200000
#define S5PC100_UART_BASE	0xEC000000
#define S5PC100_MMC_BASE	0xED800000

/* S5PC110 */
#define S5PC110_PRO_ID		0xE0000000
#define S5PC110_CLOCK_BASE	0xE0100000
#define S5PC110_GPIO_BASE	0xE0200000
#define S5PC110_PWMTIMER_BASE	0xE2500000
#define S5PC110_WATCHDOG_BASE	0xE2700000
#define S5PC110_UART_BASE	0xE2900000
#define S5PC110_SROMC_BASE	0xE8000000
#define S5PC110_MMC_BASE	0xEB000000
#define S5PC110_DMC0_BASE	0xF0000000
#define S5PC110_DMC1_BASE	0xF1400000
#define S5PC110_VIC0_BASE	0xF2000000
#define S5PC110_VIC1_BASE	0xF2100000
#define S5PC110_VIC2_BASE	0xF2200000
#define S5PC110_VIC3_BASE	0xF2300000
#define S5PC110_OTG_BASE	0xEC000000
#define S5PC110_PHY_BASE	0xEC100000
#define S5PC110_USB_PHY_CONTROL 0xE010E80C


#define BIT0						0x00000001
#define BIT1						0x00000002
#define BIT2						0x00000004
#define BIT3						0x00000008
#define BIT4						0x00000010
#define BIT5						0x00000020
#define BIT6						0x00000040
#define BIT7						0x00000080
#define BIT8						0x00000100
#define BIT9						0x00000200
#define BIT10						0x00000400
#define BIT11						0x00000800
#define BIT12						0x00001000
#define BIT13						0x00002000
#define BIT14						0x00004000
#define BIT15						0x00008000
#define BIT16						0x00010000
#define BIT17						0x00020000
#define BIT18						0x00040000
#define BIT19						0x00080000
#define BIT20						0x00100000
#define BIT21						0x00200000
#define BIT22						0x00400000
#define BIT23						0x00800000
#define BIT24						0x01000000
#define BIT25						0x02000000
#define BIT26						0x04000000
#define BIT27						0x08000000
#define BIT28						0x10000000
#define BIT29						0x20000000
#define BIT30						0x40000000
#define BIT31						0x80000000

#ifndef __ASSEMBLY__
#define UData(Data)	((unsigned long) (Data))

#define __REG(x)	(*(vu_long *)(x))
#define __REGl(x)	(*(vu_long *)(x))
#define __REGw(x)	(*(vu_short *)(x))
#define __REGb(x)	(*(vu_char *)(x))
#define __REG2(x,y)	(*(vu_long *)((x) + (y)))
#else
#define UData(Data)	(Data)

#define __REG(x)	(x)
#define __REGl(x)	(x)
#define __REGw(x)	(x)
#define __REGb(x)	(x)
#define __REG2(x,y)	((x) + (y))
#endif

/*
 * UART
 */
#define ELFIN_UART_BASE				0XE2900000

#define ELFIN_UART0_OFFSET			0x0000
#define ELFIN_UART1_OFFSET			0x0400
#define ELFIN_UART2_OFFSET			0x0800
#define ELFIN_UART3_OFFSET			0x0c00

#if defined(CONFIG_SERIAL0)
#define ELFIN_UART_CONSOLE_BASE		(ELFIN_UART_BASE + ELFIN_UART0_OFFSET)
#elif defined(CONFIG_SERIAL1)
#define ELFIN_UART_CONSOLE_BASE		(ELFIN_UART_BASE + ELFIN_UART1_OFFSET)
#elif defined(CONFIG_SERIAL2)
#define ELFIN_UART_CONSOLE_BASE		(ELFIN_UART_BASE + ELFIN_UART2_OFFSET)
#elif defined(CONFIG_SERIAL3)
#define ELFIN_UART_CONSOLE_BASE		(ELFIN_UART_BASE + ELFIN_UART3_OFFSET)
#else
#define ELFIN_UART_CONSOLE_BASE		(ELFIN_UART_BASE + ELFIN_UART0_OFFSET)
#endif

#define ULCON_OFFSET				0x00
#define UCON_OFFSET					0x04
#define UFCON_OFFSET				0x08
#define UMCON_OFFSET				0x0C
#define UTRSTAT_OFFSET				0x10
#define UERSTAT_OFFSET				0x14
#define UFSTAT_OFFSET				0x18
#define UMSTAT_OFFSET				0x1C
#define UTXH_OFFSET					0x20
#define URXH_OFFSET					0x24
#define UBRDIV_OFFSET				0x28
#define UDIVSLOT_OFFSET				0x2C
#define UINTP_OFFSET				0x30
#define UINTSP_OFFSET				0x34
#define UINTM_OFFSET				0x38

#define UTRSTAT_TX_EMPTY			BIT2
#define UTRSTAT_RX_READY			BIT0
#define UART_ERR_MASK				0xF

/*
 * GPIO
 */
#define ELFIN_GPIO_BASE			0xE0200000

#define GPA0CON_OFFSET				0x000 
#define GPA0DAT_OFFSET				0x004 
#define GPA0PUD_OFFSET				0x008 
#define GPA0DRV_SR_OFFSET			0x00C 
#define GPA0CONPDN_OFFSET			0x010 
#define GPA0PUDPDN_OFFSET			0x014

#define GPA1CON_OFFSET				0x020
#define GPA1DAT_OFFSET				0x024 
#define GPA1PUD_OFFSET				0x028 
#define GPA1DRV_SR_OFFSET			0x02C 
#define GPA1CONPDN_OFFSET			0x030 
#define GPA1PUDPDN_OFFSET			0x034 

#define GPJ1CON_OFFSET 			0x260 
#define GPJ1DAT_OFFSET 			0x264 
#define GPJ1PUD_OFFSET 			0x268 
#define GPJ1DRV_SR_OFFSET 		0x26C 
#define GPJ1CONPDN_OFFSET 		0x270 
#define GPJ1PUDPDN_OFFSET 		0x274 

#define GPJ2CON_OFFSET				0x280 
#define GPJ2DAT_OFFSET				0x284 
#define GPJ2PUD_OFFSET				0x288 
#define GPJ2DRV_SR_OFFSET			0x28C 
#define GPJ2CONPDN_OFFSET			0x290 
#define GPJ2PUDPDN_OFFSET			0x294

#define GPJ4CON_OFFSET 			0x2C0 
#define GPJ4DAT_OFFSET 			0x2C4 
#define GPJ4PUD_OFFSET 			0x2C8 
#define GPJ4DRV_SR_OFFSET 		0x2CC 
#define GPJ4CONPDN_OFFSET 		0x2D0 
#define GPJ4PUDPDN_OFFSET 		0x2D4 

#define MP1_0DRV_SR_OFFSET 		0x3CC
#define MP1_1DRV_SR_OFFSET 		0x3EC
#define MP1_2DRV_SR_OFFSET 		0x40C
#define MP1_3DRV_SR_OFFSET 		0x42C
#define MP1_4DRV_SR_OFFSET 		0x44C
#define MP1_5DRV_SR_OFFSET 		0x46C
#define MP1_6DRV_SR_OFFSET 		0x48C
#define MP1_7DRV_SR_OFFSET 		0x4AC
#define MP1_8DRV_SR_OFFSET 		0x4CC

#define MP2_0DRV_SR_OFFSET 		0x4EC
#define MP2_1DRV_SR_OFFSET 		0x50C
#define MP2_2DRV_SR_OFFSET 		0x52C
#define MP2_3DRV_SR_OFFSET 		0x54C
#define MP2_4DRV_SR_OFFSET 		0x56C
#define MP2_5DRV_SR_OFFSET 		0x58C
#define MP2_6DRV_SR_OFFSET 		0x5AC
#define MP2_7DRV_SR_OFFSET 		0x5CC
#define MP2_8DRV_SR_OFFSET 		0x5EC

#define MP01CON_OFFSET 			0x2E0 
#define MP01DAT_OFFSET 			0x2E4 
#define MP01PUD_OFFSET 			0x2E8 
#define MP01DRV_SR_OFFSET 		0x2EC 
#define MP01CONPDN_OFFSET 		0x2E0 
#define MP01PUDPDN_OFFSET 		0x2E4 

#define MP01CON_REG			__REG(ELFIN_GPIO_BASE + MP01CON_OFFSET)
#define MP01DAT_REG			__REG(ELFIN_GPIO_BASE + MP01DAT_OFFSET)		 
#define MP01PUD_REG			__REG(ELFIN_GPIO_BASE + MP01PUD_OFFSET)		 
#define MP01DRV_REG			__REG(ELFIN_GPIO_BASE + MP01DRV_SR_OFFSET)
#define MP01CONPDN_REG			__REG(ELFIN_GPIO_BASE + MP01CONPDN_OFFSET)	 
#define MP01PUDPDN_REG			__REG(ELFIN_GPIO_BASE + MP01PUDPDN_OFFSET)

/*
 * SDRAM Controller
 */
#define APB_DMC_0_BASE			0xF0000000
#define APB_DMC_1_BASE			0xF1400000
#define ASYNC_MSYS_DMC0_BASE		0xF1E00000

#define DMC_CONCONTROL 			0x00
#define DMC_MEMCONTROL 			0x04
#define DMC_MEMCONFIG0 			0x08
#define DMC_MEMCONFIG1 			0x0C
#define DMC_DIRECTCMD 			0x10
#define DMC_PRECHCONFIG 		0x14
#define DMC_PHYCONTROL0 		0x18
#define DMC_PHYCONTROL1 		0x1C
#define DMC_RESERVED 			0x20
#define DMC_PWRDNCONFIG 		0x28
#define DMC_TIMINGAREF 			0x30
#define DMC_TIMINGROW 			0x34
#define DMC_TIMINGDATA 			0x38
#define DMC_TIMINGPOWER 		0x3C
#define DMC_PHYSTATUS 			0x40
#define DMC_CHIP0STATUS 		0x48
#define DMC_CHIP1STATUS 		0x4C
#define DMC_AREFSTATUS 			0x50
#define DMC_MRSTATUS 			0x54
#define DMC_PHYTEST0 			0x58
#define DMC_PHYTEST1 			0x5C
#define DMC_QOSCONTROL0 		0x60
#define DMC_QOSCONFIG0 			0x64
#define DMC_QOSCONTROL1 		0x68
#define DMC_QOSCONFIG1 			0x6C
#define DMC_QOSCONTROL2 		0x70
#define DMC_QOSCONFIG2 			0x74
#define DMC_QOSCONTROL3 		0x78
#define DMC_QOSCONFIG3 			0x7C
#define DMC_QOSCONTROL4 		0x80
#define DMC_QOSCONFIG4 			0x84
#define DMC_QOSCONTROL5 		0x88
#define DMC_QOSCONFIG5 			0x8C
#define DMC_QOSCONTROL6 		0x90
#define DMC_QOSCONFIG6 			0x94
#define DMC_QOSCONTROL7 		0x98
#define DMC_QOSCONFIG7 			0x9C
#define DMC_QOSCONTROL8 		0xA0
#define DMC_QOSCONFIG8 			0xA4
#define DMC_QOSCONTROL9 		0xA8
#define DMC_QOSCONFIG9 			0xAC
#define DMC_QOSCONTROL10 		0xB0
#define DMC_QOSCONFIG10 		0xB4
#define DMC_QOSCONTROL11 		0xB8
#define DMC_QOSCONFIG11 		0xBC
#define DMC_QOSCONTROL12 		0xC0
#define DMC_QOSCONFIG12 		0xC4
#define DMC_QOSCONTROL13 		0xC8
#define DMC_QOSCONFIG13 		0xCC
#define DMC_QOSCONTROL14 		0xD0
#define DMC_QOSCONFIG14 		0xD4
#define DMC_QOSCONTROL15 		0xD8
#define DMC_QOSCONFIG15 		0xDC

#define ELFIN_CLOCK_POWER_BASE		0xE0100000
#define OTHERS_OFFSET				0xe000
#define IO_RET_REL					((1 << 31) | (1 << 29) | (1 << 28))
#define PS_HOLD_CONTROL_OFFSET		0xe81c

/*
 * Watchdog timer
 */
#define ELFIN_WATCHDOG_BASE			0xE2700000

/* Clock & Power Controller for s5pc110*/
#define APLL_LOCK_OFFSET			0x00
#define MPLL_LOCK_OFFSET			0x08
#define EPLL_LOCK_OFFSET			0x10
#define VPLL_LOCK_OFFSET			0x20
#define APLL_CON0_OFFSET			0x100
#define APLL_CON1_OFFSET			0x104
#define MPLL_CON_OFFSET				0x108
#define EPLL_CON_OFFSET				0x110
#define VPLL_CON_OFFSET				0x120

#define CLK_SRC0_OFFSET				0x200
#define CLK_SRC1_OFFSET				0x204
#define CLK_SRC2_OFFSET				0x208
#define CLK_SRC3_OFFSET				0x20c
#define CLK_SRC4_OFFSET				0x210
#define CLK_SRC5_OFFSET				0x214
#define CLK_SRC6_OFFSET				0x218
#define CLK_SRC_MASK0_OFFSET		0x280
#define CLK_SRC_MASK1_OFFSET		0x284

#define CLK_DIV0_OFFSET				0x300
#define CLK_DIV1_OFFSET				0x304
#define CLK_DIV2_OFFSET				0x308
#define CLK_DIV3_OFFSET				0x30c
#define CLK_DIV4_OFFSET				0x310
#define CLK_DIV5_OFFSET				0x314
#define CLK_DIV6_OFFSET				0x318
#define CLK_DIV7_OFFSET				0x31c

#define ELFIN_TZPC0_BASE			0xF1500000
#define ELFIN_TZPC1_BASE			0xFAD00000
#define ELFIN_TZPC2_BASE			0xE0600000
#define ELFIN_TZPC3_BASE			0xE1C00000

/* Access Controller (TZPC) */
#define TZPC_DECPROT0SET_OFFSET		0x804
#define TZPC_DECPROT1SET_OFFSET		0x810
#define TZPC_DECPROT2SET_OFFSET		0x81C
#define TZPC_DECPROT3SET_OFFSET		0x828

/*
 * Memory controller
 */
#define ELFIN_SROM_BASE			0xE8000000

#define SROM_BW_REG			__REG(ELFIN_SROM_BASE+0x0)
#define SROM_BC0_REG			__REG(ELFIN_SROM_BASE+0x4)
#define SROM_BC1_REG			__REG(ELFIN_SROM_BASE+0x8)
#define SROM_BC2_REG			__REG(ELFIN_SROM_BASE+0xC)
#define SROM_BC3_REG			__REG(ELFIN_SROM_BASE+0x10)
#define SROM_BC4_REG			__REG(ELFIN_SROM_BASE+0x14)
#define SROM_BC5_REG			__REG(ELFIN_SROM_BASE+0x18)


#ifndef __ASSEMBLY__
#include <asm/io.h>
/* CPU detection macros */
extern unsigned int s5p_cpu_id;

static inline void s5p_set_cpu_id(void)
{
	s5p_cpu_id = readl(S5PC100_PRO_ID);
	s5p_cpu_id = 0xC000 | ((s5p_cpu_id & 0x00FFF000) >> 12);
}

static inline char *s5p_get_cpu_name(void)
{
	return S5P_CPU_NAME;
}

#define IS_SAMSUNG_TYPE(type, id)			\
static inline int cpu_is_##type(void)			\
{							\
	return s5p_cpu_id == id ? 1 : 0;		\
}

IS_SAMSUNG_TYPE(s5pc100, 0xc100)
IS_SAMSUNG_TYPE(s5pc110, 0xc110)

#define SAMSUNG_BASE(device, base)				\
static inline unsigned int samsung_get_base_##device(void)	\
{								\
	if (cpu_is_s5pc100())					\
		return S5PC100_##base;				\
	else if (cpu_is_s5pc110())				\
		return S5PC110_##base;				\
	else							\
		return 0;					\
}

SAMSUNG_BASE(clock, CLOCK_BASE)
SAMSUNG_BASE(gpio, GPIO_BASE)
SAMSUNG_BASE(pro_id, PRO_ID)
SAMSUNG_BASE(mmc, MMC_BASE)
SAMSUNG_BASE(sromc, SROMC_BASE)
SAMSUNG_BASE(timer, PWMTIMER_BASE)
SAMSUNG_BASE(uart, UART_BASE)
SAMSUNG_BASE(watchdog, WATCHDOG_BASE)
#endif

#endif	/* _S5PC1XX_CPU_H */
