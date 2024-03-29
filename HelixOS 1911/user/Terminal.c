#include "Terminal.h"

HL_Thread hl_terminal_thread;

#ifndef HL_EXTENDED_RAM_EXIST
uint32_t HL_System_Terminal_Stack[HL_LARGE_STACK_SIZE];
uint8_t HL_System_Terminal_INPUT_BUFFER[HL_TERMINAL_BUFFER_SIZE];
uint8_t HL_System_Terminal_INPUT_TEMPBUFFER[HL_TERMINAL_BUFFER_SIZE];
uint8_t HL_System_Terminal_INPUT_DATA[64];
uint8_t HL_System_Terminal_INPUT_CMD[16];
#else
uint32_t* HL_System_Terminal_Stack; //大小8kb
uint8_t* HL_System_Terminal_INPUT_BUFFER;
uint8_t* HL_System_Terminal_INPUT_TEMPBUFFER;
uint8_t* HL_System_Terminal_INPUT_DATA; //64
uint8_t* HL_System_Terminal_INPUT_CMD; //16
#endif

uint8_t HL_Terminal_EnterPassword=0;
uint8_t HL_System_Terminal_INPUT_PTR=0;

void HL_Terminal_Handler(void)
{
	if(HL_CompareString((const char*)HL_System_Terminal_INPUT_CMD,"get-sysinfo"))
	{
		HL_APP_SYSINFO();
	}
	else if(HL_CompareString((const char*)HL_System_Terminal_INPUT_CMD,"get-time"))
	{
		HL_APP_GetTime();
	}
	else if(HL_CompareString((const char*)HL_System_Terminal_INPUT_CMD,"get-cpurate"))
	{
		HL_APP_GetCPURATE();
	}
	else if(HL_CompareString((const char*)HL_System_Terminal_INPUT_CMD,"get-threads"))
	{
		HL_APP_GetThread();
	}
	else if(HL_CompareString((const char*)HL_System_Terminal_INPUT_CMD,"set-standby"))
	{
		HL_Terminal_Write("[WARNINGS] CPU IS ABOUT TO ENTER STANDBY MODE.");
		HAL_PWR_EnterSTANDBYMode();
	}
	else if(HL_CompareString((const char*)HL_System_Terminal_INPUT_CMD,"set-time"))
	{
		HL_APP_SetTime();
	}
	else
	{
		HL_Terminal_Write("Unknown Command:");
		HL_Terminal_Write(HL_System_Terminal_INPUT_CMD);
	}
	
}

void HL_Terminal_Entry(void)
{
	while(1)
	{
		HL_Terminal_Write("NON-USER:^$");
		HL_Terminal_ReadLine(HL_System_Terminal_INPUT_DATA);
		HL_Terminal_Write("\r\n");
		HL_ScanNext(HL_System_Terminal_INPUT_DATA,HL_System_Terminal_INPUT_CMD);
		/*From this below to handle the input*/
		HL_Terminal_Handler();
		/*From this above to handle the input*/
		HL_Terminal_Write("\r\n");
		memset(HL_System_Terminal_INPUT_CMD,0,16);
		memset(HL_System_Terminal_INPUT_DATA,0,64);
		
		HL_CPU_USAGE_ADD(&hl_terminal_thread);
	}
}

void HL_Terminal_Write(uint8_t* dat)
{
	HL_System_Base_OUTPUT(dat);
}

void HL_Terminal_ReadLine(uint8_t* buffer)
{
	uint8_t i;
	for(i=0;i<HL_TERMINAL_BUFFER_SIZE;i++)
	{
		if(HL_System_Terminal_INPUT_BUFFER[i]=='\n')
		{
			//如果这里没有数据输入的话这里将一直卡住
			//因为i最大为255，如果继续++就变成0了
			break;
		}
	}
	i++;
	memcpy(buffer,HL_System_Terminal_INPUT_BUFFER,i-1);
	HL_System_Terminal_INPUT_PTR=0;
	//处理缓存区
	HL_Lib_ARRAY_LEFTMOVE(HL_System_Terminal_INPUT_BUFFER,HL_System_Terminal_INPUT_TEMPBUFFER,
												i);
}

