#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "desktoptextshowdialog.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    DesktopTextShowDialog * textShowDialog = nullptr;

private slots:
    void on_pushButton_begin_clicked();
    void on_pushButton_close_clicked();

private:
    Ui::MainWindow *ui;
    QString needWriteStr = "";
    int settingFontColor_R = 0;
    int settingFontColor_G = 0;
    int settingFontColor_B = 0;
    int setTransparency = 255;
    int setRollSpeed = 4;
    int setTextShowWidth = 800;
    int setTextShowHeight = 80;
};
#endif // MAINWINDOW_H
