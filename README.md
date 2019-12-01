# HelixOS
The ARM-based Embedded Extendable Operation System (NOT REAL TIME)

Now it is only gets a first-step development
I will extend the OS step by step

Platforms that the OS supports:
-ARM CM3
---STM32F103ZE
---STM32F103Cx
-ARM CM4
---STM32F429Ix
-ARM CM7
---STM32H750Vx

Functions that the OS supports:
Multi-Thread
Memory Manager
Extend RAM
Inside RTC (only for STM32 Series)
Extended KERNEL-BINDED TERMINAL
will support:filesystem and more

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
