#include <common.h>
#include <asm/arch/spl.h>
#include <linux/types.h>

DECLARE_GLOBAL_DATA_PTR;

#define UTRSTAT0    (*(volatile unsigned int *)0xE2900010)
#define UTXH0       (*(volatile unsigned char *)0xE2900020)

void uart_putc (char c)
{
	//如果发送缓冲区还有有效数据，则循环
	//判断是否全部发送完成
	while ( (UTRSTAT0&(1<<2))==0 );
	//发送一个字符
	UTXH0 = c;
}

void uart_puts (char *s)
{
	while (*s != '\0') {
		uart_putc(*s++);
	}
}

void debug_reg(u32 value)
{
	u32 m;
	u32 i;

	uart_puts("0x");
	for(i=0; i<8; i++)
	{
		m = (value>>((7-i)*4)) & 0x0000000f;

		if(m>9)
			m = m - 0xa + 'A'; 
		else
			m = m + '0';

		uart_putc(m);
	}	
	uart_puts("\r\n");
}

#define PRO_ID_BASE					0xE0000000
#define OMR_OFFSET					0x04

u32 spl_boot_device(void)
{
	ulong reg;
	ulong src=BOOT_DEVICE_UNKNOWN;

	reg = (*(volatile u32 *)(PRO_ID_BASE + OMR_OFFSET));
	uart_puts("OMR_VALUE=");
	debug_reg(reg);
	
	reg &= 0x0000003f;	
	if (reg == 0x0000000C)
		/* boot device is SDMMC */
		src = BOOT_DEVICE_MMC0;
	else if (reg == 0x00000002)
		/* boot device is NOR */
		src = BOOT_DEVICE_NAND;

	return src;
}
