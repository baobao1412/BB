

/*
 *gpio.h is writen by BB
 *7-11-2020
 *
*/
 #include <linux/io.h>

#ifndef _GPIO_
#define _GPIO_


#define GPIO_BASE 0x3f200000
#define GPSET0 7
#define GPSET1 8
#define GPCLR0 10
#define GPCLR1 11
#define GPLVE0 13
#define GPLVE1 14



#define INPUT(pin)	iowrite32(0<<(pin%10)*3,gpio_map+(pin/10))
#define OUTPUT(pin)	iowrite32(1<<(pin%10)*3,gpio_map+(pin/10))

#define SET_PIN_HIGH(pin)	(pin<32?iowrite32(1<<(pin-0),gpio_map + GPSET0):iowrite32(1<<(pin-32),gpio_map + GPSET1))
#define SET_PIN_LOW(pin)	(pin<32?iowrite32(1<<(pin-0),gpio_map + GPCLR0):iowrite32(1<<(pin-32),gpio_map + GPCLR1))

#define READ_PIN(pin) pin<32?(((ioread32(gpio_map + GPLVE0))&((1<<(pin-0))))>>(pin-0)):(((ioread32(gpio_map + GPLVE1))&(1<<(pin-32)))>>pin-32)
#endif
