#include "sht1x_lib.h"


void transmission_start(void )
{
    // printk("transmission_start!!\n");
    CLOCK_HIGH;
    DELAY_SHT1X; 
    DATA_LOW;
    DELAY_SHT1X;
    CLOCK_LOW;
    DELAY_SHT1X;

    CLOCK_HIGH;
    DELAY_SHT1X;
    DATA_HIGH;
    DELAY_SHT1X;
    CLOCK_LOW;
    DELAY_SHT1X;
}
void init_sht1x(void)
{
     printk("init_sht1x!!\n");
    msleep(20);
    //SCK is set to low first
    CLOCK_LOW;
    //Set GPIO PUB  OFF
    gpio_pud(GPIO_PUD_OFF);
    //Data out set to low first
    DATA_LOW;
    //reset sensor
    sht1x_rs();
    //start 
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
uint8_t send_command(uint8_t _cmd)
{
    // printk("send_command!!\n");
    uint8_t mask;
    uint8_t i=20;//coutern 

 	for(mask = 0x80; mask; mask>>=1)
	{   
        CLOCK_LOW;
        DELAY_SHT1X;
		if( _cmd & mask )
		{  
			DATA_HIGH;
            // printk("data_wait %d %d\n",2,GET_DATA); 	
            DELAY_SHT1X;
		}
		else
		{
			DATA_LOW;	
            DELAY_SHT1X;
            // printk("data_wait %d %d\n",4,GET_DATA);
		}
        CLOCK_HIGH;	
        DELAY_SHT1X;   

	}   
    // printk("end send\n");
    CLOCK_LOW;	
    DELAY_SHT1X;  // SCK hi => sensor reads data
    DATA_HIGH;
    DELAY_SHT1X;
    CLOCK_HIGH;	
    DELAY_SHT1X;
    CLOCK_LOW;	  
    DELAY_SHT1X; 

    //wait data complete
    while ( GET_DATA && i)
    {
    printk("data_wait %d %d\n",i,GET_DATA);
    i--;
    mdelay(50);
    if(!i)
    {
        return 0;
    }
    }
    return 1;  	
}
uint16_t read_data()
{
    uint8_t mask;
    uint8_t value = 0;

    for(mask = 0x80; mask; mask >>=1)
    {
        CLOCK_HIGH;
        DELAY_SHT1X;
        if(GET_DATA !=0){
            value |= mask;
        }
        CLOCK_LOW;
        DELAY_SHT1X;
    }
    CLOCK_HIGH;
    DELAY_SHT1X;
    CLOCK_LOW;
    return value;
}
uint16_t calc_data(float *temp_, float *humi_)
{
    
    //request temp
    if(send_command(TEMP))
    {
        //temp
        uint16_t d1 = -4010; //  VDD 5v
        uint8_t d2 = 100; // 14 bit
        uint16_t T = 0;

        T = read_data();
        T  = T  << 8;
        T  = T | read_data();
        
        T = d1 + d2 * T;
        temp_ = T/100;
    }

    printk("%d\n",T);


    if(send_command(HUMI)){
        //temp
        uint32_t c1 = -40000000 ; //12 bit
        uint8_t c2 = -28; //12 bit
        uint32_t c3 =  405000;   //12 bit 
        uint32_t t1 = 100000;
        uint16_t t2 = 800;
        uint16_t RH = 0;    // RH true
        uint8_t RH_ln = 0; //RH linear



        RH = read_data();
        RH  = RH  << 8;
        RH  = RH | read_data();
        
        RH_ln = c1 + c2 * RH + c3 * RH * RH;
        RH = (temp_*10000000-25*10000000) * (t1 + t2 * RH) + RH_ln;

        humi_ = RH/10000000;
    }





    return 1;
}