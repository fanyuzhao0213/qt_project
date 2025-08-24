#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>  // 必须包含，用于重写 paintEvent
#include <QtMqtt/qmqttclient.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMqttClient *m_client = nullptr;

    void MyMQTTSubscribe(QString);
    void MyMQTTSendMessage(const QString, const QString);

public slots:
    void brokerConnected();
    void updateLogStateChange();
    void brokerDisconnected();
    void receiveMess(const QByteArray &, const QMqttTopicName &);

protected:
    void paintEvent(QPaintEvent *event) override; // 重写 paintEvent
private slots:
    void on_ledBtn_clicked(bool checked);

    void on_alarmBtn_clicked(bool checked);

    void on_fanBtn_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
