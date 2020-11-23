

#include "gpio.h"
uint8_t addr_gpio(volatile uint32_t *_gpio)
{
    gpio_base = _gpio;

    if(gpio_base)
    {
        return -1;// Failed
    }
    else
    {
        return 1;//OK
    }
}

/* Set pullup/down */
void gpio_pud(uint8_t pin)
{
    uint32_t* paddr = gpio_base + GPPUD;
    iowrite32(pin,paddr);
}
void set_mode(uint8_t _pin, uint8_t _mode)
{   
    uint32_t* paddr = gpio_base + _pin/10;
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

 void write_pin(uint8_t pin, uint8_t status)
{
    // set_mode(gpio_map,pin, OUTPUT);
    uint32_t* paddr;
    uint8_t shift = pin % 32;  
    if(status)
    {
        paddr = gpio_base + GPSET0 + pin/32;
        // iowrite32(0,paddr);
        iowrite32(1<<shift,paddr);
    }
    else
    {
        paddr = gpio_base + GPCLR0 + pin/32;
        // iowrite32(0,paddr);
        iowrite32(1<<shift,paddr);
    }
}

 uint8_t get_status_pin(uint8_t pin)
{
    // set_mode(gpio_base,pin,INPUT);
    uint32_t* paddr = gpio_base + GPLVE0 + pin/32;
    uint8_t shift = pin % 32;
    uint32_t value = ioread32(paddr);
    // printk("bcm2835_peri_write_nb paddr %p, value %32X\n",
    //             paddr, value);
    return ((value) & (1 << shift)) ? HIGH : LOW;
}

