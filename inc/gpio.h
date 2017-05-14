/*
 * gpio.h
 *
 *  Created on: 4/12/2016
 *      Author: game
 */



#ifndef GPIO_H_
#define GPIO_H_

#define HIGH 1
#define LOW  0
#define OUTPUT 1
#define INPUT 0


void pinmode(unsigned char,unsigned char);
void digitalwrite(unsigned char,unsigned char);
unsigned char digitalread(unsigned char);


#endif /* GPIO_H_ */
