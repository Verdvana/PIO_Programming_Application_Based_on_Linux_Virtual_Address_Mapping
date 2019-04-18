/*
 * main.c
 *
 *  Created on: 2019年3月5日
 *      Author: Verdvana
 */

//gcc标准头文件
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>


//hps 厂家提供的底层定义头文件
#define soc_cv_av	//定义使用soc_cv_av硬件平台

#include "hwlib.h"			//常量定义
#include "socal/socal.h"	//底层操作函数，如位、字节、半字、字的读写
#include "socal/hps.h"		//外设地址信息定义


//与用户具体HPS应用系统相关的硬件描述头文件
#include "hps_0.h"

//
#include "../inc/mpu.h"
#include "../inc/led.h"
#include "../inc/button.h"
#include "../inc/uart.h"

volatile unsigned long *led_pio_virtual_base = NULL;	//led_pio虚拟地址
volatile unsigned long *button_pio_virtual_base = NULL;	//button_pio虚拟地址
volatile unsigned long *uart_0_virtual_base = NULL;     //uart_0虚拟地址

unsigned int button_edge;	//定义边沿捕获寄存器临时变量



int main(int argc, char ** argv) {

	int fd;
	int virtual_base = 0;	//虚拟基地址


	unsigned int led0 = 1, led1 = 1;

	//完成fpga侧外设虚拟地址映射
	fd = fpga_init(&virtual_base);

	uart_0_init(115200); //设置串口0波特率


	printf("1\n");

	bool STOP = false;
	while(STOP == false)
	{
		//读取PIO边沿捕获寄存器以获知是否有检测到设定的边沿
		Button_Edge();

		printf("button_edge=%u\n",button_edge);

		switch (button_edge) {
		case 0x1:  //01

			led0 = !led0; //对FPGA_LED 的bit0取反
				//LED(0); //清除边沿捕获寄存器的bit0位

			if (led0)
				LED(10); //置位led_pio输出 1010101010

			else
				LED(5); //清零led_pio输出 0101010101

			break;

		case 0x2:  //10
			STOP = true;break;	//设置程序退出标志

		case 0x3: //11
			STOP = true;break;	//设置程序退出标志

		default:
			break;
		}
	}

	printf("2\n");
	uart_printf("Hello World! Verdvana\n");
	printf("3\n");
	uart_printf("SoC FPGA\n");

	char rx_buf[128] = {0}; //定义一个128字节的接收数组
	memset(rx_buf,0,128);	//清除数组中内容
	uart_scanf(&rx_buf);	//接受一行数组到rx_buf中
	printf(rx_buf);			//打印当前接受到的字符串内容
	uart_printf(rx_buf);

	//程序退出前，取消虚拟地址映射
	if (munmap(virtual_base, HW_REGS_SPAN) != 0) {
		printf("ERROR: munmap() failed...\n");
		close(fd);
		return (1);
	}

	close(fd); //关闭MPU
	return 0;
}

