/*
 * aurt.c
 *
 *  Created on: 5/12/2016
 *      Author: game
 */
#include "altera_avalon_uart_regs.h"
#include "type.h"
#include <unistd.h>
#include "system.h"

void set_baud(int baud){
	int div=UART_FREQ/(baud+1);
	IOWR_ALTERA_AVALON_UART_DIVISOR(UART_BASE,div);

}
//void set_numbits(u8 num_bits){
//	UART_DATA_BITS=num_bits;

//}

//void set_parity(char a){
//	UART_PARITY=a;
//}

void uart_init(int baud,u8 num_bits,u8 parity){
	set_baud(baud);
//	set_numbits(num_bits);
//	set_parity(parity);
}

void uart_send(u8 tx){
	//TRDY =0 txdata full
	//TRDY =1 txdata empity
	while(!(IORD_ALTERA_AVALON_UART_STATUS(UART_BASE)& ALTERA_AVALON_UART_STATUS_TRDY_MSK));
	IOWR_ALTERA_AVALON_UART_TXDATA(UART_BASE, tx);

}
u8 uart_read(){
	//RRDY =0 rxdata empity
	//RRDY =1 rxdata full
	while(!(IORD_ALTERA_AVALON_UART_STATUS(UART_BASE)& ALTERA_AVALON_UART_STATUS_RRDY_MSK));
	return IORD_ALTERA_AVALON_UART_RXDATA(UART_BASE);
}

char *uart_flag_read(){
	char c;
	u8 i = 0;
	static char buffer[80];
	if (IORD_ALTERA_AVALON_UART_STATUS(UART_BASE)& ALTERA_AVALON_UART_STATUS_RRDY_MSK){
		buffer[i++]=IORD_ALTERA_AVALON_UART_RXDATA(UART_BASE);
		do {
		    c = uart_read();
		    buffer[i++] = c;
		}while (c != '\r');
		buffer[i++]='\n';
		buffer[i] = '\r';
	}
	else
		buffer[i]='\0';
	return (buffer);
}

void uart_print(char *msm){
    u8 a=0;
    do{
        uart_send(msm[a++]);
    }while (msm[a]!='\r');
    uart_send('\n');
    uart_send('\r');
    //while (uart_read()!='\n');
}

char * uart_GetString()
{
    u8 i = 0;
    char c;
    static char buffer[80];
    do {
        c = uart_read();
        //SerialPrintf(port, (u8 *)"%c", c);
        //SerialPutChar(port, c);
        buffer[i++] = c;
    } while (c != '\r');
    buffer[i++]='\n';
    buffer[i] = '\r';

    //uart_send('\n');
    return (buffer);
}
