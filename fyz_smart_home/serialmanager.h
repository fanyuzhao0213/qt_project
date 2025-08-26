#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

/**
 * @brief The serialmanager class
 *
 * 串口管理类，封装了串口的常用功能：
 * - 打开/关闭串口
 * - 发送/接收数据
 * - 定时扫描可用串口
 * - 通过信号与 UI 层（如 MainWindow）交互
 *
 * 使用场景：
 * - 上位机程序，用于和嵌入式设备通信
 * - 支持 HEX / 文本模式显示
 */
class serialmanager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父对象，通常是 MainWindow
     */
    explicit serialmanager(QObject *parent = nullptr);

    /**
     * @brief 析构函数
     *        析构时会确保串口关闭
     */
    ~serialmanager();

    // ================= 串口操作接口 =================
    /**
     * @brief 打开指定串口
     * @param portName 串口名 (如 "COM3" 或 "/dev/ttyUSB0")
     * @param baudRate 波特率 (如 9600 / 115200)
     * @return 成功返回 true，失败返回 false
     */
    bool openSerial(const QString &portName, int baudRate);

    /**
     * @brief 关闭串口
     *        关闭后会重新启动端口扫描
     */
    void closeSerial();

    /**
     * @brief 判断串口是否已经打开
     * @return true 表示已打开，false 表示未打开
     */
    bool isOpen() const;

    /**
     * @brief 向串口发送数据
     * @param data 要发送的字节数组
     *
     * 会触发信号 @see dataToSendToMainWindow 用于更新 UI
     */
    void sendData(const QByteArray &data);

    /**
     * @brief 设置定时扫描串口或定时读取的间隔
     * @param ms 毫秒数
     */
    void setReadInterval(int ms);

    /**
     * @brief 获取系统当前可用串口列表
     * @return 串口名称列表
     */
    QStringList availablePorts() const;

public slots:
    /**
     * @brief 主动扫描可用串口
     *        并触发 @see portListUpdated 信号通知 UI
     */
    void scanPorts();

signals:
    // ================= 信号接口 =================

    /**
     * @brief 接收到串口数据时触发
     * @param data 收到的字节数组
     */
    void dataReceived(const QByteArray &data);

    /**
     * @brief 串口发生错误时触发
     * @param errorMsg 错误描述信息
     */
    void errorOccurred(const QString &errorMsg);

    /**
     * @brief 串口成功打开时触发
     */
    void serialOpened();

    /**
     * @brief 串口关闭时触发
     */
    void serialClosed();

    /**
     * @brief 串口列表更新时触发
     * @param ports 串口名称列表
     */
    void portListUpdated(const QStringList &ports);

    /**
     * @brief 向 MainWindow 发送数据回显信号
     * @param data 发送的数据
     * @param isHex 是否以 HEX 格式显示
     */
    void dataToSendToMainWindow(const QByteArray &data, bool isHex);

private slots:
    /**
     * @brief 内部槽函数：读取串口数据
     *        当串口 readyRead 信号触发时调用
     */
    void readSerialData();

    /**
     * @brief 内部槽函数：处理串口错误
     * @param error 错误类型
     */
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort *serial = nullptr;   ///< 串口对象指针
    QTimer *g_scanTimer = nullptr;   ///< 定时扫描串口的定时器
};

#endif // SERIALMANAGER_H
