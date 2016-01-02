#include "MainWindow.h"

using windos_gui::MainWindow;

enum {
  ID_DATABASE_EXIT = wxID_EXIT,
  ID_HELP_ABOUT = wxID_ABOUT,

  ID_DATABASE_NEW = wxID_HIGHEST + 1,
  ID_DATABASE_OPEN,
  ID_DATABASE_SAVE,
  ID_DATABASE_SAVE_AS,

  ID_VIEW_TASKS_SHOW_COMPLETED,
  ID_VIEW_TASKS_SORT_BY_TITLE,
  ID_VIEW_TASKS_SORT_BY_FINISH_DATE,
  ID_VIEW_TASKS_SORT_BY_PUBLICATION_DATE,
  ID_VIEW_TASKS_SORT_ORDER_ASC,
  ID_VIEW_TASKS_SORT_ORDER_DESC,

  ID_TOOLS_SETTINGS,

  ID_HELP_URL_LATEST_SOURCE_CODE,
  ID_HELP_URL_LATEST_RELEASES
};

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(0, wxID_ANY, _("windos"), wxDefaultPosition, wxDefaultSize)
{
  InitializeMenubar();

  //wxIcon icon("ICON_APP", wxICON_DEFAULT_TYPE, 16, 16);
  //this->SetIcon(icon);

  // Configure status bar

  this->CreateStatusBar(5, wxSTB_DEFAULT_STYLE);

  int statusWidths[] = {120, 75, 10, 150, 550};
  this->SetStatusWidths(5, statusWidths);

  this->SetStatusBarPane(-1);
}

MainWindow::~MainWindow()
{
}

void MainWindow::InitializeMenubar()
{
  wxMenu *menuDatabase = new wxMenu;
  menuDatabase->Append(ID_DATABASE_NEW, _("&New"));
  menuDatabase->AppendSeparator();
  menuDatabase->Append(ID_DATABASE_OPEN, _("&Open...\tCtrl+O"));
  menuDatabase->Append(ID_DATABASE_SAVE, _("&Save changes\tCtrl+S"));
  menuDatabase->Append(ID_DATABASE_SAVE_AS, _("S&ave as..."));
  menuDatabase->AppendSeparator();
  menuDatabase->Append(ID_DATABASE_EXIT, _("E&xit"));

  wxMenu *menuViewTasksSortBy = new wxMenu;
  menuViewTasksSortBy->Append(ID_VIEW_TASKS_SORT_BY_TITLE, _("&Title"));
  menuViewTasksSortBy->Append(ID_VIEW_TASKS_SORT_BY_FINISH_DATE, _("&Finish date"));
  menuViewTasksSortBy->Append(ID_VIEW_TASKS_SORT_BY_PUBLICATION_DATE, _("&Publication date"));

  wxMenu *menuViewTasksSortOrder = new wxMenu;
  menuViewTasksSortOrder->Append(ID_VIEW_TASKS_SORT_ORDER_ASC, _("&Ascending"));
  menuViewTasksSortOrder->Append(ID_VIEW_TASKS_SORT_ORDER_DESC, _("&Descending"));

  wxMenu *menuView = new wxMenu;
  menuView->Append(ID_VIEW_TASKS_SHOW_COMPLETED, _("&Show completed tasks"));
  menuView->AppendSeparator();
  menuView->AppendSubMenu(menuViewTasksSortBy, _("Sort tasks &by"));
  menuView->AppendSubMenu(menuViewTasksSortOrder, _("Sort tasks &order"));

  wxMenu *menuTools = new wxMenu;
  menuTools->Append(ID_TOOLS_SETTINGS, _("&Settings..."));

  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(ID_HELP_URL_LATEST_RELEASES, _("&Latest application releases on GitHub"));
  menuHelp->Append(ID_HELP_URL_LATEST_SOURCE_CODE, _("&Latest application source code on GitHub"));
  menuHelp->AppendSeparator();
  menuHelp->Append(ID_HELP_ABOUT, _("&About...\tF1"));

  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuDatabase, _("&Database"));
  menuBar->Append(menuView, _("&View"));
  menuBar->Append(menuTools, _("&Tools"));
  menuBar->Append(menuHelp, _("&Help"));

  SetMenuBar(menuBar);
}