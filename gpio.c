

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
    uint32_t mask = 0x07 << shift;
    uint32_t mode_set = _mode<<shift;

    uint32_t value = ioread32(paddr);
    value = (value & (~mask)) | (mode_set & mask);
    iowrite32(value,paddr);

    // if(_mode)
    // {   
    //     iowrite32((value|(1<<shift)),paddr);
    // }
    // else
    // {   
    //     iowrite32((value|(0<<shift)),paddr);
    // }
}

 void write_pin(uint8_t pin, uint8_t status)
{
    set_mode(pin, OUTPUT);
    uint32_t* paddr_set;
    uint32_t* paddr_clr;

    uint8_t shift = pin % 32;  
    if(status)
    {
        paddr_set = gpio_base + GPSET0 + pin/32;
        paddr_clr = gpio_base + GPCLR0 + pin/32;

        uint32_t value_set = ioread32(paddr_set);
        uint32_t value_clr = ioread32(paddr_clr);

        iowrite32(value_set|(1<<shift),paddr_set);
        iowrite32(value_clr|(0<<shift),paddr_clr);
    }
    else
    {

        paddr_set = gpio_base + GPSET0 + pin/32;
        paddr_clr = gpio_base + GPCLR0 + pin/32;

        uint32_t value_set = ioread32(paddr_set);
        uint32_t value_clr = ioread32(paddr_clr);

        iowrite32(value_set|(0<<shift),paddr_set);
        iowrite32(value_clr|(1<<shift),paddr_clr);
    }
}
 
uint8_t get_status_pin(uint8_t pin)
{
    set_mode(pin,INPUT);
    uint32_t* paddr = gpio_base + GPLVE0 + pin/32;
    uint8_t shift = pin % 32;
    uint32_t value = ioread32(paddr);
    printk("bcm2835_peri_write_nb paddr %p, value %32X\n",
                paddr, value);
    return ((value) & (1 << shift)) ? HIGH : LOW;
}

