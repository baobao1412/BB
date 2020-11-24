
#include "sht1x_lib.h"



void transmission_start(void ){
    printk("transmission_start!!\n");

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
void init_sht1x(void){
     printk("init_sht1x!!\n");
    msleep(20);
    //SCK is set to low first
    CLOCK_LOW;
    gpio_pud(GPIO_PUD_OFF);
    DATA_LOW;
    sht1x_rs();

    transmission_start();
    send_command(0x03);
    uint16_t valu = 0;
    valu = read_data();
    valu = valu << 8;
    valu = valu|read_data();
    printk("%d\n",valu);

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
    printk("send_command!!\n");

    uint8_t mask;
    uint8_t i=20;
 	for(mask = 0x80; mask; mask>>=1)
	{   
        CLOCK_LOW;

        DELAY_SHT1X;  // SCK hi => sensor reads data
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
    printk("end send\n");

    CLOCK_LOW;	
    DELAY_SHT1X;  // SCK hi => sensor reads data
    DATA_HIGH;
    DELAY_SHT1X;
    CLOCK_HIGH;	
    DELAY_SHT1X;
    CLOCK_LOW;	  
    DELAY_SHT1X; 

    while ( GET_DATA && i)
    {
    printk("data_wait %d %d\n",i,GET_DATA);
    i--;
    mdelay(50);
    }
    
    	
    DELAY_SHT1X;	
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