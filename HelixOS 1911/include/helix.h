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

/*引用C标准库*/
#include "string.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"

#define HL_HARDWARE_STM32F103//定义系统类型

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

/*↓系统设置↓*/
#define HL_SYSINFO_CPUARCH "Cortex-M3" //CPU架构
#define HL_SYSINFO_VERSION "0.0.1 BETA" //版本
#define HL_LinkLIST_SIZE 256//最大任务数
#define HL_DYNAMIC_TimeSliceMode 0 //动态调整时间片开关
#define HL_STATIC_TimeSlice 1 //ms 默认时间片
#define HL_MEM_MANAGER_ENABLE //允许内存管理
//#define HL_FILESYSTEM_ENABLE //允许文件系统存在
#define HL_EXTENDED_RAM_EXIST //存在外扩RAM
#define HL_TIME_ENABLE //支持内置RTC

/*↑系统设置↑*/

//进程信息
typedef struct
{
	uint32_t* m_SP;//栈顶指针
	
	uint32_t priority;//优先级越小越优先 作为ID使用
	
	const char* thread_name;
	
	uint8_t PID;
	
	uint32_t* bottom_Stack;// 栈底指针>m_SP
	
	uint32_t Ticks;//被调用的数量
	
	uint32_t TickSlice;//被调用的时间片数量
	
	float CPU_USAGE;//cpu使用率
	
	void (*Thread_Entry)(void); //函数入口 不能带参数
	
	uint8_t specialFlag;
} HL_Thread;

extern uint32_t HL_SYS_INITED;
extern uint8_t HL_GLOBAL_TEMP_STRING[256];
extern void HL_WHILE(void);
void HL_Thread_Create_STATIC(HL_Thread* hl,const char* name,void (*Thread_Entry)(void),uint32_t* bottomStack,uint32_t priority);
void HL_System_Init(void);


/*引用系统内的文件*/
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
