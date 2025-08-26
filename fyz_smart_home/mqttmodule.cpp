#include "mqttmodule.h"
#include <QDateTime>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#define SUB_TOPIC   "fyz/123/#"   // 默认订阅的主题

MqttModule::MqttModule(QObject *parent) : QObject(parent)
{
    m_client = new QMqttClient(this);
    testCounter = 0;

    // ===== 信号绑定 =====
    connect(m_client, &QMqttClient::stateChanged, this, [=](QMqttClient::ClientState state){
        emit stateChanged(state);
    });

    connect(m_client, &QMqttClient::connected,    this, &MqttModule::onConnected);
    connect(m_client, &QMqttClient::disconnected, this, &MqttModule::onDisconnected);
    connect(m_client, &QMqttClient::messageReceived, this, &MqttModule::handleMessageReceived);

    // 定时器，用于测试定时发布消息
    mqttTestTimer = new QTimer(this);
    // connect(mqttTestTimer, &QTimer::timeout, this, &MqttModule::sendTestMessage);
}

MqttModule::~MqttModule() {}

/**
 * @brief 连接到 MQTT Broker
 * @param host 服务器地址
 * @param port 端口
 * @param clientId 客户端 ID
 * @param username 用户名（可为空）
 * @param password 密码（可为空）
 */
// 重载函数 1：只传 host, port, clientId
void MqttModule::connectToBroker(const QString &host, quint16 port, const QString &clientId)
{
    m_client->setHostname(host);
    m_client->setPort(port);

    if (!clientId.isEmpty()) {
        m_client->setClientId(clientId);
    }

    // 触发连接
    m_client->connectToHost();
}

// 重载函数 2：host, port, clientId, username, password
void MqttModule::connectToBroker(const QString &host, quint16 port,
                                 const QString &clientId,
                                 const QString &username,
                                 const QString &password)
{
    m_client->setHostname(host);
    m_client->setPort(port);

    if (!clientId.isEmpty()) {
        m_client->setClientId(clientId);
    }
    if (!username.isEmpty()) {
        m_client->setUsername(username);
    }
    if (!password.isEmpty()) {
        m_client->setPassword(password);
    }

    // 触发连接
    m_client->connectToHost();
}

/**
 * @brief 发布消息
 * @param topic 主题
 * @param msg 消息内容
 */
void MqttModule::publishMessage(const QString &topic, const QString &msg)
{
    if(m_client->publish(topic, msg.toUtf8()) == -1){
        qDebug() << "❌ MQTT publish failed!";
    }
}

/**
 * @brief 启动定时测试发布
 * @param intervalMs 时间间隔 (毫秒)
 */
void MqttModule::startTestPublish(int intervalMs)
{
    mqttTestTimer->start(intervalMs);
}

/**
 * @brief 处理接收到的 MQTT 消息
 * @param message 收到的消息数据
 * @param topic 消息对应的主题
 */
void MqttModule::handleMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    qDebug() << "📩 收到MQTT消息, Topic:" << topic.name();
    qDebug() << "原始消息:" << message;

    // JSON 解析
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(message, &parseError);

    if (doc.isNull() || parseError.error != QJsonParseError::NoError) {
        qDebug() << "❌ JSON 解析失败:" << parseError.errorString();
        return;
    }

    if (!doc.isObject()) {
        qDebug() << "❌ JSON 格式不是对象";
        return;
    }

    QJsonObject root = doc.object();

    // ===== 解析 header =====
    if (root.contains("header") && root["header"].isObject()) {
        QJsonObject header = root["header"].toObject();
        QString deviceId = header["device_id"].toString();
        int msgId = header["msg_id"].toInt();

        qDebug() << "设备ID:" << deviceId;
        qDebug() << "消息ID:" << msgId;
    }

    // ===== 解析 payload =====
    if (root.contains("payload") && root["payload"].isObject()) {
        QJsonObject payload = root["payload"].toObject();

        if (payload.contains("user") && payload["user"].isObject()) {
            QJsonObject user = payload["user"].toObject();
            QString name = user["name"].toString();
            int age = user["age"].toInt();

            qDebug() << "用户名:" << name;
            qDebug() << "年龄:" << age;
        }
    }

    // 发出信号供 UI 层使用
    emit messageReceived(topic.name(), message);
}

/**
 * @brief 发送测试 JSON 消息 (模拟传感器数据)
 */
void MqttModule::sendTestMessage()
{
    static int msg_id  = 1;
    if(!m_client || m_client->state() != QMqttClient::Connected) return;

    QString topic = "fyz/123/test/112233";

    // ===== 构建 header =====
    QJsonObject header;
    header.insert("device_id", "V_hw_01.01.00_sw_2.2.88");
    header.insert("timestamp", QDateTime::currentDateTimeUtc().toString(Qt::ISODate));
    header["msg_id"] = msg_id++;

    // ===== 构建 payload (模拟温湿度数据) =====
    QJsonArray sensorArray;

    QJsonObject temp;
    temp.insert("type", "temperature");
    temp.insert("value", 26.4);
    temp.insert("unit", "C");
    sensorArray.append(temp);

    QJsonObject hum;
    hum.insert("type", "humidity");
    hum.insert("value", 55.2);
    hum.insert("unit", "%");
    sensorArray.append(hum);

    QJsonObject payload;
    payload.insert("sensor_data", sensorArray);

    // ===== 根对象 =====
    QJsonObject root;
    root.insert("header", header);
    root.insert("payload", payload);

    // 转成 JSON 字符串
    QJsonDocument doc(root);
    QString jsonString = doc.toJson(QJsonDocument::Compact);
    qDebug() << "📤 发布测试消息:" << jsonString;

    // 发布
    publishMessage(topic, jsonString);
    emit signal_publishMessage(topic, jsonString);
}

// MqttModule.cpp
void MqttModule::disconnectFromBroker()
{
    if (m_client && m_client->state() == QMqttClient::Connected) {
        m_client->disconnectFromHost();  // 主动断开
        qDebug() << "MQTT 断开连接中...";
    } else {
        qDebug() << "MQTT 已经断开或未初始化";
    }
}

/**
 * @brief 连接成功槽函数
 */
void MqttModule::onConnected()
{
    // subscribeTopic(SUB_TOPIC);  // 自动订阅默认主题
    emit connected();
}

/**
 * @brief 断开连接槽函数
 */
void MqttModule::onDisconnected()
{
    emit disconnected();
}


// MqttModule.cpp
bool MqttModule::isConnected() const
{
    return m_client && m_client->state() == QMqttClient::Connected;
}

/**
 * @brief 订阅指定主题
 * @param topic 主题字符串
 */
void MqttModule::subscribeTopic(const QString &topic)
{
    if (!m_client) return;

    if (m_client->state() == QMqttClient::Connected) {
        auto subscription = m_client->subscribe(topic);
        if (!subscription) {
            qDebug() << "订阅失败:" << topic;
        } else {
            qDebug() << "已订阅:" << topic;
        }
    } else {
        qDebug() << "MQTT 未连接，无法订阅";
    }
}
