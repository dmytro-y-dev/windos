#ifndef WINDOS_MAINWINDOW_H
#define WINDOS_MAINWINDOW_H

#include <QtWidgets/QMainWindow>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
private:
  typedef Ui::MainWindowClass MainWindowUI;

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  MainWindowUI m_ui;
};

#endif // WINDOS_MAINWINDOW_H
