#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDateTime>
#include <QSettings>
#include <QFileInfo>
#include <QDebug>

#define BURN_DELAY  5
#define BURN_STEP_SIZE 1024
#define LICENSE_START_ADDR 0xFC00
#define CPUID_CHECK_TIMES 5

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("aqua自动烧录工具V1.0"));

    // 初始化 J-Link 库
    jlink_lib = new QLibrary("E:/QT_JLINK/stm_jlink_burn_tool-master/JLink_x64.dll");
    timer_burn = new QTimer(this);

    // 加载 J-Link 函数
    load_library_function();

    // 加载系统参数
    load_sys_params();

    // 连接设备并读取 J-Link SN 和芯片 ID
    if (connect_device()) {
        read_jlink_sn();       // 读取 J-Link SN
        read_chip_id();        // 读取芯片 ID
        disconnect_device();   // 断开设备连接
    }

    // 连接定时器信号槽
    connect(timer_burn, SIGNAL(timeout()), this, SLOT(on_timer_burn_timeout()));

    burnning_flag = 0;  // 初始化烧录标志
}

Widget::~Widget()
{
    delete ui;
}

// 读取 J-Link SN
void Widget::read_jlink_sn()
{
    DWORD sn = JLINKARM_GetSN();
    if (sn != 0) {
        QString snStr = QString("J-Link SN: %1").arg(sn);
        print_log(snStr);  // 打印 J-Link SN
    } else {
        print_log("Failed to read J-Link SN!");
    }
}

// 读取芯片 ID
void Widget::read_chip_id()
{
    QString cpuId = get_cpu_id();
    if (!cpuId.isEmpty()) {
        QString cpuIdStr = QString("芯片 ID: %1").arg(cpuId);
        print_log(cpuIdStr);  // 打印芯片 ID
    } else {
        print_log("Failed to read chip ID!");
    }
}

// 打印日志
void Widget::print_log(QString log_str)
{
    QString msg = QDateTime::currentDateTime().toString("[hh:mm:ss.zzz]-> ");
    msg += log_str;
    ui->textBrowser->append(msg);
}

// 加载 J-Link 函数
void Widget::load_library_function()
{
    if (jlink_lib->load()) {
        qDebug() << "加载 JLinkARM.dll 成功, 开始解析函数";
        JLINKARM_Open_Entry = (JLINKARM_Open_Func_Ptr)jlink_lib->resolve("JLINKARM_Open");
        JLINKARM_IsOpen_Entry = (JLINKARM_IsOpen_Func_Ptr)jlink_lib->resolve("JLINKARM_IsOpen");
        JLINKARM_Close_Entry = (JLINKARM_Close_Func_Ptr)jlink_lib->resolve("JLINKARM_Close");
        JLINKARM_ExecCommand_Entry = (JLINKARM_ExecCommand_Func_Ptr)jlink_lib->resolve("JLINKARM_ExecCommand");
        JLINKARM_GetDLLVersion_Entry = (JLINKARM_GetDLLVersion_Func_Ptr)jlink_lib->resolve("JLINKARM_GetDLLVersion");
        JLINKARM_TIF_Select_Entry = (JLINKARM_TIF_Select_Func_Ptr)jlink_lib->resolve("JLINKARM_TIF_Select");
        JLINKARM_SetSpeed_Entry = (JLINKARM_SetSpeed_Func_Ptr)jlink_lib->resolve("JLINKARM_SetSpeed");
        JLINKARM_GetSpeed_Entry = (JLINKARM_GetSpeed_Func_Ptr)jlink_lib->resolve("JLINKARM_GetSpeed");
        JLINKARM_Connect_Entry = (JLINKARM_Connect_Func_Ptr)jlink_lib->resolve("JLINKARM_Connect");
        JLINKARM_IsConnected_Entry = (JLINKARM_IsConnected_Func_Ptr)jlink_lib->resolve("JLINKARM_IsConnected");
        JLINKARM_GetId_Entry = (JLINKARM_GetId_Func_Ptr)jlink_lib->resolve("JLINKARM_GetId");
        JLINKARM_GetSN_Entry = (JLINKARM_GetSN_Func_Ptr)jlink_lib->resolve("JLINKARM_GetSN");
        JLINKARM_Reset_Entry = (JLINKARM_Reset_Func_Ptr)jlink_lib->resolve("JLINKARM_Reset");
        JLINKARM_Halt_Entry = (JLINKARM_Halt_Func_Ptr)jlink_lib->resolve("JLINKARM_Halt");
        JLINKARM_WriteMem_Entry = (JLINKARM_WriteMem_Func_Ptr)jlink_lib->resolve("JLINKARM_WriteMem");
        JLINKARM_ReadMem_Entry = (JLINKARM_ReadMem_Func_Ptr)jlink_lib->resolve("JLINKARM_ReadMem");
        JLINK_EraseChip_Entry = (JLINK_EraseChip_Func_Ptr)jlink_lib->resolve("JLINK_EraseChip");
        qDebug() << "解析函数完成";
    } else {
        qDebug() << "加载 JLinkARM.dll 失败!!";
    }
}

// 连接设备
bool Widget::connect_device()
{
    if (JLINKARM_IsOpen()) {
        qDebug() << "JLINKARM was Opened!";
        return true;
    }

    print_log("尝试打开 JLINKARM...");
    JLINKARM_Open();

    if (JLINKARM_IsOpen()) {
        print_log("JLINKARM 打开成功");
        JLINKARM_ExecCommand("device = STM32L151CC", 0, 0);  // 设置目标设备型号
        JLINKARM_TIF_Select(JLINKARM_TIF_SWD);  // 选择 SWD 接口
        JLINKARM_SetSpeed(4000);  // 设置通信速度
        JLINKARM_Connect();  // 连接设备

        if (JLINKARM_IsConnected()) {
            return true;
        } else {
            print_log("连接设备失败! 请检查设备连接..");
        }
    } else {
        print_log("JLINKARM 打开失败! 请检查烧录器连接..");
    }

    return false;
}

// 断开设备连接
void Widget::disconnect_device()
{
    qDebug() << "尝试关闭 JLINKARM...";
    JLINKARM_Close();

    if (!JLINKARM_IsOpen()) {
        qDebug() << "JLINKARM 关闭成功!";
    } else {
        qDebug() << "JLINKARM 关闭失败!";
    }
}

// 获取芯片 ID
QString Widget::get_cpu_id()
{
    unsigned char cpuid[12] = {0};
    char cpu_id_tmp[128] = {0};
    JLINKARM_ReadMem(0x1FF80050, 12, cpuid);  // 读取芯片 ID
    JLINKARM_ReadMem(0x1FF80050, 12, cpuid);  // 多读一次解决读取错误的问题

    sprintf(cpu_id_tmp, "%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X",
            cpuid[3], cpuid[2], cpuid[1], cpuid[0],
            cpuid[7], cpuid[6], cpuid[5], cpuid[4],
            cpuid[11], cpuid[10], cpuid[9], cpuid[8]);

    for (int i = 0; i < sizeof(cpuid); i++) {
        qDebug("cpuid[%d] = %02X", i, cpuid[i]);
    }
    qDebug("cpuid = %s", cpu_id_tmp);

    return QString(cpu_id_tmp);
}
