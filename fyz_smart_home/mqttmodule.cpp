#include "MqttModule.h"
#include <QDateTime>
#include <QDebug>

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
    connect(mqttTestTimer, &QTimer::timeout, this, &MqttModule::sendTestMessage);
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
    emit messageReceived(topic.name(), message);
}

void MqttModule::sendTestMessage()
{
    if(!m_client || m_client->state() != QMqttClient::Connected) return;
    QString topic = "fyz/123/test/112233";
    QString msg = QString("Test message #%1").arg(testCounter++);
    publishMessage(topic, msg);
    emit signal_publishMessage(topic, msg);
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
