#include "mqttmodule.h"
#include <QDateTime>
#include <QDebug>
#include <qdatetime.h>

#define SUB_TOPIC   "fyz/123/#"

MqttModule::MqttModule(QObject *parent) : QObject(parent)
{
    m_client = new QMqttClient(this);
    testCounter = 0;

    connect(m_client, &QMqttClient::stateChanged, this, [=](QMqttClient::ClientState state){
        emit stateChanged(state);
    });

    // 信号绑定
    connect(m_client, &QMqttClient::connected, this, &MqttModule::onConnected);
    connect(m_client, &QMqttClient::disconnected, this, &MqttModule::onDisconnected);
    connect(m_client, &QMqttClient::messageReceived, this, &MqttModule::handleMessageReceived);

    mqttTestTimer = new QTimer(this);
    /*模拟发送mqttpub 槽函数*/
//    connect(mqttTestTimer, &QTimer::timeout, this, &MqttModule::sendTestMessage);
}

MqttModule::~MqttModule() {}

void MqttModule::connectToBroker(const QString &host, quint16 port)
{
    // 设置 MQTT 客户端的服务器地址和端口
     m_client->setHostname(host);
     m_client->setPort(port);

     // 触发连接
     m_client->connectToHost();

//     // 如果传入了对应的 UI 控件，则更新 UI 显示
//     if(lineEditBroker) lineEditBroker->setText(host);
//     if(lineEditPort) lineEditPort->setText(QString::number(port));

//     // 生成日志字符串
//     if(textEditLog){
//         QString log = QString("服务器地址: %1").arg(host);
//         textEditLog->append(log);

//         log = QString("服务器端口: %1").arg(port);
//         textEditLog->append(log);
//     }
}

void MqttModule::subscribeTopic(const QString &topic)
{
    auto sub = m_client->subscribe(topic, 0);
    if(!sub) {
        qDebug() << "MQTT subscribe failed!";
    }
}

void MqttModule::publishMessage(const QString &topic, const QString &msg)
{
    if(m_client->publish(topic, msg.toUtf8()) == -1){
        qDebug() << "MQTT publish failed!";
    }
}

void MqttModule::startTestPublish(int intervalMs)
{
    mqttTestTimer->start(intervalMs);
}

void MqttModule::handleMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    /*解析json数据*/
    qDebug() << "收到MQTT消息, Topic:" << topic.name();
    qDebug() << "原始消息:" << message;

    // 1. 将 QByteArray 转成 QJsonDocument
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(message, &parseError);

    if (doc.isNull() || parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON 解析失败:" << parseError.errorString();
        return; // ❌ 不要 return -1，因为这是 void 函数
    }

    // 2. 确认是对象
    if (!doc.isObject()) {
        qDebug() << "JSON 格式不是对象";
        return;
    }

    QJsonObject root = doc.object();
    /*
    {
      "header": {
        "device_id": "dev-001",
        "msg_id": 1002
      },
      "payload": {
        "user": {
          "name": "Alice",
          "age": 25
        }
      }
    }
    */
    // ===== 示例：解析 header 里的内容 =====
    if (root.contains("header") && root["header"].isObject()) {
        // 取出 header 对象
        QJsonObject header = root["header"].toObject();

        // 从 header 中读取字符串类型的 "device_id"
        QString deviceId = header["device_id"].toString();

        // 从 header 中读取整型的 "msg_id"
        int msgId = header["msg_id"].toInt();

        // 打印出来，方便调试
        qDebug() << "设备ID:" << deviceId;
        qDebug() << "消息ID:" << msgId;
    }


    // ===== 示例：解析 payload 里的 user 对象 =====
    if (root.contains("payload") && root["payload"].isObject()) {
        // 取出 payload 对象
        QJsonObject payload = root["payload"].toObject();

        // 检查 payload 里是否包含 "user" 且是对象
        if (payload.contains("user") && payload["user"].isObject()) {
            // 取出 user 对象
            QJsonObject user = payload["user"].toObject();

            // 从 user 中读取字符串字段 "name"
            QString name = user["name"].toString();

            // 从 user 中读取整型字段 "age"
            int age = user["age"].toInt();

            // 打印出来，方便调试
            qDebug() << "用户名:" << name;
            qDebug() << "年龄:" << age;
        }
    }

    emit messageReceived(topic.name(), message);
}

/*
{
  "header": {
    "device_id": "dev-001",
    "timestamp": "2025-08-25T12:00:00Z",
    "msg_id": 1001
  },
  "payload": {
    "sensor_data": [
      {
        "type": "temperature",
        "value": 26.4,
        "unit": "C"
      },
      {
        "type": "humidity",
        "value": 55.2,
        "unit": "%"
      }
    ]
  }
}
*/
/*调用发送mqtt函数*/
void MqttModule::sendTestMessage()
{
    static int msg_id  = 1;
    if(!m_client || m_client->state() != QMqttClient::Connected) return;
    /*string 数据*/
//    QString topic = "fyz/123/test/112233";
//    QString msg = QString("Test message #%1").arg(testCounter++);
//    publishMessage(topic, msg);

    /*json数据*/
    QString topic = "fyz/123/test/112233";

    // 1. header 对象
    QJsonObject header;
    header.insert("device_id","V_hw_01.01.00_sw_2.2.88");
    header.insert("timestamp", QDateTime::currentDateTimeUtc().toString(Qt::ISODate)); // UTC时间
    header["msg_id"] = msg_id++;  // 可变参数，每次发送时可以 ++

    // 2. payload 对象里的 sensor_data 数组
    QJsonArray sensorArray;
    QJsonObject temp;
    temp.insert("type","temperature");
    temp.insert("value",26.4);
    temp.insert("unit","C");
    sensorArray.append(temp);
    QJsonObject hum;
    hum.insert("type","humidity");
    hum.insert("value",55.2);
    hum.insert("unit","%");
    sensorArray.append(hum);

    // 3. payload 对象
    QJsonObject payload;
    payload.insert("sensor_data", sensorArray);

    // 4. 根对象
    QJsonObject root;
    root.insert("header", header);
    root.insert("payload", payload);

    // 5. 转成 JSON 字符串
    QJsonDocument doc(root);
    QString jsonString = doc.toJson(QJsonDocument::Compact);
    qDebug() << jsonString;
    publishMessage(topic, jsonString);

    emit signal_publishMessage(topic, jsonString);
}

// 槽函数
void MqttModule::onConnected()
{
    subscribeTopic(SUB_TOPIC);
    emit connected();
}

void MqttModule::onDisconnected()
{
    emit disconnected();
}
