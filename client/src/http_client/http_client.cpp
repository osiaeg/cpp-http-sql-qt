//
// Created by osia on 23.06.23.
//
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return QApplication::exec();
}
