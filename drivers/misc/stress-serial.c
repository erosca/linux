// SPDX-License-Identifier: GPL-2.0
/*
 * Serial console load generator
 *
 * Copyright (C) 2020 Advanced Driver Information Technology.
 */

#include <linux/hrtimer.h>
#include <linux/init.h>
#include <linux/ktime.h>
#include <linux/module.h>

#define PERIOD_MS 1

static struct hrtimer hr_timer;

static enum hrtimer_restart hr_timer_cb(struct hrtimer *timer)
{
	pr_crit("123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789\n");
	hrtimer_forward_now(timer, ms_to_ktime(PERIOD_MS));

	return HRTIMER_RESTART;
}

static int stress_serial_init(void)
{
	ktime_t ktime = ktime_set(0, PERIOD_MS * 1000 * 1000);

	hrtimer_init(&hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hr_timer.function = &hr_timer_cb;
	hrtimer_start(&hr_timer, ktime, HRTIMER_MODE_REL);

	return 0;
}

static void stress_serial_exit(void)
{
	hrtimer_cancel(&hr_timer);
	pr_crit("%s: %d\n", __func__, hrtimer_is_queued(&hr_timer));
}

module_init(stress_serial_init);
module_exit(stress_serial_exit);
MODULE_AUTHOR("Eugeniu Rosca <erosca@de.adit-jv.com>");
MODULE_LICENSE("GPL");
