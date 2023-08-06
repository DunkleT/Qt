#include "desktoptextshowdialog.h"
#include "ui_desktoptextshowdialog.h"

#include <QFile>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>

DesktopTextShowDialog::DesktopTextShowDialog(QString needShowText, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DesktopTextShowDialog)
{
    ui->setupUi(this);
    //读取保存的播报设置文件
    QString filename ="dataShowSetting.ini";
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QStringList settingDataList;
        QString  iii = "﹎";
        QString settingDataStr;
        settingDataStr = file.readAll();
        if(settingDataStr != "")
        {
            settingDataList = settingDataStr.split(iii.toUtf8());
            if(settingDataList.length()==7)
            {

                fontColor_R = settingDataList[0].toInt();
                fontColor_G = settingDataList[1].toInt();
                fontColor_B = settingDataList[2].toInt();
                transparency = settingDataList[3].toInt();
                rollSpeed = settingDataList[4].toInt();
                textShowWidth = settingDataList[5].toInt();
                textShowHeight = settingDataList[6].toInt();
                file.close();
            }
        }
    }

    //创建新窗口
    this->setWindowFlags(Qt::Dialog |Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明

    //窗口大小
    resize(textShowWidth, textShowHeight);

    //滚动文字
    timer = new QTimer(this);//创建定时器
    connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));

    //文字内容
    text = needShowText;


    setText(text);
}

DesktopTextShowDialog::~DesktopTextShowDialog()
{
    delete ui;
}

//设置字体相关信息
void DesktopTextShowDialog::setText(QString text)
{
    font.setFamily("Microsoft Yahei");//字体样式——微软雅黑

    showText = text;            //显示内容

    //计算字符大小
    QFontMetrics metrics(font);
    int char_w = metrics.horizontalAdvance(" ");
    setDelay(50,char_w*rollSpeed/10);//调用setDelay()函数,设置滚动延时

    int blankLine =width()/char_w+2;
    for(int i=0;i<blankLine;i++)
    {
        showText.insert(0," ");//开头插入blankLine个空格
    }

    m_moveSize=metrics.horizontalAdvance(showText)+width()/char_w+2;
    m_moveOffset = 0;
    //如果计时器没有运行
    if(!timer->isActive())
    {
        if(m_ms)
        {
            timer->start(m_ms);//启动计时,以m_ms为间隔
        }
    }
}

void DesktopTextShowDialog::timeOut(){
    m_moveOffset+=m_pixelSize;

    if(m_moveOffset>m_moveSize)
    {
        m_moveOffset= 0;
    }
    update();
}

//设置滚动延迟,多少ms滚动多少像素点pixelSize
void DesktopTextShowDialog::setDelay(int ms,int pixelSize)
{
    this->m_ms=ms;
    this->m_pixelSize=pixelSize;
}

//绘图事件
void DesktopTextShowDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setFont(font);//设置字体
    painter.setPen(QColor(fontColor_R, fontColor_G, fontColor_B, transparency));//文字颜色

    //外边框
    //painter.setPen(QColor(120,120,120));//设置画笔颜色——灰色
    //painter.drawRect(QRect(0,0,width()-1,height()-1));//主窗口绘制矩形
    //播报文字
    painter.drawText(QRect(-m_moveOffset,0,width()-1+m_moveOffset-(height()*1.5),height()-1),
                   Qt::AlignVCenter|Qt::AlignLeft,showText);//绘制文字,水平居左垂直居中
    //拖动定位符
    QString locationText = "█";
    painter.drawText(QRect(width()-1-(height()*1.35), 0, height(), height()-1), Qt::AlignVCenter|Qt::AlignHCenter, locationText);
}

void DesktopTextShowDialog::resizeEvent(QResizeEvent *event)
{
    font.setPixelSize(event->size().height()*0.75);//字体大小(这里设置为窗口高度的0.75倍)
    showText = text;

    //计算字符大小
    QFontMetrics metrics(font);
    int char_w = metrics.horizontalAdvance(" ");
    setDelay(50,char_w*rollSpeed/10);//调用setDelay()函数,设置滚动延时

    int blankLine =width()/char_w+2;
    for(int i=0;i<blankLine;i++)
    {
        showText.insert(0," ");//开头插入blankLine个空格
    }

    m_moveSize=metrics.horizontalAdvance(showText)+width()/char_w+2;
    m_moveOffset = 0;
    update();
}

//鼠标拖拽移动
void DesktopTextShowDialog::mouseMoveEvent(QMouseEvent *event)
{
    QPoint y = event->globalPos();//鼠标相当于桌面左上角的位置，鼠标全局位置
    QPoint x = y - this->z;
    this->move(x);
}
void DesktopTextShowDialog::mousePressEvent(QMouseEvent *event)
{
    QPoint y = event->globalPos();//鼠标相当于桌面左上角的位置，鼠标全局位置
    QPoint x = this->geometry().topLeft();//窗口左上角位于桌面左上角的位置，窗口位置
    this->z = y - x; //定值，不变
}
void DesktopTextShowDialog::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    this->z = QPoint(); //鼠标松开获取当前的坐标
}
