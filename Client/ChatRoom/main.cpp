#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/style/stylesheet.qss");
    if(qss.open(QFile::ReadOnly))
    {
        qDebug("open success!");
        QString style = QLatin1String(qss.readAll());// 转换QString
        a.setStyleSheet(style);
        qss.close();
    }
    else
    {
        qDebug("open failed!");
    }
    MainWindow w;
    w.show();
    return a.exec();
}
