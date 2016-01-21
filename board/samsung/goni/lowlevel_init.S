/*
 * Memory Setup stuff - taken from blob memsetup.S
 *
 * Copyright (C) 2009 Samsung Electronics
 * Kyungmin Park <kyungmin.park@samsung.com>
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

#include <config.h>
#include <version.h>
#include <asm/arch/cpu.h>
#include <asm/arch/clock.h>
#include <asm/arch/power.h>

/*
 * Register usages:
 *
 * r5 has zero always
 * r7 has S5PC100 GPIO base, 0xE0300000
 * r8 has real GPIO base, 0xE0300000, 0xE0200000 at S5PC100, S5PC110 repectively
 * r9 has Mobile DDR size, 1 means 1GiB, 2 means 2GiB and so on
 */

_TEXT_BASE:
	.word	CONFIG_SYS_TEXT_BASE

	.globl lowlevel_init
lowlevel_init:
	mov	r11, lr

	/* check reset status  */	

	/*
	 * Initialize Async Register Setting for EVT1
	 * Because we are setting EVT1 as the default value of EVT0,
	 * setting EVT0 as well does not make things worse.
	 * Thus, for the simplicity, we set for EVT0, too
	 *
	 * The "Async Registers" are:
	 *	0xE0F0_0000
	 *	0xE1F0_0000
	 *	0xF180_0000
	 *	0xF190_0000
	 *	0xF1A0_0000
	 *	0xF1B0_0000
	 *	0xF1C0_0000
	 *	0xF1D0_0000
	 *	0xF1E0_0000
	 *	0xF1F0_0000
	 *	0xFAF0_0000
	 */
	ldr     r0, =0xe0f00000
	ldr     r1, [r0]
	bic     r1, r1, #0x1
	str     r1, [r0]

	ldr     r0, =0xe1f00000
	ldr     r1, [r0]
	bic     r1, r1, #0x1
	str     r1, [r0]

	ldr     r0, =0xf1800000
	ldr     r1, [r0]
	bic     r1, r1, #0x1
	str     r1, [r0]

	ldr     r0, =0xf1900000
	ldr     r1, [r0]
	bic     r1, r1, #0x1
	str     r1, [r0]

	ldr     r0, =0xf1a00000
	ldr     r1, [r0]
	bic     r1, r1, #0x1
	str     r1, [r0]

	ldr     r0, =0xf1b00000
	ldr     r1, [r0]
	bic     r1, r1, #0x1
	str     r1, [r0]

	ldr     r0, =0xf1c00000
	ldr     r1, [r0]
	bic     r1, r1, #0x1
	str     r1, [r0]

	ldr     r0, =0xf1d00000
	ldr     r1, [r0]
	bic     r1, r1, #0x1
	str     r1, [r0]

	ldr     r0, =0xf1e00000
	ldr     r1, [r0]
	bic     r1, r1, #0x1
	str     r1, [r0]

	ldr     r0, =0xf1f00000
	ldr     r1, [r0]
	bic     r1, r1, #0x1
	str     r1, [r0]

	ldr     r0, =0xfaf00000
	ldr     r1, [r0]
	bic     r1, r1, #0x1
	str     r1, [r0]

	/*
	 * Diable ABB block to reduce sleep current at low temperature
	 * Note that it's hidden register setup don't modify it
	 */
	ldr	r0, =0xE010C300
	ldr	r1, =0x00800000
	str	r1, [r0]

	/* IO Retention release */
	ldr	r0, =(ELFIN_CLOCK_POWER_BASE + OTHERS_OFFSET)
	ldr	r1, [r0]
	ldr	r2, =IO_RET_REL
	orr	r1, r1, r2
	str	r1, [r0]

	/* Disable Watchdog */
	ldr	r0, =ELFIN_WATCHDOG_BASE	/* 0xE2700000 */
	mov	r1, #0
	str	r1, [r0]

	/* S5PC100 has 3 groups of interrupt sources */
	ldr	r0, =S5PC110_VIC0_BASE			@0xE4000000
	ldr	r1, =S5PC110_VIC1_BASE			@0xE4000000
	ldr	r2, =S5PC110_VIC2_BASE			@0xE4000000

	/* Disable all interrupts (VIC0, VIC1 and VIC2) */
	mvn	r3, #0x0
	str	r3, [r0, #0x14]				@INTENCLEAR
	str	r3, [r1, #0x14]				@INTENCLEAR
	str	r3, [r2, #0x14]				@INTENCLEAR

	mov	r5, #0
	
	/* Set all interrupts as IRQ */
	str	r5, [r0, #0xc]				@INTSELECT
	str	r5, [r1, #0xc]				@INTSELECT
	str	r5, [r2, #0xc]				@INTSELECT

	/* Pending Interrupt Clear */
	str	r5, [r0, #0xf00]			@INTADDRESS
	str	r5, [r1, #0xf00]			@INTADDRESS
	str	r5, [r2, #0xf00]			@INTADDRESS

	/* init system clock */
	bl system_clock_init

	/* Memory initialize */
	bl mem_ctrl_asm_init

	/* for UART */
	bl	uart_asm_init

	bl tzpc_init

	/* check reset status  */	
	

	/* Print 'K' */
	ldr	r0, =ELFIN_UART_CONSOLE_BASE
	ldr	r1, =0x4b4b4b4b
	str	r1, [r0, #UTXH_OFFSET]
	
	mov	lr, r11
	mov	pc, lr

/*
 * system_clock_init: Initialize core clock and bus clock.
 * void system_clock_init(void)
 */
system_clock_init:
	ldr	r0, =ELFIN_CLOCK_POWER_BASE	@0xe0100000

	/* Set Mux to FIN */
	ldr	r1, =0x0
	str	r1, [r0, #CLK_SRC0_OFFSET]

	ldr	r1,	=APLL_LOCKTIME_VAL
	str	r1,	[r0, #APLL_LOCK_OFFSET]

	/* Disable PLL */
#if defined(CONFIG_CHECK_MPLL_LOCK)
retryloop:
#endif
	ldr	r1, =0x0
	str	r1, [r0, #APLL_CON0_OFFSET]
	ldr	r1, =0x0
	str	r1, [r0, #MPLL_CON_OFFSET]

	ldr	r1, =0x0
	str	r1, [r0, #MPLL_CON_OFFSET]

	ldr   	r1, [r0, #CLK_DIV0_OFFSET]
	ldr	r2, =CLK_DIV0_MASK
	bic	r1, r1, r2

	ldr	r2, =CLK_DIV0_VAL
	orr	r1, r1, r2
	str	r1, [r0, #CLK_DIV0_OFFSET]

	ldr	r1, =APLL_VAL
	str	r1, [r0, #APLL_CON0_OFFSET]

	ldr	r1, =MPLL_VAL
	str	r1, [r0, #MPLL_CON_OFFSET]

	ldr	r1, =VPLL_VAL
	str	r1, [r0, #VPLL_CON_OFFSET]

	ldr	r1, =AFC_ON
	str	r1, [r0, #APLL_CON1_OFFSET]

	mov	r1, #0x10000
1:	subs	r1, r1, #1
	bne	1b

#if defined(CONFIG_CHECK_MPLL_LOCK)
	/* MPLL software workaround */
	ldr	r1, [r0, #MPLL_CON_OFFSET]
	orr     r1, r1, #(1<<28)
	str	r1, [r0, #MPLL_CON_OFFSET]

	mov	r1, #0x100
1:	subs	r1, r1, #1
	bne	1b

	ldr	r1, [r0, #MPLL_CON_OFFSET]
	and	r1, r1, #(1<<29)
	cmp	r1, #(1<<29)
	bne 	retryloop

	/* H/W lock detect disable */
	ldr	r1, [r0, #MPLL_CON_OFFSET]
	bic     r1, r1, #(1<<28)
	str	r1, [r0, #MPLL_CON_OFFSET]
#endif

	ldr	r1, [r0, #CLK_SRC0_OFFSET]
	ldr	r2, =0x10001111
	orr	r1, r1, r2
	str	r1, [r0, #CLK_SRC0_OFFSET]

	/* CLK_DIV6 */
	ldr	r1, [r0, #CLK_DIV6_OFFSET]
	bic	r1, r1, #(0x7<<12)	@; ONENAND_RATIO: 0
	str	r1, [r0, #CLK_DIV6_OFFSET]

	mov	pc, lr

/*
 * uart_asm_init: Initialize UART in asm mode, 115200bps fixed.
 * void uart_asm_init(void)
 */
uart_asm_init:
	/* set GPIO to enable UART0-UART4 */
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r1, =0x22222222
	str r1, [r0, #GPA0CON_OFFSET]
	ldr r1, =0x00002222
	str r1, [r0, #GPA1CON_OFFSET]

	ldr	r0, =ELFIN_UART_CONSOLE_BASE		@0xE2900000
	mov	r1, #0x0
	str	r1, [r0, #UFCON_OFFSET]
	str	r1, [r0, #UMCON_OFFSET]

	mov	r1, #0x3
	str	r1, [r0, #ULCON_OFFSET]

	ldr	r1, =0x3c5
	str	r1, [r0, #UCON_OFFSET]

	ldr	r1, =UART_UBRDIV_VAL
	str	r1, [r0, #UBRDIV_OFFSET]

	ldr	r1, =UART_UDIVSLOT_VAL
	str	r1, [r0, #UDIVSLOT_OFFSET]

	ldr	r1, =0x4f4f4f4f
	str	r1, [r0, #UTXH_OFFSET]		@'O'

	mov	pc, lr

/*
 * Setting TZPC[TrustZone Protection Controller]
 */
tzpc_init:

	ldr	r0, =ELFIN_TZPC0_BASE
 	mov	r1, #0x0
 	str	r1, [r0]
 	mov	r1, #0xff
 	str	r1, [r0, #TZPC_DECPROT0SET_OFFSET]
 	str	r1, [r0, #TZPC_DECPROT1SET_OFFSET]
	str	r1, [r0, #TZPC_DECPROT2SET_OFFSET] 	

 	ldr 	r0, =ELFIN_TZPC1_BASE
 	str	r1, [r0, #TZPC_DECPROT0SET_OFFSET]
 	str	r1, [r0, #TZPC_DECPROT1SET_OFFSET]
	str	r1, [r0, #TZPC_DECPROT2SET_OFFSET] 	

 	ldr	r0, =ELFIN_TZPC2_BASE
 	str	r1, [r0, #TZPC_DECPROT0SET_OFFSET]
 	str	r1, [r0, #TZPC_DECPROT1SET_OFFSET]
	str	r1, [r0, #TZPC_DECPROT2SET_OFFSET]
	str	r1, [r0, #TZPC_DECPROT3SET_OFFSET] 

 	ldr	r0, =ELFIN_TZPC3_BASE
 	str	r1, [r0, #TZPC_DECPROT0SET_OFFSET]
 	str	r1, [r0, #TZPC_DECPROT1SET_OFFSET]
	str	r1, [r0, #TZPC_DECPROT2SET_OFFSET] 	

 	mov	pc, lr
