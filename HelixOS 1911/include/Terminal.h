#ifndef HL_TERMINAL_HEADER
#define HL_TERMINAL_HEADER
#include "helix.h"

#define HL_TERMINAL_IO_ENABLE
#define HL_TERMINAL_BUFFER_SIZE 256

extern HL_Thread hl_terminal_thread;

#ifndef HL_EXTENDED_RAM_EXIST
extern uint32_t HL_System_Terminal_Stack[HL_LARGE_STACK_SIZE];
extern uint8_t HL_System_Terminal_INPUT_BUFFER[HL_TERMINAL_BUFFER_SIZE];
extern uint8_t HL_System_Terminal_INPUT_TEMPBUFFER[HL_TERMINAL_BUFFER_SIZE];
extern uint8_t HL_System_Terminal_INPUT_DATA[64];
extern uint8_t HL_System_Terminal_INPUT_CMD[16];
#else
extern uint32_t* HL_System_Terminal_Stack; //ด๓ะก8kb
extern uint8_t* HL_System_Terminal_INPUT_BUFFER;
extern uint8_t* HL_System_Terminal_INPUT_TEMPBUFFER;
extern uint8_t* HL_System_Terminal_INPUT_DATA; //64
extern uint8_t* HL_System_Terminal_INPUT_CMD; //16
#endif

extern uint8_t HL_System_Terminal_INPUT_PTR;
extern uint8_t HL_Terminal_EnterPassword;



void HL_Terminal_Entry(void);

void HL_SYSINFO(void);

void HL_Terminal_Write(uint8_t* dat);
void HL_Terminal_Read(uint8_t* buffer);
void HL_Terminal_ReadLine(uint8_t* buffer);

#endif
