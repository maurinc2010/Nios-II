/*
 * lcd.h
 *
 *  Created on: 4/12/2016
 *      Author: game
 */

#ifndef LCD_H_
#define LCD_H_

#include "type.h"
// commands

#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

#define MODO_4 1
#define MODO_8 0

u8 _displayfunction;
u8 _displaycontrol;
u8 _displaymode;

u8 _initialized;

u8 _numlines,_currline;

void lcd_init(u8,u8, u8);

void lcd_begin(u8 lines, u8 dotsize);

void lcd_noAutoscroll(void);
void lcd_autoscroll(void);
void lcd_rightToLeft(void);
void lcd_leftToRight(void);
void lcd_scrollDisplayRight(void);
void lcd_scrollDisplayLeft(void);
void lcd_clear();
void lcd_home();
void lcd_printNumber(u16 n, u8 base);
void lcd_printFloat(float number, u8 digits);
void lcd_print(char *string);
void lcd_setCursor(u8 col, u8 row);
void lcd_command(u8 value);
void lcd_send(u8 value);

void lcd_write4bits_data(u8 value);
void lcd_write4bits_command(u8 value);
void lcd_write8bits_data(u8 value);
void lcd_write8bits_command(u8 value);



#endif /* LCD_H_ */
