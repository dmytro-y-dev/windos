#ifndef WINDOS_MAINWINDOW_H
#define WINDOS_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindowClass ui;
};

#endif // WINDOS_MAINWINDOW_H
