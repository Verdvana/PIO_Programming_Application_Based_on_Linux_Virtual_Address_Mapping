/*
 * button.c
 *
 *  Created on: 2019年3月26日
 *      Author: Verdvana
 */


#include <stddef.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "../inc/button.h"

extern volatile unsigned long *button_pio_virtual_base ;

extern unsigned int button_edge;	//定义边沿捕获寄存器临时变量

void Button_Edge(void)
{
	button_edge = *(button_pio_virtual_base + 3);  	//读取PIO边沿捕获器
	*(button_pio_virtual_base + 3) = 0x3;			//清除边沿捕获器的bit0，bit1的值
}
