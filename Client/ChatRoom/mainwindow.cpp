#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _login_dlg = new LoginDialog(this);
    setCentralWidget(_login_dlg);
//    _login_dlg->show();

    // 创建和注册消息链接
    connect(_login_dlg, &LoginDialog::switchRegister, this, &MainWindow::SLOTSwitchReg);
    _regis_dlg = new registerDialog(this);

    // 设置窗口属性
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    _regis_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    _regis_dlg->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
//    if(_login_dlg)
//    {
//        delete _login_dlg;
//        _login_dlg = nullptr;
//    }
//    if(_regis_dlg)
//    {
//        delete _regis_dlg;
//        _regis_dlg = nullptr;
//    }
}

void MainWindow::SLOTSwitchReg()
{
    setCentralWidget(_regis_dlg);
    _login_dlg->hide();
    _regis_dlg->show();
}

