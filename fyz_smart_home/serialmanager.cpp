#include "serialmanager.h"
#include <QDebug>
#include <QThread>


serialmanager::serialmanager(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this);
    g_scanTimer = new QTimer(this);


    connect(g_scanTimer, &QTimer::timeout, this, &serialmanager::scanPorts);
    connect(serial, &QSerialPort::errorOccurred, this, &serialmanager::handleError);

    g_scanTimer->start(500);  // 默认500ms扫描一次可用串口
}
serialmanager::~serialmanager()
{
    closeSerial();
}

// 打开串口
bool serialmanager::openSerial(const QString &portName, int baudRate)
{
    if (serial->isOpen()) serial->close();

    serial->setPortName(portName);
    serial->setBaudRate(baudRate);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        qDebug() << "openSerial success!";
        emit serialOpened();
        return true;
    } else {
        qDebug() << "openSerial failed!";
        emit errorOccurred("串口打开失败: " + serial->errorString());
        return false;
    }
}

// 关闭串口
void serialmanager::closeSerial()
{
    if (serial->isOpen()) {
        serial->close();
        g_scanTimer->stop();
        emit serialClosed();
    }
}

bool serialmanager::isOpen() const
{
    return serial->isOpen();
}

// 发送数据
void serialmanager::sendData(const QByteArray &data)
{
    if (serial->isOpen())
        serial->write(data);
    else
        emit errorOccurred("串口未打开，无法发送数据");
}

// 设置读取间隔
void serialmanager::setReadInterval(int ms)
{
    g_scanTimer->setInterval(ms);
}


// 定时读取串口数据
void serialmanager::readSerialData()
{
    if (!serial->isOpen()) return;

    QByteArray data = serial->readAll();
    if (!data.isEmpty()) {
        emit dataReceived(data);
    }
}

// 错误处理
void serialmanager::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError) return;
    emit errorOccurred(serial->errorString());
}


// 扫描可用串口
QStringList serialmanager::availablePorts() const
{
    QStringList ports;
    const auto infos = QSerialPortInfo::availablePorts();
//    qDebug() << "Scanning serial ports... found" << infos.size() << "ports";

    for (const QSerialPortInfo &info : infos) {
        ports << info.portName();
//        qDebug() << "Port found:" << info.portName()
//                 << "Description:" << info.description()
//                 << "Manufacturer:" << info.manufacturer();
    }

    if (infos.isEmpty()) {
        qDebug() << "No serial ports found!";
    }

    return ports;
}

// 主动扫描串口，并发送信号更新界面
void serialmanager::scanPorts()
{
    QStringList ports = availablePorts();
    emit portListUpdated(ports);
}

