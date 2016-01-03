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
  SetBackgroundColour(wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ));

  InitializeIcon();
  InitializeWidgets();
  InitializeMenubar();
  InitializeStatusbar();

  Centre(wxBOTH);
}

MainWindow::~MainWindow()
{
}

void MainWindow::InitializeWidgets()
{
  wxBoxSizer* sizerTasks;
  sizerTasks = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* sizerFilterAndSortSettings;
  sizerFilterAndSortSettings = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer* sizerFilterSettings;
  sizerFilterSettings = new wxBoxSizer(wxHORIZONTAL);

  wxStaticText* labelFilterCategory = new wxStaticText(this, wxID_ANY, wxT("Category:"), wxDefaultPosition, wxDefaultSize, 0);
  labelFilterCategory->Wrap(-1);
  sizerFilterSettings->Add(labelFilterCategory, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  wxArrayString m_choiceCategoryChoices;
  m_choiceCategory = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceCategoryChoices, 0);
  m_choiceCategory->SetSelection(0);
  sizerFilterSettings->Add(m_choiceCategory, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  wxStaticText* btnCategoriesEditor = new wxStaticText(this, wxID_ANY, wxT("Edit..."), wxDefaultPosition, wxDefaultSize, 0);
  btnCategoriesEditor->Wrap(-1);
  btnCategoriesEditor->SetForegroundColour(wxColour(4, 74, 104));

  sizerFilterSettings->Add(btnCategoriesEditor, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  sizerFilterAndSortSettings->Add(sizerFilterSettings, 1, wxEXPAND, 5);

  wxBoxSizer* sizerSortSettings;
  sizerSortSettings = new wxBoxSizer(wxHORIZONTAL);

  wxStaticText* labelSortBy = new wxStaticText(this, wxID_ANY, wxT("Sort by:"), wxDefaultPosition, wxDefaultSize, 0);
  labelSortBy->Wrap(-1);
  sizerSortSettings->Add(labelSortBy, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  wxArrayString m_choiceSortByChoices;
  m_choiceSortByChoices.Add(_("Title"));
  m_choiceSortByChoices.Add(_("Finish date"));
  m_choiceSortByChoices.Add(_("Publication date"));
  m_choiceSortBy = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSortByChoices, 0);
  m_choiceSortBy->SetSelection(0);
  sizerSortSettings->Add(m_choiceSortBy, 0, wxALIGN_CENTER_VERTICAL, 5);

  wxStaticText* labelSortOrder = new wxStaticText(this, wxID_ANY, wxT("Order:"), wxDefaultPosition, wxDefaultSize, 0);
  labelSortOrder->Wrap(-1);
  sizerSortSettings->Add(labelSortOrder, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  wxArrayString m_choiceOrderByChoices;
  m_choiceOrderByChoices.Add(_("Ascending"));
  m_choiceOrderByChoices.Add(_("Descending"));
  m_choiceOrderBy = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceOrderByChoices, 0);
  m_choiceOrderBy->SetSelection(0);
  sizerSortSettings->Add(m_choiceOrderBy, 0, wxALIGN_CENTER_VERTICAL, 5);

  sizerFilterAndSortSettings->Add(sizerSortSettings, 0, wxALIGN_CENTER_VERTICAL, 5);

  sizerTasks->Add(sizerFilterAndSortSettings, 0, wxALL | wxEXPAND, 5);

  m_searchBoxTask = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
  sizerTasks->Add(m_searchBoxTask, 0, wxALL | wxEXPAND, 5);

  m_listTasks = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_ALWAYS_SB | wxLB_SINGLE); 
  sizerTasks->Add(m_listTasks, 1, wxALL | wxEXPAND, 5);

  wxBoxSizer* sizerTasksActions;
  sizerTasksActions = new wxBoxSizer(wxHORIZONTAL);

  wxStaticText* btnCreateNewTask = new wxStaticText(this, wxID_ANY, wxT("+ Create new task"), wxDefaultPosition, wxDefaultSize, 0);
  btnCreateNewTask->Wrap(-1);
  btnCreateNewTask->SetForegroundColour(wxColour(4, 74, 104));

  sizerTasksActions->Add(btnCreateNewTask, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
  sizerTasks->Add(sizerTasksActions, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

  SetSizer(sizerTasks);
  Layout();
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
