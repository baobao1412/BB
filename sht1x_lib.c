
#include "sht1x_lib.h"



void transmission_start(void ){
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
void init_sht1x(void){
  printk("init_sht1x!!\n");

    //SCK is set to low first
    CLOCK_LOW;
    //set mode for gpio
    set_mode(_clockPin,OUTPUT);
    DATA_HIGH;
    set_mode(_dataPin,OUTPUT);
    gpio_pud(GPIO_PUD_OFF);
    // //
    sht1x_rs();
    transmission_start();


}
void sht1x_rs(void){
    unsigned char i;
    DATA_HIGH;
    DELAY_SHT1X;

    for (i = 0; i < 9; i++)
    {
        // printk("%d - clock %d\n",i,);
        CLOCK_HIGH;
        DELAY_SHT1X;
        CLOCK_LOW;
        DELAY_SHT1X;
    }  
}
