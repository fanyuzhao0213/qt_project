#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

/**
 * @brief The serialmanager class
 * 用于管理串口操作：打开/关闭串口、发送/接收数据
 * 支持扫描可用串口，并通过信号通知 UI 更新
 */
class serialmanager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父对象，默认 nullptr
     */
    explicit serialmanager(QObject *parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~serialmanager();

    // ================= 串口操作接口 =================
    /**
     * @brief 打开指定串口
     * @param portName 串口名，如 COM1
     * @param baudRate 波特率，如 115200
     * @return 成功返回 true，失败返回 false
     */
    bool openSerial(const QString &portName, int baudRate);

    /**
     * @brief 关闭串口
     */
    void closeSerial();

    /**
     * @brief 判断串口是否已经打开
     * @return true 表示已打开
     */
    bool isOpen() const;

    /**
     * @brief 向串口发送数据
     * @param data 要发送的数据
     */
    void sendData(const QByteArray &data);

    /**
     * @brief 设置定时读取串口数据的间隔（毫秒）
     * @param ms 时间间隔
     */
    void setReadInterval(int ms);

    /**
     * @brief 获取当前可用串口列表
     * @return 串口名称列表
     */
    QStringList availablePorts() const;

public slots:
    /**
     * @brief 主动扫描串口并发送 portListUpdated 信号
     */
    void scanPorts();

signals:
    // ================= 信号 =================
    void dataReceived(const QByteArray &data);    // 接收到串口数据
    void errorOccurred(const QString &errorMsg);  // 串口错误信息
    void serialOpened();                          // 串口成功打开
    void serialClosed();                          // 串口关闭
    void portListUpdated(const QStringList &ports); // 扫描到的串口列表

    // 发送给 MainWindow，用于在界面显示发送的数据
    // 参数：data - 要显示的数据
    //        isHex - 是否以 HEX 模式显示
    void dataToSendToMainWindow(const QByteArray &data, bool isHex);

private slots:
    /**
     * @brief 内部槽函数：读取串口数据
     */
    void readSerialData();

    /**
     * @brief 内部槽函数：处理串口错误
     */
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort *serial = nullptr;  // 串口对象指针
    QTimer *g_scanTimer;            // 添加定时扫描串口的定时器
};

#endif // SERIALMANAGER_H
