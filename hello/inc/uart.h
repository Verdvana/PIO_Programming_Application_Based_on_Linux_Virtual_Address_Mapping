/*
 * uart.h
 *
 *  Created on: 2019��4��17��
 *      Author: Verdvana
 */

#ifndef INC_UART_H_
#define INC_UART_H_

void uart_putc(char c);  //�ַ�����
int uart_getc(void);    //�ַ�����

void uart_printf(char *str); //�ַ�������
int uart_scanf(char *p);    //�ַ�������

void uart_0_init(int br);    //����0��ʼ������

#endif /* INC_UART_H_ */
