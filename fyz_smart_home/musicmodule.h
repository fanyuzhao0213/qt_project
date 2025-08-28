#ifndef MUSICMODULE_H
#define MUSICMODULE_H

#include <QWidget>
#include <QMediaPlayer>
#include <QUrl>
#include <QMediaMetaData>

class musicmodule : public QWidget
{
    Q_OBJECT
public:
    explicit musicmodule(QWidget *parent = nullptr);
    // 播放指定路径的音乐
    void playMusic(const QString &filePath);
    // 播放 / 暂停
    void playPause();
    // 停止
    void stop();
    // 设置音量 0-100
    void setVolume(int vol);

    // 获取播放对象，用于绑定进度条
    QMediaPlayer* player();
public slots:
    void updateSongInfo();
signals:
    void playSuccess(); // 播放成功信号
    void playFailed(const QString &errorMsg); // 播放失败信号
    void songInfoChanged(const QString &title, const QString &artist, const QString &composer); // 歌曲信息
private:
    QMediaPlayer *m_player;
    QString m_currentFile;  // 保存当前播放文件路径
private slots:
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void handleError(QMediaPlayer::Error error);
};
#endif // MUSICMODULE_H
