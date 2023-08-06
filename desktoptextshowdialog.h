#ifndef DESKTOPTEXTSHOWDIALOG_H
#define DESKTOPTEXTSHOWDIALOG_H

#include <QDialog>

namespace Ui {
class DesktopTextShowDialog;
}

class DesktopTextShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DesktopTextShowDialog(QString needShowText, QWidget *parent = nullptr);
    ~DesktopTextShowDialog();
    void setText(QString text);
    void setDelay(int ms, int pixelSize);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void timeOut();

private:
    Ui::DesktopTextShowDialog *ui;
    QTimer* timer;          //滚动定时器
    QString text;           //播报文字
    QString showText;       //显示内容
    QFont font;             //播报字体

    QPoint z;               //当前点击位置坐标

    int m_ms;               //文字滚动帧时间
    int m_pixelSize;        //文字滚动帧偏移
    int m_moveOffset;       //文字滚动偏移
    int m_moveSize;         //文字滚动最大值

    int fontColor_R = 0;
    int fontColor_G = 0;
    int fontColor_B = 0;
    int transparency = 255;
    int rollSpeed = 4;
    int textShowWidth = 800;
    int textShowHeight = 80;

    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // DESKTOPTEXTSHOWDIALOG_H
