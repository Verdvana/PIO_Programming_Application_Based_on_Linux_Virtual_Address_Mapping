/*
 * mpu.h
 *
 *  Created on: 2019��3��26��
 *      Author: Verdvana
 */

#ifndef MPU_H_
#define MPU_H_

#include <string.h>

#define HW_REGS_BASE (ALT_STM_OFST )	//HPS�����ַ�λ���ַ  0xfc000000
#define HW_REGS_SPAN (0x04000000 )		//HPS�����ַ�ε�ַ�ռ�
#define HW_REGS_MASK (HW_REGS_SPAN - 1 )	//HPS�����ַ�ε�ַ����



int fpga_init(long int *virtual_base);

#endif /* MPU_H_ */