/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _I8042_PHY_H
#define _I8042_PHY_H


#include <asm/io.h>
#include <linux/acpi.h>

static int i8042_kbd_irq = -1;
static int i8042_aux_irq = -1;
#define I8042_KBD_IRQ i8042_kbd_irq
#define I8042_AUX_IRQ i8042_aux_irq

#define I8042_COMMAND_REG	(kbd_iobase + 0x64UL)
#define I8042_DATA_REG		(kbd_iobase + 0x60UL)

#define I8042_KBD_PHYS_DESC "phy8042/serio0"
#define I8042_AUX_PHYS_DESC "phy8042/serio1"
#define I8042_MUX_PHYS_DESC "phy8042/serio%d"

static void __iomem *kbd_iobase;

static inline int i8042_read_data(void)
{
	return readb(kbd_iobase + 0x60UL);
}

static inline int i8042_read_status(void)
{
	return readb(kbd_iobase + 0x64UL);
}

static inline void i8042_write_data(int val)
{
	writeb(val, kbd_iobase + 0x60UL);
}

static inline void i8042_write_command(int val)
{
	writeb(val, kbd_iobase + 0x64UL);
}

static int __init i8042_platform_init(void)
{
	/* Hardcoded values for MrCoffee.  */
	// i8042_kbd_irq = i8042_aux_irq = 19;
	u32 gsi=0x25; 
	u32 irq; 

	irq = acpi_register_gsi(NULL, gsi, ACPI_LEVEL_SENSITIVE,
					ACPI_ACTIVE_HIGH);

	i8042_kbd_irq = i8042_aux_irq = irq;
	kbd_iobase = ioremap(0x20000000, 0x8000000);

	printk(KERN_INFO "i8042_platform_init kbd_iobase : 0x%lX, irq: %d\n",
	       (long unsigned int)kbd_iobase, i8042_kbd_irq);
	i8042_reset = I8042_RESET_ALWAYS;

	return 0;
}

static inline void i8042_platform_exit(void)
{
	iounmap(kbd_iobase);
}

#endif /* _I8042_SPARCIO_H */