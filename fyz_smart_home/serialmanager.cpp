#include "serialmanager.h"
#include <QComboBox>
#include <QDebug>
#include <QThread>

serialmanager::serialmanager(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this);
    g_scanTimer = new QTimer(this);

    connect(serial, &QSerialPort::errorOccurred, this, &serialmanager::handleError);
    connect(serial, &QSerialPort::readyRead, this, &serialmanager::readSerialData);
    // 延迟调用，保证 MainWindow 已经初始化完成
    QTimer::singleShot(0, this, &serialmanager::scanPorts);

//    g_scanTimer->start(1000);  // 默认2000ms扫描一次可用串口
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
        g_scanTimer->stop();
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
        g_scanTimer->start();
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
    bool isHex = false;
    if (serial->isOpen())
    {
        // 1️⃣ 写入串口
        serial->write(data);

        // 2️⃣ 判断当前发送模式：文本模式还是 HEX 模式
        //parent() 返回的就是 MainWindow 对象
        if (parent())
        {
            // 通过 parent() 获取 MainWindow 下的 comboBox_sendMode
            QComboBox *modeCombo = parent()->findChild<QComboBox*>("comboBox_revmode");

            if (modeCombo && modeCombo->currentText() == "HEX模式") {
                isHex = true; // 用户选择了 HEX 模式
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

