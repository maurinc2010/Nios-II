/*
 * lcd.c
 *
 *  Created on: 4/12/2016
 *      Author: game
 */
#include <stdio.h>
#include "system.h"
#include "altera_avalon_lcd_16207_regs.h"
#include <unistd.h>  //libreria de retardos
#include "gpio.h"
#include <type.h>
#include "lcd.h"
#include <stdarg.h>
#define PRINTF_BUF_LEN 12

void lcd_write4bits_data(u8 value)
{
	IOWR_ALTERA_AVALON_LCD_16207_DATA(LCD_16X2_BASE,(value  & 0xF0));
	IOWR_ALTERA_AVALON_LCD_16207_DATA(LCD_16X2_BASE,(value<<4 & 0xF0));
}

void lcd_write4bits_command(u8 value)
{
	IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_16X2_BASE,(value & 0xF0));
	IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_16X2_BASE,(value<<4 & 0xF0));
}

void lcd_write8bits_data(u8 value)
{
	IOWR_ALTERA_AVALON_LCD_16207_DATA(LCD_16X2_BASE,value);
}

void lcd_write8bits_command(u8 value)
{
	IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_16X2_BASE,value);
}


void lcd_send(u8 value)
{
	if (_displayfunction & LCD_8BITMODE)
	{
		lcd_write8bits_data(value);
	}
	else
	{
		lcd_write4bits_data(value);	// Upper 4 bits first
	}
}

void lcd_command(u8 value){
	if (_displayfunction & LCD_8BITMODE)
		{
			lcd_write8bits_command(value);
		}
		else
		{
			lcd_write4bits_command(value);	// Upper 4 bits first
		}
}

void lcd_setCursor(u8 col, u8 row)
{
	u8 row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if (_numlines==1) {
		row_offsets[1] = 0x14;
		row_offsets[2] = 0x28;
		row_offsets[3] = 0x3C;
		}
	lcd_command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void lcd_print(char *string)
{
	u8 i=0;
	for( i=0; string[i]; i++){
		lcd_send(string[i]);
		usleep(1000);
	}

}

void lcd_printNumber(u16 n, u8 base)
{
	u8 buf[8 * sizeof(long)];
	u16 i = 0;

	if (n == 0)
	{
		lcd_send('0');
		return;
	}

	while (n > 0)
	{
		buf[i++] = n % base;
		n /= base;
	}

	for (; i > 0; i--){
		//lcd_send(buf[i-1]+0x30);
		 //printf("%2d \n",(buf[i - 1] < 10 ? '0' + buf[i - 1] : 'A' + buf[i - 1] - 10)-0x30);
		 lcd_send((char) (buf[i - 1] < 10 ? '0' + buf[i - 1] : 'A' + buf[i - 1] - 10));
		 usleep(1000);
	}
}

void lcd_printFloat(float number, u8 digits)
{
	u8 i, toPrint;
	u16 int_part;
	float rounding, remainder;
	//number=-658.54;
	printf("%5.2f",number);
	if(number<0.00)
	{
		//printf("Float menor que  0.0!\n");
		lcd_send('-');
		number = -number;
	}


	rounding = 0.1;
	for (i=0; i<digits; ++i)
		rounding /= 10.0;

	number += rounding;


	int_part = (u16)number;
	remainder = number - (float)int_part;
	lcd_printNumber(int_part, 10);


	if (digits > 0)
		lcd_send('.');


	while (digits-- > 0)
	{
		remainder *= 10.0;
		toPrint = (unsigned int)remainder;
		lcd_printNumber(toPrint, 10);
		remainder -= toPrint;
	}
}


void lcd_home()
{
	lcd_command(LCD_RETURNHOME);
	usleep(2000);

}

void lcd_clear()
{
	lcd_command(LCD_CLEARDISPLAY);
	usleep(2000);
}

void lcd_scrollDisplayLeft(void)
{
	lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void lcd_scrollDisplayRight(void)
{
	lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void lcd_leftToRight(void)
{
	_displaymode |= LCD_ENTRYLEFT;
	lcd_command(LCD_ENTRYMODESET | _displaymode);
}

void lcd_rightToLeft(void)
{
	_displaymode &= ~LCD_ENTRYLEFT;
	lcd_command(LCD_ENTRYMODESET | _displaymode);
}

void lcd_autoscroll(void) {
	_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	lcd_command(LCD_ENTRYMODESET | _displaymode);
}

void lcd_noAutoscroll(void) {
	_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	lcd_command(LCD_ENTRYMODESET | _displaymode);
}



void lcd_begin(u8 lines, u8 dotsize)
{
    if (lines > 1)
        _displayfunction |= LCD_2LINE;

    _numlines = lines;
    _currline = 0;
    if ((dotsize != 0) && (lines == 1))
        _displayfunction |= LCD_5x10DOTS;
    usleep(15000);
    if (!(_displayfunction & LCD_8BITMODE) )
    {
        lcd_command(LCD_FUNCTIONSET | _displayfunction);
        usleep(5000);
        lcd_command(LCD_FUNCTIONSET | _displayfunction);
        usleep(150000);
        printf("LCD MODO 4 BITS!\n");
    }

    else
    {
    	lcd_command(LCD_FUNCTIONSET | _displayfunction);
        usleep(5000);
        lcd_command(LCD_FUNCTIONSET | _displayfunction);
        usleep(5000);
        lcd_command(LCD_FUNCTIONSET | _displayfunction);
        printf("LCD MODO 8 BITS!\n");
    }


    lcd_command(LCD_FUNCTIONSET | _displayfunction);
    _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
    // clear it off
    lcd_command(LCD_CLEARDISPLAY);
    usleep(2500);
    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    lcd_command(LCD_ENTRYMODESET | _displaymode);
    usleep(2500);
}

void lcd_init(u8 cuatro_bits,u8 leng, u8 line){
	if (cuatro_bits)
		_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
	else
		_displayfunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;
	lcd_begin(leng,line);
}






