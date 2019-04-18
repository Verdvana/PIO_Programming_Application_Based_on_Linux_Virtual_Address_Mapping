/*
 * button.c
 *
 *  Created on: 2019��3��26��
 *      Author: Verdvana
 */


#include <stddef.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "../inc/button.h"

extern volatile unsigned long *button_pio_virtual_base ;

extern unsigned int button_edge;	//������ز���Ĵ�����ʱ����

void Button_Edge(void)
{
	button_edge = *(button_pio_virtual_base + 3);  	//��ȡPIO���ز�����
	*(button_pio_virtual_base + 3) = 0x3;			//������ز�������bit0��bit1��ֵ
}