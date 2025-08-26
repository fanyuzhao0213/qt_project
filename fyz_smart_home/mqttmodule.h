#ifndef MQTTMODULE_H
#define MQTTMODULE_H

#include <QObject>
#include <QtMqtt/qmqttclient.h>
#include <QTimer>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

/**
 * @brief MqttModule 类
 *        封装了 MQTT 客户端的连接、订阅、发布、消息处理逻辑
 *        支持 JSON 格式解析与测试消息发送
 */
class MqttModule : public QObject
{
    Q_OBJECT

public:
    explicit MqttModule(QObject *parent = nullptr);
    ~MqttModule();

    /**
     * @brief 连接到 MQTT Broker
     * @param host 主机地址
     * @param port 端口号
     */
    // 只有 host, port, clientId
    void connectToBroker(const QString &host, quint16 port, const QString &clientId);

    // 所有参数都需要
    void connectToBroker(const QString &host, quint16 port,
                         const QString &clientId,
                         const QString &username,
                         const QString &password);

    /**
     * @brief 订阅主题
     * @param topic 主题名称
     */
    void subscribeTopic(const QString &topic);

    /**
     * @brief 发布消息
     * @param topic 主题
     * @param msg 消息内容
     */
    void publishMessage(const QString &topic, const QString &msg);

    /**
     * @brief 启动定时测试发布
     * @param intervalMs 时间间隔（毫秒），默认 5000ms
     */
    void startTestPublish(int intervalMs = 5000);

signals:
    /**
     * @brief 收到消息时发出
     * @param topic 主题
     * @param msg 消息内容
     */
    void messageReceived(const QString &topic, const QByteArray &msg);

    /**
     * @brief MQTT 客户端状态变化时发出
     */
    void stateChanged(QMqttClient::ClientState state);

    /**
     * @brief 连接成功信号
     */
    void connected();

    /**
     * @brief 断开连接信号
     */
    void disconnected();

    /**
     * @brief 发布消息信号（供 UI 显示）
     */
    void signal_publishMessage(QString topic, QString msg);

private slots:
    /**
     * @brief 处理接收到的消息
     * @param message 消息内容
     * @param topic 消息主题
     */
    void handleMessageReceived(const QByteArray &message, const QMqttTopicName &topic);

    /**
     * @brief 发送测试消息（JSON 格式，模拟传感器数据）
     */
    void sendTestMessage();

    /**
     * @brief 连接成功槽函数
     */
    void onConnected();

    /**
     * @brief 断开连接槽函数
     */
    void onDisconnected();

private:
    QMqttClient *m_client;   ///< MQTT 客户端对象
    QTimer *mqttTestTimer;   ///< 定时器，用于定时发送测试消息
    int testCounter;         ///< 测试消息计数器
};

#endif // MQTTMODULE_H
