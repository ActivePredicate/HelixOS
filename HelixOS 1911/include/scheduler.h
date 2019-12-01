#ifndef HLSCHE
#define HLSCHE
#include "helix.h"


extern uint32_t HL_LinkLIST[HL_LinkLIST_SIZE];
extern uint32_t HL_LinkLIST_LENG;//链表长度
extern uint32_t HL_LinkLIST_PTR;//当前执行的任务

extern HL_Thread* HL_currentThread;
extern HL_Thread* HL_nextThread;

void HL_LinkLIST_Insert(uint32_t Thread_ADDR);
void HL_LinkLIST_Remove(uint32_t Thread_ADDR);
HL_Thread* HL_LinkLIST_ACCESS(uint32_t addr);
HL_Thread* HL_LinkLIST_ACCESS_BYPID(uint8_t PID);
void HL_LinkLIST_SWAP(uint32_t ptr1,uint32_t ptr2);
void HL_LinkLIST_SORT(void);

void HL_LinkLIST_Refresh(void);
void HL_LinkLIST_Schedule(void);

#endif
