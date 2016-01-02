#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  m_ui.setupUi(this);

  QActionGroup* sortOrderGroup = new QActionGroup(this);
  sortOrderGroup->addAction(m_ui.actionAscending);
  sortOrderGroup->addAction(m_ui.actionDescending);

  QActionGroup* sortByGroup = new QActionGroup(this);
  sortOrderGroup->addAction(m_ui.actionPublicationDate);
  sortOrderGroup->addAction(m_ui.actionFinishDate);
  sortOrderGroup->addAction(m_ui.actionTitle);
}

MainWindow::~MainWindow()
{
}
