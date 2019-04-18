/*
 * main.c
 *
 *  Created on: 2019��3��5��
 *      Author: Verdvana
 */

//gcc��׼ͷ�ļ�
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>


//hps �����ṩ�ĵײ㶨��ͷ�ļ�
#define soc_cv_av	//����ʹ��soc_cv_avӲ��ƽ̨

#include "hwlib.h"			//��������
#include "socal/socal.h"	//�ײ������������λ���ֽڡ����֡��ֵĶ�д
#include "socal/hps.h"		//�����ַ��Ϣ����


//���û�����HPSӦ��ϵͳ��ص�Ӳ������ͷ�ļ�
#include "hps_0.h"

//
#include "../inc/mpu.h"
#include "../inc/led.h"
#include "../inc/button.h"
#include "../inc/uart.h"

volatile unsigned long *led_pio_virtual_base = NULL;	//led_pio�����ַ
volatile unsigned long *button_pio_virtual_base = NULL;	//button_pio�����ַ
volatile unsigned long *uart_0_virtual_base = NULL;     //uart_0�����ַ

unsigned int button_edge;	//������ز���Ĵ�����ʱ����



int main(int argc, char ** argv) {

	int fd;
	int virtual_base = 0;	//�������ַ


	unsigned int led0 = 1, led1 = 1;

	//���fpga�����������ַӳ��
	fd = fpga_init(&virtual_base);

	uart_0_init(115200); //���ô���0������


	printf("1\n");

	bool STOP = false;
	while(STOP == false)
	{
		//��ȡPIO���ز���Ĵ����Ի�֪�Ƿ��м�⵽�趨�ı���
		Button_Edge();

		printf("button_edge=%u\n",button_edge);

		switch (button_edge) {
		case 0x1:  //01

			led0 = !led0; //��FPGA_LED ��bit0ȡ��
				//LED(0); //������ز���Ĵ�����bit0λ

			if (led0)
				LED(10); //��λled_pio��� 1010101010

			else
				LED(5); //����led_pio��� 0101010101

			break;

		case 0x2:  //10
			STOP = true;break;	//���ó����˳���־

		case 0x3: //11
			STOP = true;break;	//���ó����˳���־

		default:
			break;
		}
	}

	printf("2\n");
	uart_printf("Hello World! Verdvana\n");
	printf("3\n");
	uart_printf("SoC FPGA\n");

	char rx_buf[128] = {0}; //����һ��128�ֽڵĽ�������
	memset(rx_buf,0,128);	//�������������
	uart_scanf(&rx_buf);	//����һ�����鵽rx_buf��
	printf(rx_buf);			//��ӡ��ǰ���ܵ����ַ�������
	uart_printf(rx_buf);

	//�����˳�ǰ��ȡ�������ַӳ��
	if (munmap(virtual_base, HW_REGS_SPAN) != 0) {
		printf("ERROR: munmap() failed...\n");
		close(fd);
		return (1);
	}

	close(fd); //�ر�MPU
	return 0;
}
