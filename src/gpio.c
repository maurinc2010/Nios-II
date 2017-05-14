/*
 * gpio.c
 *
 *  Created on: 4/12/2016
 *      Author: game
 */

#include <stdio.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "gpio.h"

void digitalwrite(unsigned char pin,unsigned char valor){
	int a=1;
	if (valor==HIGH){
		a<<=pin;
		//IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE,0XAAAA);
		IOWR_ALTERA_AVALON_PIO_SET_BITS(PIO_LED_BASE,a);
	}
	else{
		a<<=pin;
		IOWR_ALTERA_AVALON_PIO_CLEAR_BITS(PIO_LED_BASE, a);
	}
}

unsigned char digitalread(unsigned char pin){
	int a=1;
	int data;
	data=IORD_ALTERA_AVALON_PIO_DATA(PIO_SWICH_BASE);
	data=data & (a<<=pin);
	if (data)
		return HIGH;
	else
		return LOW;
}
