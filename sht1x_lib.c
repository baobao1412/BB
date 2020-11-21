#include "sht1x_lib.h"
#include <linux/delay.h>

void transmission_start(){
    DATA_LOW;
    DELAY_SHT1X;   
    CLOCK_HIGH;
    DELAY_SHT1X;
    CLOCK_LOW;
    DELAY_SHT1X;

    DATA_HIGH;
    DELAY_SHT1X;   
    CLOCK_HIGH;
    DELAY_SHT1X;
    CLOCK_LOW;
    DELAY_SHT1X;
         
}
void init_sht1x(){
  

    //SCK is set to low first
    CLOCK_LOW;
    //set mode for gpio
    set_mode(gpio_map,_clockPin,OUTPUT);
    DATA_HIGH;
    set_mode(gpio_map,_dataPin,OUTPUT);
    gpio_pud(gpio_map,GPIO_PUD_OFF);
    //
    sht1x_rs();
    transmission_start();


}
void sht1x_rs(){
    unsigned char i;
    DATA_HIGH;
    DELAY_SHT1X;

    for (i = 0; i < 9; i++)
    {
        CLOCK_HIGH;
        DELAY_SHT1X;
        CLOCK_LOW;
        DELAY_SHT1X;
    }  
}
