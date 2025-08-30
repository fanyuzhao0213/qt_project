#include "musicmodule.h"
#include <QFileInfo>
#include <QDebug>

musicmodule::musicmodule(QWidget *parent) : QWidget(parent)
{
    // 创建 QMediaPlayer 对象
    m_player = new QMediaPlayer(this);

    // 设置默认音量为 50%
    m_player->setVolume(50);

    // 连接媒体状态变化信号
    connect(m_player, &QMediaPlayer::mediaStatusChanged,
            this, &musicmodule::handleMediaStatusChanged);

    // 连接播放错误信号
    connect(m_player, SIGNAL(error(QMediaPlayer::Error)),
            this, SLOT(handleError(QMediaPlayer::Error)));

    // 【新增】连接元数据变化信号，用于更新歌曲信息
    // 使用lambda表达式作为中间层
    // 使用旧的字符串连接语法
    connect(m_player, SIGNAL(metaDataChanged()),
            this, SLOT(updateSongInfo()));

    playMusic("qrc:/music/1.mp3"); // 注意路径不要用反斜杠

}

// 播放指定路径的音乐
void musicmodule::playMusic(const QString &filePath)
{
    if (filePath.isEmpty()) {
        emit playFailed("文件路径为空");
        return;
    }

    // 判断是否资源路径
    if (filePath.startsWith("qrc:/")) {
        m_player->setMedia(QUrl(filePath));  // 资源路径直接用 QUrl
    } else {
        QFileInfo checkFile(filePath);
        if (!checkFile.exists() || !checkFile.isFile()) {
            emit playFailed("文件不存在或不是有效文件: " + filePath);
            return;
        }
        m_player->setMedia(QUrl::fromLocalFile(filePath)); // 本地文件使用 fromLocalFile
    }

    m_currentFile = filePath;
    qDebug() << "[播放] 设置媒体文件：" << m_currentFile;
    m_player->play();
}

// 播放/暂停切换
void musicmodule::playPause()
{
    if(m_player->state() == QMediaPlayer::PlayingState)
        m_player->pause();
    else
        m_player->play();
}

// 停止播放
void musicmodule::stop()
{
    m_player->stop(); // 停止播放并将播放位置重置到开头
}

// 设置音量
void musicmodule::setVolume(int vol)
{
    m_player->setVolume(vol); // 范围 0-100
}

// 获取内部 QMediaPlayer 对象
QMediaPlayer* musicmodule::player()
{
    return m_player; // 外部可以绑定进度条或获取播放状态
}

// 处理媒体状态变化
void musicmodule::handleMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    switch (status) {
    case QMediaPlayer::UnknownMediaStatus:
        qDebug() << "[状态] UnknownMediaStatus, 文件：" << m_currentFile;
        break;
    case QMediaPlayer::NoMedia:
        qDebug() << "[状态] NoMedia, 文件：" << m_currentFile;
        break;
    case QMediaPlayer::LoadingMedia:
        qDebug() << "[状态] LoadingMedia, 正在加载：" << m_currentFile;
        break;
    case QMediaPlayer::LoadedMedia:
        qDebug() << "[状态] LoadedMedia, 媒体加载完成：" << m_currentFile;
        emit playSuccess(); // 可以认为准备播放成功
        break;
    case QMediaPlayer::StalledMedia:
        qDebug() << "[状态] StalledMedia, 播放被中断或缓冲：" << m_currentFile;
        break;
    case QMediaPlayer::BufferedMedia:
        qDebug() << "[状态] BufferedMedia, 缓冲完成，准备播放：" << m_currentFile;
        emit playSuccess(); // 可以认为准备播放成功
        break;
    case QMediaPlayer::EndOfMedia:
        qDebug() << "[状态] EndOfMedia, 播放结束：" << m_currentFile;
        emit playFailed("播放结束：");
        break;
    case QMediaPlayer::InvalidMedia:
        qDebug() << "[状态] InvalidMedia, 无效文件：" << m_currentFile;
        emit playFailed("无效的媒体文件");
        break;
    default:
        qDebug() << "[状态] 未知状态:" << status << " 文件：" << m_currentFile;
        break;
    }
}

// 处理播放错误
void musicmodule::handleError(QMediaPlayer::Error error)
{
    if (error != QMediaPlayer::NoError) {
        emit playFailed(m_player->errorString()); // 将错误信息发送给 MainWindow
    }
}

// 【新增函数】更新歌曲信息并发送给 MainWindow
void musicmodule::updateSongInfo()
{
    QString title, artist, album;
    int duration = 0; // 单位：秒

    // 方法1：QtMetaData
    if (m_player->isMetaDataAvailable()) {
        QVariant titleVar  = m_player->metaData(QMediaMetaData::Title);
        QVariant artistVar = m_player->metaData(QMediaMetaData::Author);
        QVariant albumVar  = m_player->metaData(QMediaMetaData::AlbumTitle);

        if (titleVar.isValid())  title  = titleVar.toString();
        if (artistVar.isValid()) artist = artistVar.toString();
        if (albumVar.isValid())  album  = albumVar.toString();
    }

    // 方法2：如果仍然为空，用文件名解析
    if (title.isEmpty()) {
        QString fileName = QFileInfo(m_currentFile).baseName(); // 去掉扩展名
        QRegExp pattern("(.+)\\s+-\\s+(.+)"); // 歌手 - 歌曲名
        if (pattern.indexIn(fileName) != -1) {
            artist = pattern.cap(1).trimmed();
            title  = pattern.cap(2).trimmed();
        } else {
            title = fileName; // 文件名直接作为标题
        }
    }

    // 方法3：获取歌曲时长（毫秒 -> 秒）
    if (m_player->duration() > 0)
        duration = m_player->duration() / 1000;

    // 打印调试信息
    qDebug() << "=== 歌曲信息 ===";
    qDebug() << "文件路径:" << m_currentFile;
    qDebug() << "标题    :" << title;
    qDebug() << "歌手    :" << artist;
    qDebug() << "专辑    :" << album;
    qDebug() << "时长(s) :" << duration;
    qDebug() << "================";

    // 发信号给 UI
    emit songInfoChanged(title, artist, album);
}



