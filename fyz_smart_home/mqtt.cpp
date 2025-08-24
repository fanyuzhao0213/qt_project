#include "mqtt.h"

mqtt::mqtt(QWidget *parent) : QWidget(parent)
{

}


// 定时发送槽函数
void MainWindow::sendTestMessage()
{
    if (!m_client || m_client->state() != QMqttClient::Connected) {
        qDebug() << "MQTT not connected!";
        return;
    }

    QString topic = "fyz/123/test";
    QString message = QString("Test message #%1").arg(testCounter++);

    if (m_client->publish(topic, message.toUtf8()) == -1) {
        qDebug() << "Could not publish message";
        ui->textEditMessage->append("Could not publish message");
    } else {
        qDebug() << "Published:" << message;
        ui->textEditMessage->append("Published: " + message);
    }
}

// 启动定时器函数
void MainWindow::startMQTTSendTest()
{
    connect(mqttTestTimer, &QTimer::timeout, this, &MainWindow::sendTestMessage);
    mqttTestTimer->start(5000); // 每 5 秒触发一次
}

