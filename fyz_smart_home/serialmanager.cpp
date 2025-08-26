#include "serialmanager.h"
#include <QComboBox>
#include <QDebug>
#include <QThread>

serialmanager::serialmanager(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this);
    g_scanTimer = new QTimer(this);

    // 串口错误信号绑定
    connect(serial, &QSerialPort::errorOccurred, this, &serialmanager::handleError);

    // 串口可读信号绑定
    connect(serial, &QSerialPort::readyRead, this, &serialmanager::readSerialData);

    // 延迟调用，保证 MainWindow 已经初始化完成后再扫描端口
    QTimer::singleShot(0, this, &serialmanager::scanPorts);

    // 默认定时扫描可用串口（关闭，需要时手动开启）
//    g_scanTimer->start(1000);  // 每 1000ms 扫描一次
}

serialmanager::~serialmanager()
{
    closeSerial();
}

/**
 * @brief 打开串口
 * @param portName 串口名 (如 "COM3" 或 "/dev/ttyUSB0")
 * @param baudRate 波特率
 * @return 是否成功
 */
bool serialmanager::openSerial(const QString &portName, int baudRate)
{
    if (serial->isOpen()) serial->close();

    // 基本串口参数配置
    serial->setPortName(portName);
    serial->setBaudRate(baudRate);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        qDebug() << "openSerial success!";
        g_scanTimer->stop();  // 成功打开后停止扫描
        emit serialOpened();
        return true;
    } else {
        qDebug() << "openSerial failed!";
        emit errorOccurred("串口打开失败: " + serial->errorString());
        return false;
    }
}

/**
 * @brief 关闭串口
 */
void serialmanager::closeSerial()
{
    if (serial->isOpen()) {
        serial->close();
        g_scanTimer->start();  // 重新启动端口扫描
        emit serialClosed();
    }
}

/**
 * @brief 判断串口是否已打开
 */
bool serialmanager::isOpen() const
{
    return serial->isOpen();
}

/**
 * @brief 发送数据
 * @param data 待发送数据
 */
void serialmanager::sendData(const QByteArray &data)
{
    bool isHex = false;

    if (serial->isOpen())
    {
        // 1️⃣ 写入串口
        serial->write(data);

        // 2️⃣ 判断当前发送模式：文本模式 or HEX 模式
        // parent() 返回 MainWindow 指针
        if (parent())
        {
            // 从 MainWindow 找到发送模式下拉框
            QComboBox *modeCombo = parent()->findChild<QComboBox*>("comboBox_revmode");

            if (modeCombo && modeCombo->currentText() == "HEX模式") {
                isHex = true;
            }
        }

        // 3️⃣ 发信号给 MainWindow，让界面显示发送的数据
        emit dataToSendToMainWindow(data, isHex);
    }
    else
    {
        emit errorOccurred("串口未打开，无法发送数据");
    }
}

/**
 * @brief 设置扫描或读取间隔
 * @param ms 毫秒
 */
void serialmanager::setReadInterval(int ms)
{
    g_scanTimer->setInterval(ms);
}

/**
 * @brief 串口数据读取槽函数
 *        当串口有数据时被触发
 */
void serialmanager::readSerialData()
{
    if (!serial->isOpen()) return;

    QByteArray data = serial->readAll();
    if (!data.isEmpty()) {
        emit dataReceived(data);
    }
}

/**
 * @brief 错误处理
 * @param error 串口错误类型
 */
void serialmanager::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError) return;
    emit errorOccurred(serial->errorString());
}

/**
 * @brief 获取系统当前可用的串口列表
 * @return 串口名列表
 */
QStringList serialmanager::availablePorts() const
{
    QStringList ports;
    const auto infos = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &info : infos) {
        ports << info.portName();
        // 可打印详细信息用于调试
        // qDebug() << "Port:" << info.portName()
        //          << "Desc:" << info.description()
        //          << "Manu:" << info.manufacturer();
    }

    if (infos.isEmpty()) {
        qDebug() << "No serial ports found!";
    }

    return ports;
}

/**
 * @brief 主动扫描串口并发出信号，通知 UI 更新
 */
void serialmanager::scanPorts()
{
    QStringList ports = availablePorts();
    emit portListUpdated(ports);
}
