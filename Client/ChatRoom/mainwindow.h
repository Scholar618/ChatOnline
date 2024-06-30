#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include "registerdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void SLOTSwitchReg();

private:
    Ui::MainWindow *ui;
    LoginDialog *_login_dlg;
    registerDialog *_regis_dlg;
};
#endif // MAINWINDOW_H
