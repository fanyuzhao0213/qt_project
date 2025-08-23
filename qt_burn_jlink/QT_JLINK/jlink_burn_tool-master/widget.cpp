#include "widget.h"
#include "ui_widget.h"

#define BURN_DELAY  5
#define BURN_STEP_SIZE 1024
#define LICENSE_START_ADDR 0xFC00
#define CPUID_CHECK_TIMES 5
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("J-link烧录工具V1.0"));
    timer_burn = new QTimer(this);
    load_library_function();
    JLINKARM_GetSN();
    JLINKARM_GetId();
    JLINKARM_GetSpeed();
    load_sys_params();
    connect(timer_burn, SIGNAL(timeout()),this, SLOT(on_timer_burn_timeout()));
    burnning_flag = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::delay_ms(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Widget::load_library_function()
{
    jlink_lib = new QLibrary("E:/QT_JLINK/jlink_burn_tool-master/JLink_x64.dll");
    if(jlink_lib->load()){
        qDebug()<<"加载JLink_x64.dll成功, 开始解析函数";
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
        qDebug()<<"解析函数完成";
    }
    else
    {
        qDebug()<<"加载JLink_x64.dll失败!!";
    }
}

unsigned int Widget::JLINKARM_GetDLLVersion()
{
    if(JLINKARM_GetDLLVersion_Entry)
    {
        return JLINKARM_GetDLLVersion_Entry();
    }
    qDebug()<<"JLINKARM_GetDLLVersion_Entry is NULL!";
    return FALSE;
}

bool Widget::JLINKARM_Open()
{
    if(JLINKARM_Open_Entry)
    {
       return JLINKARM_Open_Entry();
    }
    qDebug()<<"JLINKARM_Open_Entry is NULL!";
    return FALSE;
}

void Widget::JLINKARM_Close()
{
    if(JLINKARM_Close_Entry)
    {
       return JLINKARM_Close_Entry();
    }
    qDebug()<<"JLINKARM_Close_Entry is NULL!";
    return;
}

bool Widget::JLINKARM_ExecCommand(char *cmd, int a, int b)
{
    if(JLINKARM_ExecCommand_Entry)
    {
       return JLINKARM_ExecCommand_Entry(cmd, a, b);
    }
    qDebug()<<"JLINKARM_ExecCommand_Entry is NULL!";
    return FALSE;
}

DWORD Widget::JLINKARM_TIF_Select(int type)
{
    if(JLINKARM_TIF_Select_Entry)
    {
       return JLINKARM_TIF_Select_Entry(type);
    }
    qDebug()<<"JLINKARM_TIF_Select_Entry is NULL!";
    return FALSE;
}

void Widget::JLINKARM_SetSpeed(int speed)
{
    if(JLINKARM_SetSpeed_Entry)
    {
       return JLINKARM_SetSpeed_Entry(speed);
    }
    qDebug()<<"JLINKARM_SetSpeed_Entry is NULL!";
    return;
}

bool Widget::JLINKARM_Connect()
{
    if(JLINKARM_Connect_Entry)
    {
       return JLINKARM_Connect_Entry();
    }
    qDebug()<<"JLINKARM_Connect_Entry is NULL!";
    return FALSE;
}

bool Widget::JLINKARM_IsConnected()
{
    if(JLINKARM_IsConnected_Entry)
    {
       return JLINKARM_IsConnected_Entry();
    }
    qDebug()<<"JLINKARM_IsConnected_Entry is NULL!";
    return FALSE;
}

DWORD Widget::JLINKARM_GetSN()
{
    if(JLINKARM_GetSN_Entry)
    {
       return JLINKARM_GetSN_Entry();
    }
    qDebug()<<"JLINKARM_GetSN_Entry is NULL!";
    return 0;
}

DWORD Widget::JLINKARM_GetId()
{
    if(JLINKARM_GetId_Entry)
    {
       return JLINKARM_GetId_Entry();
    }
    qDebug()<<"JLINKARM_GetId_Entry is NULL!";
    return 0;
}

DWORD Widget::JLINKARM_GetSpeed()
{
    if(JLINKARM_GetSpeed_Entry)
    {
       return JLINKARM_GetSpeed_Entry();
    }
    qDebug()<<"JLINKARM_GetSpeed_Entry is NULL!";
    return 0;
}

void Widget::JLINKARM_Reset()
{
    if(JLINKARM_Reset_Entry)
    {
       return JLINKARM_Reset_Entry();
    }
    qDebug()<<"JLINKARM_Reset_Entry is NULL!";
    return;
}

void Widget::JLINKARM_Halt()
{

}

void Widget::JLINKARM_Go()
{

}

bool Widget::JLINKARM_IsOpen()
{
    if(JLINKARM_IsOpen_Entry)
    {
       return JLINKARM_IsOpen_Entry();
    }
    qDebug()<<"JLINKARM_IsOpen_Entry is NULL!";
    return FALSE;
}

int Widget::JLINKARM_ReadMem(unsigned int addr, int len, void *buf)
{
    if(JLINKARM_ReadMem_Entry)
    {
       return JLINKARM_ReadMem_Entry(addr, len, buf);
    }
    qDebug()<<"JLINKARM_ReadMem_Entry is NULL!";
    return 0;
}

int Widget::JLINKARM_WriteMem(unsigned int addr, int len, void *buf)
{
    if(JLINKARM_WriteMem_Entry)
    {
       return JLINKARM_WriteMem_Entry(addr, len, buf);
    }
    qDebug()<<"JLINKARM_WriteMem is NULL!";
    return 0;
}

int Widget::JLINKARM_EraseChip()
{
    if(JLINK_EraseChip_Entry)
    {
       return JLINK_EraseChip_Entry();
    }
    qDebug()<<"JLINK_EraseChip_Entry is NULL!";
    return 0;
}

void Widget::print_log(QString log_str)
{
    QString msg = QDateTime::currentDateTime().toString("[hh:mm:ss.zzz]-> ");
    msg += log_str;
    ui->textBrowser->append(msg);
}

void Widget::load_sys_params()
{
    QSettings settings("params.ini", QSettings::IniFormat);
    target_bin_path = settings.value("target_bin_path").toString();
    start_addr = settings.value("start_addr").toString();
    qDebug()<<"target_bin_path:"<<target_bin_path;
    qDebug()<<"start_addr:"<<start_addr;

    bool ok = false;
    write_start_addr = start_addr.toInt(&ok, 16);
    if(!ok)
    {
        start_addr = "0x8000000";
        write_start_addr = 0x8000000;
    }

    ui->lineEdit_start_addr->setText(start_addr);
    ui->lineEdit->setText(target_bin_path);
}

void Widget::set_sys_params()
{
    QSettings settings("params.ini", QSettings::IniFormat);
    qDebug()<<"save target_bin_path:"<<ui->lineEdit->text();
    settings.setValue("target_bin_path", ui->lineEdit->text());
    qDebug()<<"save start_addr:"<<ui->lineEdit_start_addr->text();
    settings.setValue("start_addr", ui->lineEdit_start_addr->text());
}

bool Widget::is_file_exist(QString fullFileName)
{
    QFileInfo fileInfo(fullFileName);
    if(fileInfo.isFile())
    {
        qDebug()<<"文件存在:"<<fullFileName;
        return true;
    }
    qDebug()<<"文件不存在:"<<fullFileName;
    return false;
}

void Widget::closeEvent(QCloseEvent *event)
{
    set_sys_params();
}

bool Widget::connect_device()
{
    if(JLINKARM_IsOpen())
    {
        qDebug()<<"JLINKARM was Opened!";
        return true;
    }
    qDebug()<<"Try Open JLINKARM...";
    JLINKARM_Open();
    if(JLINKARM_IsOpen())
    {
        qDebug()<<"JLINKARM Open success!";
        JLINKARM_ExecCommand("device = STM32F429IG", 0, 0);
        JLINKARM_TIF_Select(JLINKARM_TIF_SWD);
        JLINKARM_SetSpeed(4000);
        JLINKARM_Connect();
        if(JLINKARM_IsConnected()){
            return true;
        }else
        {
            print_log("连接设备失败! 请检查设备连接..");
        }
    }
    else {
        qDebug()<<"JLINKARM Open fail!";
        print_log("连接设备失败! 请检查烧录器连接..");
    }
    return false;
}

QString Widget::get_cpu_id()
{
    unsigned char cpuid[12]={0};
    char cpu_id_tmp[128]={0};
    JLINKARM_ReadMem(0x1FF80050, 12, cpuid);
    JLINKARM_ReadMem(0x1FF80050, 12, cpuid); //多读一次解决读取错误的问题
    sprintf(cpu_id_tmp, "%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X",
            cpuid[3],cpuid[2],cpuid[1],cpuid[0],
            cpuid[7],cpuid[6],cpuid[5],cpuid[4],
            cpuid[11],cpuid[10],cpuid[9],cpuid[8]);
    for(int i=0; i<sizeof(cpuid); i++)
        qDebug("cpuid[%d]=%02X", i, cpuid[i]);
    qDebug("cpuid=%s",cpu_id_tmp);
    return QString(cpu_id_tmp);
}

void Widget::disconnect_device()
{
    qDebug()<<"Try Close JLINKARM...";
    JLINKARM_Close();
    if(!JLINKARM_IsOpen())
    {
        qDebug()<<"JLINKARM Close success!";
    }
    else {
        qDebug()<<"JLINKARM Close fail!";
    }
}

void Widget::on_timer_burn_timeout()
{
    if(timer_burn)
    {
        timer_burn->stop();
        //烧写固件
        if(burn_bin_data.isEmpty())  //烧录完成
        {
            ui->progressBar->setValue(100);
            burnning_flag = 0;
            disconnect_device();
            print_log("烧录完成！");
            return;
        }
        else  //烧录的数据非空
        {
            if(burn_bin_data.size() > BURN_STEP_SIZE)   //大小超过1K
            {
                int ret = JLINKARM_WriteMem(write_start_addr, BURN_STEP_SIZE, burn_bin_data.data());
//                qDebug()<<"JLINKARM_WriteMem ret = "<<ret;
                write_start_addr += BURN_STEP_SIZE; //烧写地址递增
                burn_bin_data.remove(0, BURN_STEP_SIZE);
            }
            else    //大小不到1K
            {
                int ret = JLINKARM_WriteMem(write_start_addr, burn_bin_data.size(), burn_bin_data.data());
//                qDebug()<<"JLINKARM_WriteMem ret = "<<ret;
                write_start_addr += burn_bin_data.size(); //烧写地址递增
                burn_bin_data.clear();
            }

            unsigned int percent = 1.0*(total_file_size - burn_bin_data.size())/total_file_size*100;
//            qDebug()<<"Burn progress: "<<percent;
            ui->progressBar->setValue(percent);
            timer_burn->start(BURN_DELAY);//5m后继续烧录
        }
    }
}


void Widget::on_pushButton_choose_file_clicked()
{
    QFileInfo fileinfo = QFileInfo(target_bin_path);
    qDebug()<<"bootloader  absolutePath:"<<fileinfo.absolutePath();
    QString tmp = QFileDialog::getOpenFileName(this,"选择bootloader.bin文件", fileinfo.absolutePath(), "启动镜像(*.bin)");
    if(tmp.isEmpty())
        return;
    target_bin_path = tmp;
    if(target_bin_path.startsWith("/Ubuntu")) //如果是根目录
    {
        target_bin_path = "\\\\wsl$" + target_bin_path.replace("/","\\");
    } else {
        target_bin_path = target_bin_path.replace("/","\\");
    }
    ui->lineEdit->setText(target_bin_path);
    set_sys_params();
}

void Widget::on_pushButton_cpuid_clicked()
{
    static int cpuid_reading_flag = 0;
    if(cpuid_reading_flag)
    {
        print_log(QString("获取CPUID中，请稍后..."));
        return;
    }
    if( connect_device()){
//        qDebug("JLink Info:");
//        qDebug("SN = %08u", JLINKARM_GetSN());
//        qDebug("ID = %08X", JLINKARM_GetId());
//        qDebug("VER = %u", JLINKARM_GetDLLVersion());
//        qDebug("Speed = %u", JLINKARM_GetSpeed());
        print_log(QString("获取CPUID中，请稍后..."));
        cpuid_reading_flag = 1;
        delay_ms(100);
        cpu_id_str = get_cpu_id();
        print_log(QString("获取CPUID成功: ")+cpu_id_str);
        disconnect_device();
        cpuid_reading_flag = 0;
    }
}

void Widget::on_pushButton_erase_flash_clicked()
{
    if( connect_device() ){ //连接设备
        JLINKARM_EraseChip();

        disconnect_device();
    }
}

void Widget::on_pushButton_burn_clicked()
{
    if(burnning_flag)
    {
        print_log("正在加速烧录中，请稍后...");
        return;
    }
    burn_bin_data.clear();
    total_file_size = 0;
    if(target_bin_path.isEmpty())
    {
        print_log("请选择要烧录的固件！");
        return;
    }

    if( connect_device() ){ //连接设备

        cpu_id_str = get_cpu_id();// 获取CPUID

        bool ok = false;        //检查起始地址信息
        write_start_addr = ui->lineEdit_start_addr->text().trimmed().toInt(&ok, 16);
        if(!ok)
        {
            print_log("烧录起始地址格式有误！");
            disconnect_device();
            return;
        }

        QFile burn_file;
        burn_file.setFileName(target_bin_path);
        burn_file.open(QIODevice::ReadOnly); //打开文件
        if(burn_file.isOpen())
        {
            burn_bin_data = burn_file.readAll();    //将要烧录的数据读取到内存中
            burn_file.close();  //关闭文件
            if(burn_bin_data.size() > 1024*1024)
            {
                print_log("文件大小不允许超过1MB!");
                burn_bin_data.clear();
                disconnect_device();
                return;
            }

            print_log("开始烧录固件, 请稍后...");
            burnning_flag = 1;  //正在烧录
            timer_burn->start(BURN_DELAY);
        }
        else
        {
            print_log("打开固件失败, 请检查文件是否存在！");
            disconnect_device();
        }
    }
}

void Widget::on_pushButton_clear_clicked()
{
    ui->textBrowser->clear();
}
