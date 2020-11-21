

/*
 *gpio.h is writen by BB
 *7-11-2020
 *
*/
#include <linux/io.h>
#include <linux/delay.h>


#ifndef _GPIO_
#define _GPIO_

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





/*----------------*/

#define DELAY_SHT1X ndelay(5)

/* Set pullup/down */
void gpio_pud(volatile uint32_t*gpio_map,uint8_t pin)
{
    uint32_t* paddr = gpio_map + GPPUD;
    iowrite32(pin,paddr);
}

// void set_gpio_pudclk(volatile uint32_t*_gpio_map,uint8_t pin, uint8_t on)
// {

//     volatile uint32_t* paddr = _gpio_map + GPPUDCLK0 + pin/32;
//     uint8_t shift = pin % 32;
//     iowrite32(paddr, ((on ? 1 : 0) << shift));

// }



// void gpio_set_pud(volatile uint32_t*_gpio_map,uint8_t pin, uint8_t pud)
// {

//     bcm2835_gpio_pud(_gpio_map,pud);
//     udelay(100);
//     set_gpio_pudclk(_gpio_map,pin, 1);
//     udelay(100);
//     bcm2835_gpio_pud(_gpio_map,GPIO_PUD_OFF);
//     set_gpio_pudclk(_gpio_map,pin, 0);
// }
void set_mode(volatile uint32_t*_gpio_map,uint8_t _pin, uint8_t _mode)
{   
    uint32_t* paddr = _gpio_map + _pin/10;
    uint8_t shift = (_pin % 10) * 3;    

    if(_mode)
    {   
        iowrite32(1<<shift,paddr);
    }
    else
    {   
        iowrite32(0<<shift,paddr);
    }
}

 void write_pin(volatile uint32_t*gpio_map,uint8_t pin, uint8_t status)
{
    // set_mode(gpio_map,pin, OUTPUT);
    uint32_t* paddr;
    uint8_t shift = pin % 32;  
    if(status)
    {
        paddr = gpio_map + GPSET0 + pin/32;
        // iowrite32(0,paddr);
        iowrite32(1<<shift,paddr);
    }
    else
    {
        paddr = gpio_map + GPCLR0 + pin/32;
        // iowrite32(0,paddr);
        iowrite32(1<<shift,paddr);
    }
}

 uint8_t get_status_pin(volatile uint32_t*gpio_map,uint8_t pin)
{
    set_mode(gpio_map,pin,INPUT);
    uint32_t* paddr = gpio_map + GPLVE0 + pin/32;
    uint8_t shift = pin % 32;
    uint32_t value = ioread32(paddr);
    printk("bcm2835_peri_write_nb paddr %p, value %32X\n",
                paddr, value);
    return ((value) & (1 << shift)) ? HIGH : LOW;
}

#endif
