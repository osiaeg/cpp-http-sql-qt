//
// Created by osia on 26.06.23.
//

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QString title{"Http Client"};
    this->setWindowTitle(title);

    mainWidget = new QWidget(this);
    gridLayout = new QGridLayout(mainWidget);

    gridLayout->addWidget(new QLabel("ФИО: "), 0, 0);
    fioEntry = new QLineEdit(mainWidget);
    gridLayout->addWidget(fioEntry, 0, 1);

    gridLayout->addWidget(new QLabel("Год рождения: "), 1, 0);
    yearEntry = new QLineEdit(mainWidget);
    gridLayout->addWidget(yearEntry, 1, 1);

    gridLayout->addWidget(new QLabel("Номер курса: "), 2, 0);
    courseNumEntry = new QLineEdit(mainWidget);
    gridLayout->addWidget(courseNumEntry, 2, 1);

    gridLayout->addWidget(new QLabel("Название группы: "), 3, 0);
    groupEntry = new QLineEdit(mainWidget);
    gridLayout->addWidget(groupEntry, 3, 1);

    pushButton = new QPushButton("Добавить", mainWidget);
    gridLayout->addWidget(pushButton, 4, 0);

    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow() {
    delete mainWidget;
    delete gridLayout;
    delete fioEntry;
    delete yearEntry;
    delete courseNumEntry;
    delete groupEntry;
}