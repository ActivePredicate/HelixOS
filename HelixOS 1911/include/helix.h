#ifndef HELIX_h_
#define HELIX_h_

#include "main.h"

/*
HelixOS designed by hans
Transplant Tips:
OS is running on HAL Library
When making the OS on another platform
You need to confirm the configurations below
1 Confirm the System Type
2 Confirm the System Hard Settings
3 Make sure the SYSCLOCK SETTINGS and the timeslice
4 Disable the unused functions to reduce the code size
5 Go to pre_usrprvo_interface.c and rewrite all the functions
6 NVIC should be set to 2 bit 2 bit mode
7 check the arch_support.c on whether it works
8 The default timeslice is 1ms and Pulse Clock Frequence is suggested to be 1ms
*/

/*����C��׼��*/
#include "string.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"

#define HL_HARDWARE_STM32F103//����ϵͳ����

#define HL_SMALL_STACK_SIZE 128
#define HL_MIDDLE_STACK_SIZE 256
#define HL_LARGE_STACK_SIZE 512
#define HL_HUGE_STACK_SIZE 1024

#define HL_BYTES_1KB 1024
#define HL_BYTES_2KB 2048
#define HL_BYTES_4KB 4096
#define HL_BYTES_8KB 8192


#define HL_SYS_FLAG_EMPTY 0x08
#define HL_SYS_FLAG_SYSTEM 0x04
#define HL_SYS_FLAG_USER 0x00

/*��ϵͳ���á�*/
#define HL_SYSINFO_CPUARCH "Cortex-M3" //CPU�ܹ�
#define HL_SYSINFO_VERSION "0.0.1 BETA" //�汾
#define HL_LinkLIST_SIZE 256//���������
#define HL_DYNAMIC_TimeSliceMode 0 //��̬����ʱ��Ƭ����
#define HL_STATIC_TimeSlice 1 //ms Ĭ��ʱ��Ƭ
#define HL_MEM_MANAGER_ENABLE //�����ڴ����
//#define HL_FILESYSTEM_ENABLE //�����ļ�ϵͳ����
#define HL_EXTENDED_RAM_EXIST //��������RAM
#define HL_TIME_ENABLE //֧������RTC

/*��ϵͳ���á�*/

//������Ϣ
typedef struct
{
	uint32_t* m_SP;//ջ��ָ��
	
	uint32_t priority;//���ȼ�ԽСԽ���� ��ΪIDʹ��
	
	const char* thread_name;
	
	uint8_t PID;
	
	uint32_t* bottom_Stack;// ջ��ָ��>m_SP
	
	uint32_t Ticks;//�����õ�����
	
	uint32_t TickSlice;//�����õ�ʱ��Ƭ����
	
	float CPU_USAGE;//cpuʹ����
	
	void (*Thread_Entry)(void); //������� ���ܴ�����
	
	uint8_t specialFlag;
} HL_Thread;

extern uint32_t HL_SYS_INITED;
extern uint8_t HL_GLOBAL_TEMP_STRING[256];
extern void HL_WHILE(void);
void HL_Thread_Create_STATIC(HL_Thread* hl,const char* name,void (*Thread_Entry)(void),uint32_t* bottomStack,uint32_t priority);
void HL_System_Init(void);


/*����ϵͳ�ڵ��ļ�*/
#include "library.h"
#include "mem_manager.h"
#include "scheduler.h"
#include "pre_usrprvo_interface.h"
#include "arch_support.h"
#include "htime.h"
#include "sys_app.h"
#include "Terminal.h"
#include "file_system.h"

#endif
