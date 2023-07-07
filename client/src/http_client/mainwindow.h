//
// Created by osia on 26.06.23.
//

#ifndef HTTP_CLIENT_MAINWINDOW_H
#define HTTP_CLIENT_MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QLayout>
#include <QLabel>
#include <iostream>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QWidget* mainWidget;
    QGridLayout* gridLayout;
    QLineEdit* fioEntry;
    QLineEdit* yearEntry{};
    QLineEdit* courseNumEntry{};
    QLineEdit* groupEntry{};
    QPushButton* pushButton{};
};


#endif //HTTP_CLIENT_MAINWINDOW_H
