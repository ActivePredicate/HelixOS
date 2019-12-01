#include "helix.h"

uint32_t HL_SYS_INITED=0;
uint8_t HL_GLOBAL_TEMP_STRING[256];
uint32_t HL_System_Stack[HL_LARGE_STACK_SIZE];


void HL_WHILE(void)
{
	
	while(1);
}

void HL_Thread_Create_STATIC(HL_Thread* hl,const char* name,void (*Thread_Entry)(void),uint32_t* bottomStack,uint32_t priority)
{
	hl->m_SP=HL_System_INIT_STACK(bottomStack,Thread_Entry);
	hl->bottom_Stack=bottomStack;
	hl->priority=priority;
	hl->Ticks=0;
	hl->TickSlice=0;
	hl->Thread_Entry=Thread_Entry;
	hl->thread_name=name;
	hl->PID=HL_LinkLIST_LENG;
	HL_LinkLIST_Insert((uint32_t)hl);
}

#ifdef HL_EXTENDED_RAM_EXIST
#define SRAM_SIZE 1048576
uint32_t* fsmc_sram=(uint32_t*)0x68000000;
#endif

void HL_System_Init()
{
	#ifdef HL_EXTENDED_RAM_EXIST
	HL_Mem_AssignPool(&DefaultPool,(uint32_t)fsmc_sram,SRAM_SIZE,HL_MEM_DEFAULT_MANAGEPOOL_SIZE);
	HL_System_Terminal_Stack=(uint32_t*)hmalloc(4*HL_BYTES_4KB); //实际上分配了4kb
	HL_Thread_Create_STATIC(&hl_terminal_thread,"CMD",HL_Terminal_Entry,(HL_System_Terminal_Stack+HL_BYTES_4KB-1),1);
	//为终端缓存区分配空间
	HL_System_Terminal_INPUT_BUFFER=hmalloc(HL_TERMINAL_BUFFER_SIZE);
	HL_System_Terminal_INPUT_TEMPBUFFER=hmalloc(HL_TERMINAL_BUFFER_SIZE);
	HL_System_Terminal_INPUT_DATA=hmalloc(64); //64
	HL_System_Terminal_INPUT_CMD=hmalloc(16); //16
	//申请内存后要清理
	memset(HL_System_Terminal_INPUT_BUFFER,0,HL_TERMINAL_BUFFER_SIZE);
	memset(HL_System_Terminal_INPUT_TEMPBUFFER,0,HL_TERMINAL_BUFFER_SIZE);
	memset(HL_System_Terminal_INPUT_DATA,0,64);
	memset(HL_System_Terminal_INPUT_CMD,0,16);
	#else
	HL_Thread_Create_STATIC(&hl_terminal_thread,"CMD",HL_Terminal_Entry,&HL_System_Terminal_Stack[HL_LARGE_STACK_SIZE-1],1);
	#endif
	HL_Terminal_Write("\r\n#########\r\nHelix RealTime Operation System\r\n#########\r\n");
	HL_APP_SYSINFO();
	HL_USERDEFINED_INITFUNC();
	
	HL_Interrupt_DISABLE();
	HL_System_Pulse_Enable();
	HL_System_INIT_Hidden((uint32_t)&HL_System_Stack[HL_LARGE_STACK_SIZE-1]);
	
	HL_WHILE();//等待调度器执行第一次调度
}


