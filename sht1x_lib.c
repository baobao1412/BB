#include "gpio.h"
#include <linux/delay.h>

#define _dataPin 4
#define _clockPin 17
#define test_ 18

#define CLOCK_HIGH write_pin(_gpio_map,_clockPin,HIGH)
#define CLOCK_LOW write_pin(_gpio_map,test_,LOW)

#define DATA_HIGH write_pin(_gpio_map,_dataPin,HIGH)
#define DATA_LOW write_pin(_gpio_map,_dataPin,LOW)

#define GET_DATA get_status_pin(_gpio_map,_dataPin)
#define GET_DATA_CLOCK get_status_pin(_gpio_map,_clockPin)

static volatile uint32_t * _gpio_map;

uint8_t send_data(uint8_t data,uint8_t CRC)
{
	uint8_t i;
 
	//send data 
	for(i = 0x80; i; i>>=1)
	{
        printk("start--%d - %d\n",i,GET_DATA_CLOCK);
		CLOCK_LOW;
        msleep(2);
		if( data & i )
		{  
            printk("3--%d\n",GET_DATA_CLOCK);
            printk("1--%d - %d\n",i,GET_DATA);
			DATA_HIGH;printk("1--%d - %d\n",i,GET_DATA);
            msleep(2);
            printk("%d\n",1);printk("bug--%d - %d\n",i,GET_DATA);
		}
		else
		{
            printk("1--%d - %d\n",i,GET_DATA);
			DATA_LOW;printk("1--%d - %d\n",i,GET_DATA);
            msleep(2);
            printk("%d\n",0);printk("bug--%d - %d\n",i,GET_DATA);
		}
		CLOCK_HIGH;printk("start--%d\n",GET_DATA_CLOCK);
        msleep(2);printk("enddata--%d\n",GET_DATA);	
	}
    printk("4--%d\n",GET_DATA);		
    CLOCK_LOW;printk("3--%d\n",GET_DATA_CLOCK);
    msleep(2);
	//release command
    printk("4--%d\n",GET_DATA);	 DATA_HIGH;
    msleep(2);printk("4--%d\n",GET_DATA);	
	CLOCK_HIGH;printk("3--%d\n",GET_DATA_CLOCK);
    msleep(2);
    return 1;
}
void trasmission_(void){
    // stransmission start
    CLOCK_HIGH;printk("clock%d\n",GET_DATA_CLOCK);
    msleep(2);
    DATA_LOW;printk("1--%d\n",GET_DATA);
    msleep(2);
    CLOCK_LOW;printk("clock%d\n",GET_DATA_CLOCK);
    msleep(2);
    //
    CLOCK_HIGH;printk("clock%d\n",GET_DATA_CLOCK);
    msleep(2);
    DATA_HIGH;printk("2--%d\n",GET_DATA);
    msleep(2);
    CLOCK_LOW;printk("clock%d\n",GET_DATA_CLOCK);
    msleep(2);
        printk("end clock%d\n",GET_DATA_CLOCK);

    printk("end%d\n",GET_DATA);
}
void init_sht1x(volatile uint32_t*addr){

   gpio_pud(addr,GPIO_PUD_OFF);
    
    mdelay(11);
    // CLOCK_LOW;
    DATA_HIGH;
    mdelay(1);
    uint8_t i;
    uint8_t re_ = 30;

    for(i = 0; i<9;i++){
        printk("%d - %d\n",i,GET_DATA_CLOCK);
        CLOCK_HIGH;
        printk("%d - %d\n",i,GET_DATA_CLOCK);
        printk("%d - %d\n",i,GET_DATA_CLOCK);
        printk("--%d\n",GET_DATA);
        mdelay(10);
        
        printk("%d - %d\n",i,GET_DATA_CLOCK);
        mdelay(10);
        CLOCK_LOW;
        printk("%d - %d\n",i,GET_DATA_CLOCK);
        printk("--%d\n",GET_DATA);
        mdelay(10);
        printk("s--%d\n",GET_DATA);
    }
    //transmission start    
    trasmission_();
    //reset sht1x command 11110
    send_data(re_,0);

}

uint8_t read_data_sensor(void){
	uint8_t _data = 0;
	
	uint8_t i ;

	for ( i = 0x80 ; i; i>>=1)
    {
	CLOCK_HIGH;
    msleep(2);
	if(GET_DATA == 1){
		_data |=i;
	}
	CLOCK_LOW;
    msleep(2);

	}
       // CLOCK_HIGH;
    // msleep(2);
	printk("%d\n",_data); 
    return _data;
}
void wait_data(uint8_t w){
    uint8_t cout_ = 0;
 
    printk("+%d\n",w);

    if(w){

        cout_ = 80;
        printk("   +%d\n",cout_);

    }
    //wait 80ms for 12 bit
    while(cout_>0){
        printk("+%d\n",GET_DATA);
        mdelay(5);
        cout_--;
    }
}

void read_temp_sensor(void){
    uint8_t TEMP = 3;
    uint8_t value_1 = 0;
    uint8_t value_2 = 0;

    uint8_t _wait = 0;
    trasmission_();
    
    _wait = send_data(TEMP,0);//send command 
    printk("wait = %d\n",_wait);
    wait_data(_wait);
    // value_1 = read_data_sensor();
    // printk("temp = %d\n" , value_1);
}