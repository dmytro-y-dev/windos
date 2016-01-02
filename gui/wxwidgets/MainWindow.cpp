#include "MainWindow.h"

using windos_gui::MainWindow;

enum {
  ID_DATABASE_NEW = wxID_HIGHEST + 1,
  ID_DATABASE_OPEN,
  ID_DATABASE_SAVE,
  ID_DATABASE_SAVE_AS,
  ID_DATABASE_EXIT,

  ID_VIEW_TASKS_SHOW_COMPLETED,
  ID_VIEW_TASKS_SORT_BY_TITLE,
  ID_VIEW_TASKS_SORT_BY_FINISH_DATE,
  ID_VIEW_TASKS_SORT_BY_PUBLICATION_DATE,
  ID_VIEW_TASKS_SORT_ORDER_ASC,
  ID_VIEW_TASKS_SORT_ORDER_DESC,

  ID_TOOLS_SETTINGS,

  ID_HELP_URL_LATEST_SOURCE_CODE,
  ID_HELP_URL_LATEST_RELEASES,
  ID_HELP_ABOUT
};

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
  EVT_MENU(ID_DATABASE_NEW, MainWindow::MenuDatabaseNew)
  EVT_MENU(ID_DATABASE_OPEN, MainWindow::MenuDatabaseOpen)
  EVT_MENU(ID_DATABASE_SAVE, MainWindow::MenuDatabaseSave)
  EVT_MENU(ID_DATABASE_SAVE_AS, MainWindow::MenuDatabaseSaveAs)
  EVT_MENU(ID_DATABASE_EXIT, MainWindow::MenuDatabaseExit)

  EVT_MENU(ID_VIEW_TASKS_SHOW_COMPLETED, MainWindow::MenuViewTasksShowCompleted)
  EVT_MENU(ID_VIEW_TASKS_SORT_BY_TITLE, MainWindow::MenuViewTasksSortByTitle)
  EVT_MENU(ID_VIEW_TASKS_SORT_BY_FINISH_DATE, MainWindow::MenuViewTasksSortByFinishDate)
  EVT_MENU(ID_VIEW_TASKS_SORT_BY_PUBLICATION_DATE, MainWindow::MenuViewTasksSortByPublicationDate)
  EVT_MENU(ID_VIEW_TASKS_SORT_ORDER_ASC, MainWindow::MenuViewTasksSortOrderAsc)
  EVT_MENU(ID_VIEW_TASKS_SORT_ORDER_DESC, MainWindow::MenuViewTasksSortOrderDesc)

  EVT_MENU(ID_TOOLS_SETTINGS, MainWindow::MenuToolsSettings)

  EVT_MENU(ID_HELP_URL_LATEST_SOURCE_CODE, MainWindow::MenuHelpURLLatestSourceCode)
  EVT_MENU(ID_HELP_URL_LATEST_RELEASES, MainWindow::MenuHelpURLLatestReleases)
  EVT_MENU(ID_HELP_ABOUT, MainWindow::MenuHelpAbout)
wxEND_EVENT_TABLE()

const int MainWindow::STATUSBAR_PANES_SIZES[] = {200, 10};

const int MainWindow::STATUSBAR_PANE_DB_PATH = 0;
const int MainWindow::STATUSBAR_PANE_DB_ISMODIFIED = 1;

const wxSize MainWindow::MIN_WINDOW_SIZE(600, 400);

MainWindow::MainWindow() : wxFrame(0, wxID_ANY, _("windos"), wxDefaultPosition, MIN_WINDOW_SIZE)
{
  SetSizeHints(MIN_WINDOW_SIZE);

  InitializeIcon();
  InitializeWidgets();
  InitializeMenubar();
  InitializeStatusbar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::InitializeWidgets()
{
}

void MainWindow::InitializeIcon()
{
  wxIcon icon("ICON_APP", wxICON_DEFAULT_TYPE, 16, 16);
  SetIcon(icon);
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
  menuViewTasksSortBy->AppendRadioItem(ID_VIEW_TASKS_SORT_BY_TITLE, _("&Title"));
  menuViewTasksSortBy->AppendRadioItem(ID_VIEW_TASKS_SORT_BY_FINISH_DATE, _("&Finish date"));
  menuViewTasksSortBy->AppendRadioItem(ID_VIEW_TASKS_SORT_BY_PUBLICATION_DATE, _("&Publication date"));

  wxMenu *menuViewTasksSortOrder = new wxMenu;
  menuViewTasksSortOrder->AppendRadioItem(ID_VIEW_TASKS_SORT_ORDER_ASC, _("&Ascending"));
  menuViewTasksSortOrder->AppendRadioItem(ID_VIEW_TASKS_SORT_ORDER_DESC, _("&Descending"));

  wxMenu *menuView = new wxMenu;
  menuView->AppendCheckItem(ID_VIEW_TASKS_SHOW_COMPLETED, _("&Show completed tasks"));
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

void MainWindow::InitializeStatusbar()
{
  CreateStatusBar(sizeof(STATUSBAR_PANES_SIZES) / sizeof(int), wxSTB_DEFAULT_STYLE);
  SetStatusWidths(sizeof(STATUSBAR_PANES_SIZES) / sizeof(int), STATUSBAR_PANES_SIZES);

  SetStatusBarPane(-1);
}

void MainWindow::MenuDatabaseNew(wxCommandEvent & event)
{
}

void MainWindow::MenuDatabaseOpen(wxCommandEvent & event)
{
}

void MainWindow::MenuDatabaseSave(wxCommandEvent & event)
{
}

void MainWindow::MenuDatabaseSaveAs(wxCommandEvent & event)
{
}

void MainWindow::MenuDatabaseExit(wxCommandEvent & event)
{
  Close();
}

void MainWindow::MenuViewTasksShowCompleted(wxCommandEvent & event)
{
}

void MainWindow::MenuViewTasksSortByTitle(wxCommandEvent & event)
{
}

void MainWindow::MenuViewTasksSortByFinishDate(wxCommandEvent & event)
{
}

void MainWindow::MenuViewTasksSortByPublicationDate(wxCommandEvent & event)
{
}

void MainWindow::MenuViewTasksSortOrderAsc(wxCommandEvent & event)
{
}

void MainWindow::MenuViewTasksSortOrderDesc(wxCommandEvent & event)
{
}

void MainWindow::MenuToolsSettings(wxCommandEvent & event)
{
}

void MainWindow::MenuHelpURLLatestSourceCode(wxCommandEvent & event)
{
}

void MainWindow::MenuHelpURLLatestReleases(wxCommandEvent & event)
{
}

void MainWindow::MenuHelpAbout(wxCommandEvent & event)
{
}
