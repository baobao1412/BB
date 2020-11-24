#ifndef RPI_SHT1x_
#define	RPI_SHT1x_

#include "gpio.h"
#include <linux/delay.h>

//define gpio data and clock
#define _dataPin 4
#define _clockPin 17


#define LOW 0
#define HIGH 1


#define DELAY_SHT1X udelay(10)

#define CLOCK_HIGH write_pin(_clockPin,HIGH)
#define CLOCK_LOW write_pin(_clockPin,LOW)

#define DATA_HIGH write_pin(_dataPin,HIGH)
#define DATA_LOW write_pin(_dataPin,LOW)

#define GET_DATA get_status_pin(_dataPin)
                            


//Functions

void init_sht1x(void);
void transmission_start(void);
void sht1x_rs(void);
void send_command(uint8_t _cmd);
uint16_t read_data(void);

#endif
