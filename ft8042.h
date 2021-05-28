/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _I8042_H
#define _I8042_H

#include <linux/types.h>

/*
 * Standard commands.
 */

#define I8042_CMD_CTL_RCTR	0x0120
#define I8042_CMD_CTL_WCTR	0x1060
#define I8042_CMD_CTL_TEST	0x01aa

#define I8042_CMD_KBD_DISABLE	0x00ad
#define I8042_CMD_KBD_ENABLE	0x00ae
#define I8042_CMD_KBD_TEST	0x01ab
#define I8042_CMD_KBD_LOOP	0x11d2

#define I8042_CMD_AUX_DISABLE	0x00a7
#define I8042_CMD_AUX_ENABLE	0x00a8
#define I8042_CMD_AUX_TEST	0x01a9
#define I8042_CMD_AUX_SEND	0x10d4
#define I8042_CMD_AUX_LOOP	0x11d3

#define I8042_CMD_MUX_PFX	0x0090
#define I8042_CMD_MUX_SEND	0x1090

/*
 * Status register bits.
 */

#define I8042_STR_PARITY	0x80
#define I8042_STR_TIMEOUT	0x40
#define I8042_STR_AUXDATA	0x20
#define I8042_STR_KEYLOCK	0x10
#define I8042_STR_CMDDAT	0x08
#define I8042_STR_MUXERR	0x04
#define I8042_STR_IBF		0x02
#define I8042_STR_OBF		0x01

/*
 * Control register bits.
 */

#define I8042_CTR_KBDINT	0x01
#define I8042_CTR_AUXINT	0x02
#define I8042_CTR_IGNKEYLOCK	0x08
#define I8042_CTR_KBDDIS	0x10
#define I8042_CTR_AUXDIS	0x20
#define I8042_CTR_XLATE		0x40
/*
 *  Copyright (c) 1999-2002 Vojtech Pavlik
 */

/*
 * Arch-dependent inline functions and defines.
 */
#include "paramter.h"

/*
 * This is in 50us units, the time we wait for the i8042 to react. This
 * has to be long enough for the i8042 itself to timeout on sending a byte
 * to a non-existent mouse.
 */

#define I8042_CTL_TIMEOUT	10000

/*
 * Return codes.
 */

#define I8042_RET_CTL_TEST	0x55

/*
 * Expected maximum internal i8042 buffer size. This is used for flushing
 * the i8042 buffers.
 */

#define I8042_BUFFER_SIZE	16

/*
 * Number of AUX ports on controllers supporting active multiplexing
 * specification
 */

#define I8042_NUM_MUX_PORTS	4

/*
 * Debug.
 */
#define DEBUG
#ifdef DEBUG
static unsigned long i8042_start_time;
#define dbg_init() do { i8042_start_time = jiffies; } while (0)
#define dbg(format, arg...)							\
	do {									\
		if (i8042_debug)						\
			printk(KERN_DEBUG KBUILD_MODNAME ": [%d] " format,	\
			       (int) (jiffies - i8042_start_time), ##arg);	\
	} while (0)

#define filter_dbg(filter, data, format, args...)		\
	do {							\
		if (!i8042_debug)				\
			break;					\
								\
		if (!filter || i8042_unmask_kbd_data)		\
			dbg("%02x " format, data, ##args);	\
		else						\
			dbg("** " format, ##args);		\
	} while (0)
#else
#define dbg_init() do { } while (0)
#define dbg(format, arg...)							\
	do {									\
		if (0)								\
			printk(KERN_DEBUG pr_fmt(format), ##arg);		\
	} while (0)

#define filter_dbg(filter, data, format, args...) do { } while (0)
#endif

#endif /* _I8042_H */
