/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <drivers/gpio.h>


#define LEDRED_NODE DT_ALIAS(ledred)
#define LEDGREEN_NODE DT_ALIAS(ledgreen)
#define LEDBLUE_NODE DT_ALIAS(ledblue)


static const struct gpio_dt_spec ledred   = GPIO_DT_SPEC_GET(LEDRED_NODE, gpios);
static const struct gpio_dt_spec ledgreen = GPIO_DT_SPEC_GET(LEDGREEN_NODE, gpios);
static const struct gpio_dt_spec ledblue  = GPIO_DT_SPEC_GET(LEDBLUE_NODE, gpios);


/**
* init_failed()
* function called if there i any kinf od zephyr initialisation problem
*/
void init_failed(void) {

	printk("Zephyr Init failed\n");
	while(1);  // Just a simple trap for errors
}



/**
* main()
* main -> check for proper zephyr inits then just toggle all 3 leds in a loop
*/
void main(void)
{
	int ret;
	printk("Hello World! %s\n", CONFIG_BOARD);

      /* Check if all devices initalised properly */
	if (!device_is_ready(ledred.port)) {
		init_failed();
	}
	if (!device_is_ready(ledgreen.port)) {
		init_failed();
	}
	if (!device_is_ready(ledblue.port)) {
		init_failed();
	}

	/* make all led pin output */
	ret = gpio_pin_configure_dt(&ledred, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		init_failed();
	}

	ret = gpio_pin_configure_dt(&ledgreen, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		init_failed();
	}

	ret = gpio_pin_configure_dt(&ledblue, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		init_failed();
	}

	/* Main loop, just flash RBG leds HITE at 1 Hz and print "+" to console */
	while(1) {
		gpio_pin_toggle_dt(&ledblue);
		gpio_pin_toggle_dt(&ledred);
		gpio_pin_toggle_dt(&ledgreen);
		k_msleep(500);
		printk("+");
	
	}
}
