#ifndef HL_FILESYS
#define HL_FILESYS
#include "helix.h"

#ifdef HL_FILESYSTEM_ENABLE

void HL_FS_GetFiles(void);
void HL_FS_ShowFilesAsTXT(uint8_t* filepath);
void HL_FS_WriteFile_CTRCMD(void); //接管CMD，对文件读写操作

#endif

#endif
