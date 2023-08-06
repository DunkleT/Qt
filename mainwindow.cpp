#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "desktoptextshowdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString filename ="dataShowSetting.ini";
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //读取文件成功
        QStringList settingDataList;
        QString  iii = "﹎";
        QString settingDataStr;

        settingDataStr = file.readAll();
        if(settingDataStr != "")
        {
            settingDataList = settingDataStr.split(iii.toUtf8());
            if(settingDataList.length()==7)
            {
                settingFontColor_R = settingDataList[0].toInt();
                settingFontColor_G = settingDataList[1].toInt();
                settingFontColor_B = settingDataList[2].toInt();
                setTransparency = settingDataList[3].toInt();
                setRollSpeed = settingDataList[4].toInt();
                setTextShowWidth = settingDataList[5].toInt();
                setTextShowHeight = settingDataList[6].toInt();
                file.close();
            }
            else
            {
                file.close();
                //创建文件
                file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);
                //写入默认数值
                needWriteStr = QString::number(settingFontColor_R) + "﹎" ;
                needWriteStr += QString::number(settingFontColor_G) + "﹎";
                needWriteStr += QString::number(settingFontColor_B) + "﹎";
                needWriteStr += QString::number(setTransparency) + "﹎";
                needWriteStr += QString::number(setRollSpeed) + "﹎";
                needWriteStr += QString::number(setTextShowWidth) + "﹎";
                needWriteStr += QString::number(setTextShowHeight);
                file.write(needWriteStr.toUtf8());
                file.close();
            }
        }
    }
    else
    {
        //创建文件
        file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);
        //写入默认数值
        needWriteStr = QString::number(settingFontColor_R) + "﹎" ;
        needWriteStr += QString::number(settingFontColor_G) + "﹎";
        needWriteStr += QString::number(settingFontColor_B) + "﹎";
        needWriteStr += QString::number(setTransparency) + "﹎";
        needWriteStr += QString::number(setRollSpeed) + "﹎";
        needWriteStr += QString::number(setTextShowWidth) + "﹎";
        needWriteStr += QString::number(setTextShowHeight);
        file.write(needWriteStr.toUtf8());
        file.close();
    }

    //初始化显示
    ui->spinBox_R->setValue(settingFontColor_R);
    ui->spinBox_G->setValue(settingFontColor_G);
    ui->spinBox_B->setValue(settingFontColor_B);
    ui->spinBox_A->setValue(setTransparency);
    ui->spinBox_speed->setValue(setRollSpeed);
    ui->spinBox_width->setValue(setTextShowWidth);
    ui->spinBox_height->setValue(setTextShowHeight);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_begin_clicked()
{
    //读取设置参数
    settingFontColor_R = ui->spinBox_R->value();
    settingFontColor_G = ui->spinBox_G->value();
    settingFontColor_B = ui->spinBox_B->value();
    setTransparency = ui->spinBox_A->value();
    setRollSpeed = ui->spinBox_speed->value();
    setTextShowWidth = ui->spinBox_width->value();
    setTextShowHeight = ui->spinBox_height->value();

    //打开文件，写入参数设置
    QString filename ="dataShowSetting.ini";
    QFile file(filename);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);
    //写入默认数值
    needWriteStr = QString::number(settingFontColor_R) + "﹎" ;
    needWriteStr += QString::number(settingFontColor_G) + "﹎";
    needWriteStr += QString::number(settingFontColor_B) + "﹎";
    needWriteStr += QString::number(setTransparency) + "﹎";
    needWriteStr += QString::number(setRollSpeed) + "﹎";
    needWriteStr += QString::number(setTextShowWidth) + "﹎";
    needWriteStr += QString::number(setTextShowHeight);
    file.write(needWriteStr.toUtf8());
    file.close();

    //判断播报
    if(ui->plainTextEdit->toPlainText()=="")
    {
        ui->statusbar->showMessage("在播报文字输入框输入要滚动播报的文字！", 3000);
    }
    else
    {
        //如果没被初始化过则初始化
        if(textShowDialog == nullptr)
        {
            textShowDialog = new DesktopTextShowDialog(ui->plainTextEdit->toPlainText());
            textShowDialog->show();
        }
        else
        {
            textShowDialog->close();
            textShowDialog = new DesktopTextShowDialog(ui->plainTextEdit->toPlainText());
            textShowDialog->show();
        }

    }

}

void MainWindow::on_pushButton_close_clicked()
{
    if(textShowDialog != nullptr)
    {
        textShowDialog->close();
    }
}
