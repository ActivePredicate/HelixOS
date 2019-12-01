//调度器
#include "scheduler.h"

uint32_t HL_LinkLIST[HL_LinkLIST_SIZE];
uint32_t HL_LinkLIST_LENG=0;//链表长度
uint32_t HL_LinkLIST_PTR=0;//当前执行的任务

HL_Thread* HL_currentThread;
HL_Thread* HL_nextThread;

uint8_t HL_Scheduled=0;

void HL_LinkLIST_Insert(uint32_t Thread_ADDR)
{
	if(HL_LinkLIST_LENG==HL_LinkLIST_SIZE-1)
	{
		//error
		return;
	}
	if(HL_LinkLIST_LENG==0)
	{
		HL_LinkLIST[HL_LinkLIST_LENG]=Thread_ADDR;
		HL_LinkLIST_LENG++;
		return;
	}
	
	HL_LinkLIST[HL_LinkLIST_LENG++]=Thread_ADDR;
	
	HL_LinkLIST_SORT();
}

void HL_LinkLIST_Remove(uint32_t Thread_ADDR)
{
	uint8_t i;
	for(i=0;i<HL_LinkLIST_LENG;i++)
	{
		if(HL_LinkLIST[i]==Thread_ADDR)
		{
			HL_LinkLIST[i]=0;
			HL_LinkLIST_LENG--;
			HL_LinkLIST_SORT();
			return;
		}
	}
	HL_LinkLIST_SORT();
}

HL_Thread* HL_LinkLIST_ACCESS(uint32_t addr)
{
	HL_Thread* thr=(HL_Thread*)addr;
	return thr;
}

HL_Thread* HL_LinkLIST_ACCESS_BYPID(uint8_t PID)
{
	HL_Thread* ht=NULL;
	for(uint8_t i=0;i<HL_LinkLIST_LENG;i++)
	{
		ht=HL_LinkLIST_ACCESS(HL_LinkLIST[i]);
		if(ht->PID==PID) return ht;
	}
	return NULL;
}

void HL_LinkLIST_SWAP(uint32_t ptr1,uint32_t ptr2)
{
	uint32_t temp=HL_LinkLIST[ptr1];
	HL_LinkLIST[ptr1]=HL_LinkLIST[ptr2];
	HL_LinkLIST[ptr2]=temp;
}

void HL_LinkLIST_SORT(void)
{
	uint8_t i,j;
	HL_Thread* temp1;
	HL_Thread* temp2;
	
	for(i=0;i<HL_LinkLIST_LENG;i++)
	{
		for(j=i+1;j<HL_LinkLIST_LENG;j++)
		{
			temp1=HL_LinkLIST_ACCESS(HL_LinkLIST[i]);
			temp2=HL_LinkLIST_ACCESS(HL_LinkLIST[j]);
			if(temp2->priority<temp1->priority)
			HL_LinkLIST_SWAP(i,j);
		}
	}
}


void HL_LinkLIST_Refresh(void)
{
	HL_currentThread=HL_LinkLIST_ACCESS(HL_LinkLIST[HL_LinkLIST_PTR]);
	if(HL_LinkLIST_PTR==HL_LinkLIST_LENG-1) //最后一个任务为空闲任务，所以尾任务为倒数第二个任务
		HL_LinkLIST_PTR=0;
	else 
		HL_LinkLIST_PTR++;
	HL_nextThread=HL_LinkLIST_ACCESS(HL_LinkLIST[HL_LinkLIST_PTR]);
}

void HL_LinkLIST_Schedule(void)
{
	HL_LinkLIST_Refresh();
	
	HL_nextThread->TickSlice++;
	
	if(!HL_Scheduled)
	{
		HL_LinkLIST_Refresh();
		HL_Scheduled=1;
	}
	if(HL_LinkLIST_LENG>1&&HL_SYS_INITED)
		HL_PendSV_SET();
}
