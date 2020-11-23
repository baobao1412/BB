

/*
 *gpio.h is writen by BB
 *7-11-2020
 *
*/
#ifndef _GPIO_
#define _GPIO_
#include <linux/io.h>


/*--------*/
#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1

#define GPIO_PUD_OFF 0

/*-----Define address--- */
#define GPIO_BASE 0x3f200000
#define GPSET0 7
#define GPSET1 8
#define GPCLR0 10
#define GPCLR1 11
#define GPLVE0 13
#define GPLVE1 14
#define GPPUDCLK0 38
#define GPPUD 37



static volatile uint32_t *gpio_base = NULL;


/*----------------*/


uint8_t addr_gpio(volatile uint32_t *_gpio);
void gpio_pud(uint8_t pin);
void set_mode(uint8_t _pin, uint8_t _mode);
void write_pin(uint8_t pin, uint8_t status);
uint8_t get_status_pin(uint8_t pin);


#endif
