/*
 * aurt.h
 *
 *  Created on: 4/12/2016
 *      Author: game
 */

#ifndef AURT_H_
#define AURT_H_
#include "type.h"

void uart_print(char *string);
void set_baud(int baud);
void set_numbits(u8 num_bits);
void set_parity(char a);
char *uart_flag_read();

void uart_init(int,u8,u8);
void uart_send(u8);
u8 uart_read();

#endif /* AURT_H_ */
