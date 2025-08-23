#ifndef JLINKARM_H
#define JLINKARM_H

#include "windows.h"

//JLINK TIF
#define JLINKARM_TIF_JTAG	0
#define JLINKARM_TIF_SWD	1
#define JLINKARM_TIF_DBM3	2
#define JLINKARM_TIF_FINE	3
#define JLINKARM_TIF_2wire_JTAG_PIC32	4

//RESET TYPE
#define JLINKARM_RESET_TYPE_NORMAL 0
#define JLINKARM_RESET_TYPE_CORE   1
#define JLINKARM_RESET_TYPE_PIN    2

//REGISTER INDEX
/*
  0 - 15     R0 - R15(SP=R13, PC=R15)
 16          XPSR
 17          MSP
 18          PSP
 19          RAZ
 20          CFBP
 21          APSR
 22          EPSR
 23          IPSR
 24          PRIMASK
 25          BASEPRI
 26          FAULTMASK
 27          CONTROL
 28          BASEPRI_MAX
 29          IAPSR
 30          EAPSR
 31          IEPSR
 */
typedef BOOL (*JLINKARM_Open_Func_Ptr)(void);       // 定义导出函数类型
typedef void (*JLINKARM_Close_Func_Ptr)(void);
typedef DWORD (*JLINKARM_TIF_Select_Func_Ptr)(int);
typedef void (*JLINKARM_SetSpeed_Func_Ptr)(int);
typedef void (*JLINKARM_Reset_Func_Ptr)(void);
typedef void  (*JLINKARM_Go_Func_Ptr)(void);
typedef BOOL (*JLINKARM_IsOpen_Func_Ptr)(void);

typedef void  (*JLINKARM_SetLogFile_Func_Ptr)(char *file);
typedef DWORD (*JLINKARM_GetDLLVersion_Func_Ptr)(void);
typedef DWORD (*JLINKARM_GetHardwareVersion_Func_Ptr)(void);
typedef DWORD (*JLINKARM_GetFirmwareString_Func_Ptr)(char *buff, int count);
typedef DWORD (*JLINKARM_GetSN_Func_Ptr)(void);

typedef BOOL  (*JLINKARM_ExecCommand_Func_Ptr)(char* cmd, int a, int b);
typedef DWORD (*JLINKARM_TIF_Select_Func_Ptr)(int type);
typedef void  (*JLINKARM_SetSpeed_Func_Ptr)(int speed);
typedef DWORD (*JLINKARM_GetSpeed_Func_Ptr)(void);
typedef DWORD (*JLINKARM_GetId_Func_Ptr)(void);
typedef DWORD (*JLINKARM_GetDeviceFamily_Func_Ptr)(void);

typedef BOOL  (*JLINKARM_Open_Func_Ptr)(void);
typedef void  (*JLINKARM_Close_Func_Ptr)(void);
typedef BOOL  (*JLINKARM_IsOpen_Func_Ptr)(void);
typedef BOOL  (*JLINKARM_Connect_Func_Ptr)(void);
typedef BOOL  (*JLINKARM_IsConnected_Func_Ptr)(void);
typedef int   (*JLINKARM_Halt_Func_Ptr)(void);
typedef BOOL  (*JLINKARM_IsHalted_Func_Ptr)(void);
typedef void  (*JLINKARM_SetResetType_Func_Ptr)(int type);
typedef void  (*JLINKARM_Reset_Func_Ptr)(void);
typedef void  (*JLINKARM_Go_Func_Ptr)(void);
typedef void  (*JLINKARM_GoIntDis_Func_Ptr)(void);
typedef DWORD (*JLINKARM_ReadReg_Func_Ptr)(int index);
typedef int   (*JLINKARM_WriteReg_Func_Ptr)(int index, DWORD data);

typedef int   (*JLINKARM_ReadMem_Func_Ptr)(DWORD addr, int len, void *buf);
typedef int   (*JLINKARM_WriteMem_Func_Ptr)(DWORD addr, int len, void *buf);
typedef int   (*JLINKARM_WriteU8_Func_Ptr)(DWORD addr, BYTE data);
typedef int   (*JLINKARM_WriteU16_Func_Ptr)(DWORD addr, WORD data);
typedef int   (*JLINKARM_WriteU32_Func_Ptr)(DWORD addr, DWORD data);

typedef int   (*JLINK_EraseChip_Func_Ptr)(void);
typedef int   (*JLINKARM_DownloadFile_Func_Ptr)(LPCSTR file, DWORD addr);
typedef void  (*JLINKARM_BeginDownload_Func_Ptr)(int index);
typedef void  (*JLINKARM_EndDownload_Func_Ptr)(void);
#endif // JLINKARM_H
