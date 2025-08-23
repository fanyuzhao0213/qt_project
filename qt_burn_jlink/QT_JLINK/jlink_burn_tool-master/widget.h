#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLibrary>
#include <QDebug>
#include <QLibrary>
#include <QDebug>
#include <QUrl>
#include <QSettings>
#include <QMessageBox>
#include <QList>
#include <QCloseEvent>
#include <QDateTime>
#include <QFileDialog>
#include <QFile>
#include <QTimer>

#include "jlinkarm.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void delay_ms(unsigned int msec);
    void load_library_function(void);
    unsigned int JLINKARM_GetDLLVersion(void);
    bool JLINKARM_Open(void);       // 定义导出函数类型
    void JLINKARM_Close(void);
    bool JLINKARM_ExecCommand(char* cmd, int a, int b);
    DWORD JLINKARM_TIF_Select(int type);
    void JLINKARM_SetSpeed(int speed);
    bool JLINKARM_Connect(void);
    bool JLINKARM_IsConnected(void);
    DWORD JLINKARM_GetSN(void);
    DWORD JLINKARM_GetId(void);
    DWORD JLINKARM_GetSpeed(void);
    void JLINKARM_Reset(void);
    void JLINKARM_Halt(void);
    void JLINKARM_Go(void);
    bool JLINKARM_IsOpen(void);
    int JLINKARM_ReadMem(unsigned int addr, int len, void *buf);
    int JLINKARM_WriteMem(unsigned int addr, int len, void *buf);
    int JLINKARM_EraseChip(void);

    void print_log(QString log_str);
    void load_sys_params();
    void set_sys_params();
    bool is_file_exist(QString fullFileName);
    void closeEvent(QCloseEvent *event);
    void save_oem_license();
    void load_oem_license();
    bool connect_device();
    QString get_cpu_id();
    void disconnect_device();
public slots:
    void on_timer_burn_timeout();

private slots:

    void on_pushButton_choose_file_clicked();

    void on_pushButton_cpuid_clicked();

    void on_pushButton_erase_flash_clicked();

    void on_pushButton_burn_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::Widget *ui;
    QLibrary *jlink_lib;
    QString target_bin_path;
    QString start_addr;
    unsigned int write_start_addr;
    QString cpu_id_str;
    QTimer *timer_burn;

    JLINKARM_GetDLLVersion_Func_Ptr JLINKARM_GetDLLVersion_Entry = NULL;   //获取DLL版本
    JLINKARM_Open_Func_Ptr JLINKARM_Open_Entry = NULL;               //打开设备
    JLINKARM_IsOpen_Func_Ptr JLINKARM_IsOpen_Entry = NULL;           //是否已经打开
    JLINKARM_Close_Func_Ptr JLINKARM_Close_Entry = NULL;             //关闭设备
    JLINKARM_TIF_Select_Func_Ptr JLINKARM_TIF_Select_Entry = NULL;   //选择设备
    JLINKARM_SetSpeed_Func_Ptr JLINKARM_SetSpeed_Entry = NULL;       //设置JLINK接口速度 0为自动调整
    JLINKARM_Reset_Func_Ptr JLINKARM_Reset_Entry = NULL;             //复位系统
    JLINKARM_Halt_Func_Ptr JLINKARM_Halt_Entry = NULL;               //中断程序执行，进入停止状态
    JLINKARM_Go_Func_Ptr JLINKARM_Go_Entry = NULL;                   //执行程序
    JLINKARM_WriteMem_Func_Ptr JLINKARM_WriteMem_Entry = NULL;       //写内存
    JLINKARM_ReadMem_Func_Ptr JLINKARM_ReadMem_Entry = NULL;         //读内存

    JLINKARM_WriteU8_Func_Ptr JLINKARM_WriteU8_Entry = NULL;
    JLINKARM_WriteU16_Func_Ptr JLINKARM_WriteU16_Entry = NULL;
    JLINKARM_WriteU32_Func_Ptr JLINKARM_WriteU32_Entry = NULL;
    JLINK_EraseChip_Func_Ptr JLINK_EraseChip_Entry = NULL;

    JLINKARM_DownloadFile_Func_Ptr JLINKARM_DownloadFile_Entry = NULL;
    JLINKARM_BeginDownload_Func_Ptr JLINKARM_BeginDownload_Entry = NULL;
    JLINKARM_EndDownload_Func_Ptr JLINKARM_EndDownload_Entry = NULL;
    JLINKARM_ExecCommand_Func_Ptr JLINKARM_ExecCommand_Entry = NULL;
    JLINKARM_ReadReg_Func_Ptr JLINKARM_ReadReg_Entry = NULL;
    JLINKARM_WriteReg_Func_Ptr JLINKARM_WriteReg_Entry = NULL;
    JLINKARM_SetLogFile_Func_Ptr JLINKARM_SetLogFile_Entry = NULL;
    JLINKARM_GetHardwareVersion_Func_Ptr JLINKARM_GetHardwareVersion_Entry = NULL;
    JLINKARM_GetFirmwareString_Func_Ptr JLINKARM_GetFirmwareString_Entry = NULL;
    JLINKARM_GetSN_Func_Ptr JLINKARM_GetSN_Entry = NULL;
    JLINKARM_GetId_Func_Ptr JLINKARM_GetId_Entry = NULL;
    JLINKARM_GetSpeed_Func_Ptr JLINKARM_GetSpeed_Entry = NULL;
    JLINKARM_Connect_Func_Ptr JLINKARM_Connect_Entry = NULL;
    JLINKARM_IsConnected_Func_Ptr JLINKARM_IsConnected_Entry = NULL;

    unsigned int total_file_size;
    QByteArray burn_bin_data;
    unsigned int burnning_flag;
};

#endif // WIDGET_H
