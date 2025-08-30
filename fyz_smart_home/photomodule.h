#ifndef PHOTOMODULE_H
#define PHOTOMODULE_H

#include <QString>
#include <QVector>
#include <QObject>

// 前向声明，避免直接包含 MainWindow 头文件，减少依赖
class MainWindow;
/**
 * @brief photomodule 类
 *
 * 该类用于实现相册功能：
 * - 加载图片文件列表
 * - 显示当前图片
 * - 支持上一张/下一张切换
 *
 * 该类不继承 QWidget，而是通过传入 MainWindow 指针操作 UI 控件。
 */
class photomodule : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 可选的父对象
     *
     * 通过 parent 可以让 QObject 正确管理生命周期。
     */
    explicit photomodule(QWidget *parent = nullptr);

    /** @brief 显示下一张照片 */
    void showNext();

    /** @brief 显示上一张照片 */
    void showPrev();
    /**
     * @brief 加载指定路径下的所有图片文件
     * @param path 图片文件夹路径
     */
    void loadPhotos(const QString &path);

private:

    /**
     * @brief 更新 QLabel 显示当前索引的图片
     */
    void updatePhoto();

private:
    MainWindow *mainWindow;      ///< 指向主窗口，操作 UI 控件

    QVector<QString> photos;     ///< 存储图片文件路径列表
    int currentIndex = 0;        ///< 当前显示的图片索引
};

#endif // PHOTOMODULE_H
