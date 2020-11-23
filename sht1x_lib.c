
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
void send_command(uint8_t _cmd)
{
    uint8_t mask;
        uint8_t i;

 	for(mask = 0x80; mask; mask>>=1)
	{
		CLOCK_LOW;	
        DELAY_SHT1X;

		if( value & mask )
		{  
			DATA_HIGH; 	
            DELAY_SHT1X;
		}
		else
		{
			DATA_LOW;	
            DELAY_SHT1X;
		}

		CLOCK_HIGH;	
        DELAY_SHT1X;  // SCK hi => sensor reads data
	}
	CLOCK_LOW;	
    DELAY_SHT1X;
	// Release DATA line
	DATA_HIGH;	
    DELAY_SHT1X;
	CLOCK_HIGH;	
    DELAY_SHT1X;

    set_mode(_dataPin,INPUT);
    DELAY_SHT1X;
    for(i = 0; i<100;i++)
    {
    printk("data_wait %d %d\n",i,GET_DATA);

    }

}