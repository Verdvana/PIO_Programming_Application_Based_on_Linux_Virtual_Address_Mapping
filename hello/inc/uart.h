/*
 * uart.h
 *
 *  Created on: 2019年4月17日
 *      Author: Verdvana
 */

#ifndef INC_UART_H_
#define INC_UART_H_

void uart_putc(char c);  //字符发送
int uart_getc(void);    //字符接收

void uart_printf(char *str); //字符串发送
int uart_scanf(char *p);    //字符串接收

void uart_0_init(int br);    //串口0初始化函数

#endif /* INC_UART_H_ */
