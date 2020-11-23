#ifndef RPI_SHT1x_
#define	RPI_SHT1x_

#include "gpio.h"
#include <linux/delay.h>

//define gpio data and clock
#define _dataPin 4
#define _clockPin 17





#define DELAY_SHT1X mdelay(5000)

#define CLOCK_HIGH write_pin(_clockPin,HIGH)
#define CLOCK_LOW write_pin(_clockPin,LOW)

#define DATA_HIGH write_pin(_dataPin,HIGH)
#define DATA_LOW write_pin(_dataPin,LOW)

#define GET_DATA get_status_pin(_dataPin)
#define GET_DATA_CLOCK get_status_pin(_clockPin)
                            


//Functions

extern void init_sht1x(void);
extern void transmission_start(void);
extern void sht1x_rs(void);


#endif
