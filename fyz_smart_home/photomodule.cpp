#include "photomodule.h"
#include <QDir>
#include <QDebug>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include "mainwindow.h"   // 必须包含完整定义

/**
 * @brief 构造函数
 * @param parent 父对象，一般为 MainWindow
 *
 * 通过 mainWindow 获取 UI 控件，连接上一张、下一张和退出按钮的槽函数。
 */
photomodule::photomodule(QWidget *parent) : QObject(parent), mainWindow(qobject_cast<MainWindow*>(parent))
{
    // 只有在 mainWindow 非空时才连接信号
    if(mainWindow)
    {
        // 上一张按钮
        connect(mainWindow->getPrevButton(), &QPushButton::clicked,
                this, &photomodule::showPrev);

        // 下一张按钮
        connect(mainWindow->getNextButton(), &QPushButton::clicked,
                this, &photomodule::showNext);

//        // 退出按钮，切换回主界面
//        connect(mainWindow->getExitButton(), &QPushButton::clicked, [=](){
//            mainWindow->switchStackedPage(0);
//            qDebug() << "[PhotoModule] Switch to main page.";
//        });
    }
}

/**
 * @brief 加载指定目录下的所有图片
 * @param path 图片文件夹路径
 *
 * 支持 *.png, *.jpg, *.jpeg 格式，加载完成后自动显示第一张。
 */
void photomodule::loadPhotos(const QString &path)
{
    QDir dir(path);
    QStringList filters = {"*.png", "*.jpg", "*.jpeg"};
    QFileInfoList fileList = dir.entryInfoList(filters, QDir::Files);

    photos.clear();  // 清空已有列表
    for (const QFileInfo &f : fileList) {
        photos.append(f.absoluteFilePath());
    }

    qDebug() << "[PhotoModule] Loaded" << photos.size() << "photos.";

    // 自动显示第一张
    currentIndex = 0;
    updatePhoto();
}

/**
 * @brief 更新 QLabel 显示当前图片
 */
void photomodule::updatePhoto()
{
    if (photos.isEmpty() || !mainWindow) return;

    QPixmap pix(photos[currentIndex]);
    QLabel *label = mainWindow->getPhotoLabel();

    if(label)
        label->setPixmap(pix.scaled(label->size(),
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation));
}

/**
 * @brief 显示下一张图片
 */
void photomodule::showNext()
{
    if (photos.isEmpty()) return;
    currentIndex = (currentIndex + 1) % photos.size();  // 循环到开头
    updatePhoto();
}

/**
 * @brief 显示上一张图片
 */
void photomodule::showPrev()
{
    if (photos.isEmpty()) return;
    currentIndex = (currentIndex - 1 + photos.size()) % photos.size(); // 循环到末尾
    updatePhoto();
}
