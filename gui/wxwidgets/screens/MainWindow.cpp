#include "MainWindow.h"
#include "../Application.h"

#include <gui/wxwidgets/components/TextLinkButton.h>
#include <gui/wxwidgets/screens/CategoriesManagerWindow.h>
#include <gui/wxwidgets/screens/TaskEditorWindow.h>

#include <model/entity/task/task.h>
#include <model/entity/category/category.h>

#include <wx/filedlg.h>
#include <wx/utils.h> 

using windos_gui_screens::TaskEditorWindow;
using windos_gui_screens::CategoriesManagerWindow;
using windos_gui_screens::MainWindow;
using windos_gui_components::TextLinkButton;
using windos_gui::wxGetApp;

using todos_model_entity::Task;
using todos_model_entity::Category;
using CategorySmartPtr = todos_model_repository::CategoryRepository::EntitySharedPtr;

enum {
  ID_FILE_NEW = wxID_HIGHEST + 1,
  ID_FILE_OPEN,
  ID_FILE_SAVE_AS,
  ID_FILE_EXIT,

  ID_VIEW_TASKS_SHOW_COMPLETED,
  ID_VIEW_TASKS_SORT_BY_TITLE,
  ID_VIEW_TASKS_SORT_BY_FINISH_DATE,
  ID_VIEW_TASKS_SORT_BY_PUBLICATION_DATE,
  ID_VIEW_TASKS_SORT_ORDER_ASC,
  ID_VIEW_TASKS_SORT_ORDER_DESC,

  ID_TOOLS_SETTINGS,

  ID_HELP_URL_LATEST_SOURCE_CODE,
  ID_HELP_URL_LATEST_RELEASES,
  ID_HELP_ABOUT,

  ID_MANAGE_CATEGORIES,
  ID_CREATE_TASK,
  ID_CHECKBOX_TASKS_SHOW_COMPLETED,
  ID_CHOICE_CATEGORIES,
  ID_CHOICE_SORT_FIELD,
  ID_CHOICE_SORT_ORDER
};

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
  EVT_MENU(ID_FILE_NEW, MainWindow::MenuDatabaseNew)
  EVT_MENU(ID_FILE_OPEN, MainWindow::MenuDatabaseOpen)
  EVT_MENU(ID_FILE_SAVE_AS, MainWindow::MenuDatabaseSaveAs)
  EVT_MENU(ID_FILE_EXIT, MainWindow::MenuDatabaseExit)

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

  EVT_CHECKBOX(ID_CHECKBOX_TASKS_SHOW_COMPLETED, MainWindow::MenuViewTasksShowCompleted)

  EVT_CHOICE(ID_CHOICE_CATEGORIES, MainWindow::ChoiceFilterCategory)
  EVT_CHOICE(ID_CHOICE_SORT_FIELD, MainWindow::ChoiceSortField)
  EVT_CHOICE(ID_CHOICE_SORT_ORDER, MainWindow::ChoiceSortOrder)

  EVT_BUTTON(ID_MANAGE_CATEGORIES, MainWindow::ButtonManageCategories)
  EVT_BUTTON(ID_CREATE_TASK, MainWindow::ButtonCreateTask)
wxEND_EVENT_TABLE()

const int MainWindow::STATUSBAR_PANES_SIZES[] = { 450, 100 };

const int MainWindow::STATUSBAR_PANE_DB_PATH = 0;
const int MainWindow::STATUSBAR_PANE_DB_UNCOMPLETED_TASKS_COUNT = 1;

const wxSize MainWindow::MIN_WINDOW_SIZE(600, 400);

MainWindow::MainWindow() : wxFrame(0, wxID_ANY, _("windos"), wxDefaultPosition, MIN_WINDOW_SIZE),
  m_settingsSort(TaskSortSettings::Field::TITLE, TaskSortSettings::Order::ASC), m_settingsFilter()
{
  m_settingsFilter.SetShowCompleted(true);

  SetSizeHints(MIN_WINDOW_SIZE);
  SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

  InitializeIcon();
  InitializeWidgets();
  InitializeMenubar();
  InitializeStatusbar();

  Centre(wxBOTH);

  EnableTasksView(false);
}

MainWindow::~MainWindow()
{
}

void MainWindow::MenuDatabaseNew(wxCommandEvent& event)
{
  wxFileDialog newFileDialog(this, _("Select path to new database file"), "", "", "Windos database files (*.windos)|*.windos", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

  if (newFileDialog.ShowModal() == wxID_CANCEL) {
    return;
  }

  if (wxGetApp().GetWorkspace().Open(newFileDialog.GetPath().c_str().AsChar())) {
    wxGetApp().GetWorkspace().GetSchema().DestroyTables();
    wxGetApp().GetWorkspace().GetSchema().CreateTables();

    EnableTasksView(true);
  } else {
    EnableTasksView(false);

    wxMessageBox("Failed to create database file.", wxMessageBoxCaptionStr, wxICON_ERROR | wxOK | wxCENTRE, this);
  }

  UpdateWorkspaceStatus();
  UpdateShownCategories();
  UpdateShownTasks();
}

void MainWindow::MenuDatabaseOpen(wxCommandEvent& event)
{
  wxFileDialog openFileDialog(this, _("Open database file"), "", "", "Windos database files (*.windos)|*.windos", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

  if (openFileDialog.ShowModal() == wxID_CANCEL) {
    return;
  }

  if (wxGetApp().GetWorkspace().Open(openFileDialog.GetPath().c_str().AsChar())) {
    EnableTasksView(true);
  } else {
    EnableTasksView(false);

    wxMessageBox("Failed to open selected database file.", wxMessageBoxCaptionStr, wxICON_ERROR | wxOK | wxCENTRE, this);
  }

  UpdateWorkspaceStatus();
  UpdateShownCategories();
  UpdateShownTasks();
}

void MainWindow::MenuDatabaseSaveAs(wxCommandEvent& event)
{
  wxMessageBox("Not yet implemented");
}

void MainWindow::MenuDatabaseExit(wxCommandEvent& event)
{
  Close();
}

void MainWindow::MenuViewTasksShowCompleted(wxCommandEvent & event)
{
  m_settingsFilter.SetShowCompleted(!m_settingsFilter.IsShowCompleted());

  m_checkboxShowCompletedTasks->SetValue(m_settingsFilter.IsShowCompleted());
  m_menuitemShowCompletedTasks->Check(m_settingsFilter.IsShowCompleted());

  UpdateShownTasks();
}

void MainWindow::MenuViewTasksSortByTitle(wxCommandEvent & event)
{
  m_settingsSort.SetField(TaskSortSettings::Field::TITLE);
  m_choiceSortBy->SetSelection(m_choiceSortBy->FindString(_("Title")));

  UpdateShownTasks();
}

void MainWindow::MenuViewTasksSortByFinishDate(wxCommandEvent & event)
{
  m_settingsSort.SetField(TaskSortSettings::Field::DUE_DATE);
  m_choiceSortBy->SetSelection(m_choiceSortBy->FindString(_("Finish date")));

  UpdateShownTasks();
}

void MainWindow::MenuViewTasksSortByPublicationDate(wxCommandEvent & event)
{
  m_settingsSort.SetField(TaskSortSettings::Field::CREATION_DATE);
  m_choiceSortBy->SetSelection(m_choiceSortBy->FindString(_("Publication date")));

  UpdateShownTasks();
}

void MainWindow::MenuViewTasksSortOrderAsc(wxCommandEvent & event)
{
  m_settingsSort.SetOrder(TaskSortSettings::Order::ASC);
  m_choiceOrderBy->SetSelection(m_choiceOrderBy->FindString(_("Ascending")));

  UpdateShownTasks();
}

void MainWindow::MenuViewTasksSortOrderDesc(wxCommandEvent & event)
{
  m_settingsSort.SetOrder(TaskSortSettings::Order::DESC);
  m_choiceOrderBy->SetSelection(m_choiceOrderBy->FindString(_("Descending")));

  UpdateShownTasks();
}

void MainWindow::MenuToolsSettings(wxCommandEvent & event)
{
  wxMessageBox("Not yet implemented");
}

void MainWindow::MenuHelpURLLatestSourceCode(wxCommandEvent & event)
{
  wxLaunchDefaultBrowser("https://github.com/metamaker/windos");
}

void MainWindow::MenuHelpURLLatestReleases(wxCommandEvent & event)
{
  wxLaunchDefaultBrowser("https://github.com/metamaker/windos/releases");
}

void MainWindow::MenuHelpAbout(wxCommandEvent & event)
{
  wxMessageBox("Not yet implemented");
}

void MainWindow::ChoiceFilterCategory(wxCommandEvent &event)
{
  if (m_choiceCategory->GetSelection() > 0) {
    Category* selectedCategory = static_cast<Category*>(m_choiceCategory->GetClientData(m_choiceCategory->GetSelection()));
    m_settingsFilter.SetCategory(selectedCategory->GetName());
    m_settingsFilter.EnableFilterByCategory(true);
  } else {
    m_settingsFilter.EnableFilterByCategory(false);
  }

  UpdateShownTasks();
}

void MainWindow::ChoiceSortField(wxCommandEvent &event)
{
  static std::map<wxString, todos_model_repository::TaskSortSettings::Field> mappingStringToField;

  if (mappingStringToField.empty()) {
    mappingStringToField.insert(std::make_pair("Title", todos_model_repository::TaskSortSettings::Field::TITLE));
    mappingStringToField.insert(std::make_pair("Finish date", todos_model_repository::TaskSortSettings::Field::CREATION_DATE));
    mappingStringToField.insert(std::make_pair("Publication date", todos_model_repository::TaskSortSettings::Field::DUE_DATE));
  }

  if (m_choiceSortBy->GetSelection() > -1) {
    wxString selection = m_choiceSortBy->GetString(m_choiceSortBy->GetSelection());
    m_settingsSort.SetField(mappingStringToField[selection]);
  } else {
    m_settingsSort.SetField(todos_model_repository::TaskSortSettings::Field::NONE);
  }

  UpdateShownTasks();
}

void MainWindow::ChoiceSortOrder(wxCommandEvent &event)
{
  static std::map<wxString, todos_model_repository::TaskSortSettings::Order> mappingStringToOrder;

  if (mappingStringToOrder.empty()) {
    mappingStringToOrder.insert(std::make_pair("Ascending", todos_model_repository::TaskSortSettings::Order::ASC));
    mappingStringToOrder.insert(std::make_pair("Descending", todos_model_repository::TaskSortSettings::Order::DESC));
  }

  if (m_choiceOrderBy->GetSelection() > -1) {
    wxString selection = m_choiceOrderBy->GetString(m_choiceOrderBy->GetSelection());
    m_settingsSort.SetOrder(mappingStringToOrder[selection]);
  } else {
    m_settingsSort.SetOrder(todos_model_repository::TaskSortSettings::Order::NONE);
  }

  UpdateShownTasks();
}

void MainWindow::ButtonManageCategories(wxCommandEvent & event)
{
  CategoriesManagerWindow *categoriesWindow = new CategoriesManagerWindow(this);
  categoriesWindow->ShowModal();

  UpdateShownCategories();
}

void MainWindow::ButtonCreateTask(wxCommandEvent &event)
{
  Task newTask(0, 0, "", Task::Priority::UNKNOWN, Task::DateTime(), Task::DateTime(), Task::DateTime(), Task::Status::UNKNOWN);

  TaskEditorWindow *taskWindow = new TaskEditorWindow(this, newTask);
  taskWindow->ShowModal();

  UpdateShownTasks();
}

void MainWindow::InitializeWidgets()
{
  wxBoxSizer* sizerTasks = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* sizerFilterAndSortSettings = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer* sizerSortSettings = new wxBoxSizer(wxHORIZONTAL);

  wxStaticText* labelSortBy = new wxStaticText(this, wxID_ANY, wxT("Sort by:"), wxDefaultPosition, wxDefaultSize, 0);
  labelSortBy->Wrap(-1);
  sizerSortSettings->Add(labelSortBy, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  wxArrayString m_choiceSortByChoices;
  m_choiceSortByChoices.Add(_("Title"));
  m_choiceSortByChoices.Add(_("Finish date"));
  m_choiceSortByChoices.Add(_("Publication date"));
  m_choiceSortBy = new wxChoice(this, ID_CHOICE_SORT_FIELD, wxDefaultPosition, wxDefaultSize, m_choiceSortByChoices, 0);
  m_choiceSortBy->SetSelection(0);
  sizerSortSettings->Add(m_choiceSortBy, 0, wxALIGN_CENTER_VERTICAL, 5);

  wxStaticText* labelSortOrder = new wxStaticText(this, wxID_ANY, wxT("Order:"), wxDefaultPosition, wxDefaultSize, 0);
  labelSortOrder->Wrap(-1);
  sizerSortSettings->Add(labelSortOrder, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  wxArrayString m_choiceOrderByChoices;
  m_choiceOrderByChoices.Add(_("Ascending"));
  m_choiceOrderByChoices.Add(_("Descending"));
  m_choiceOrderBy = new wxChoice(this, ID_CHOICE_SORT_ORDER, wxDefaultPosition, wxDefaultSize, m_choiceOrderByChoices, 0);
  m_choiceOrderBy->SetSelection(0);
  sizerSortSettings->Add(m_choiceOrderBy, 0, wxALIGN_CENTER_VERTICAL, 5);

  wxBoxSizer* sizerFilterSettings = new wxBoxSizer(wxHORIZONTAL);

  wxStaticText* labelFilterCategory = new wxStaticText(this, wxID_ANY, wxT("Category:"), wxDefaultPosition, wxDefaultSize, 0);
  labelFilterCategory->Wrap(-1);
  sizerFilterSettings->Add(labelFilterCategory, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  wxArrayString m_choiceCategoryChoices;
  m_choiceCategory = new wxChoice(this, ID_CHOICE_CATEGORIES, wxDefaultPosition, wxDefaultSize, m_choiceCategoryChoices, 0);
  m_choiceCategory->SetSelection(0);
  sizerFilterSettings->Add(m_choiceCategory, 0, wxALIGN_CENTER_VERTICAL, 5);

  TextLinkButton* btnCategoriesEditor = new TextLinkButton(this, ID_MANAGE_CATEGORIES, wxT("Manage..."), wxDefaultPosition, wxDefaultSize, 0);
  sizerFilterSettings->Add(btnCategoriesEditor, 0, wxALIGN_CENTER_VERTICAL, 5);

  sizerFilterAndSortSettings->Add(sizerSortSettings, 1, wxALIGN_CENTER_VERTICAL, 5);
  sizerFilterAndSortSettings->Add(sizerFilterSettings, 0, wxALIGN_CENTER_VERTICAL, 5);

  sizerTasks->Add(sizerFilterAndSortSettings, 0, wxALL | wxEXPAND, 5);

  m_searchBoxTask = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
  sizerTasks->Add(m_searchBoxTask, 0, wxALL | wxEXPAND, 5);

  m_listTasks = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_ALWAYS_SB | wxLB_SINGLE);
  sizerTasks->Add(m_listTasks, 1, wxALL | wxEXPAND, 5);

  wxBoxSizer* sizerTasksActions = new wxBoxSizer(wxHORIZONTAL);

  m_checkboxShowCompletedTasks = new wxCheckBox(this, ID_CHECKBOX_TASKS_SHOW_COMPLETED, wxT("Show completed tasks"), wxDefaultPosition, wxDefaultSize, 0);
  m_checkboxShowCompletedTasks->SetValue(m_settingsFilter.IsShowCompleted());
  sizerTasksActions->Add(m_checkboxShowCompletedTasks, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  TextLinkButton* btnCreateNewTask = new TextLinkButton(this, ID_CREATE_TASK, wxT("Create new task..."), wxDefaultPosition, wxDefaultSize, 0);
  sizerTasksActions->Add(btnCreateNewTask, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  sizerTasks->Add(sizerTasksActions, 0, wxEXPAND, 5);

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
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(ID_FILE_NEW, _("&New"));
  menuFile->AppendSeparator();
  menuFile->Append(ID_FILE_OPEN, _("&Open...\tCtrl+O"));
  menuFile->Append(ID_FILE_SAVE_AS, _("S&ave as...\tCtrl+S"));
  menuFile->AppendSeparator();
  menuFile->Append(ID_FILE_EXIT, _("E&xit"));

  wxMenu *menuViewTasksSortBy = new wxMenu;
  m_menuitemSortByTitle = menuViewTasksSortBy->AppendRadioItem(ID_VIEW_TASKS_SORT_BY_TITLE, _("&Title"));
  m_menuitemSortByFinishDate = menuViewTasksSortBy->AppendRadioItem(ID_VIEW_TASKS_SORT_BY_FINISH_DATE, _("&Finish date"));
  m_menuitemSortByPublicationDate = menuViewTasksSortBy->AppendRadioItem(ID_VIEW_TASKS_SORT_BY_PUBLICATION_DATE, _("&Publication date"));

  wxMenu *menuViewTasksSortOrder = new wxMenu;
  m_menuitemSortOrderAscending = menuViewTasksSortOrder->AppendRadioItem(ID_VIEW_TASKS_SORT_ORDER_ASC, _("&Ascending"));
  m_menuitemSortOrderDescending = menuViewTasksSortOrder->AppendRadioItem(ID_VIEW_TASKS_SORT_ORDER_DESC, _("&Descending"));

  wxMenu *menuView = new wxMenu;
  m_menuitemShowCompletedTasks = menuView->AppendCheckItem(ID_VIEW_TASKS_SHOW_COMPLETED, _("&Show completed tasks"));
  m_menuitemShowCompletedTasks->Check(m_settingsFilter.IsShowCompleted());
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
  menuBar->Append(menuFile, _("&File"));
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

void MainWindow::EnableTasksView(bool enable)
{
  EnableSizer(this->GetSizer(), enable);
  Refresh();
}

void MainWindow::EnableSizer(wxSizer* sizer, bool enable)
{
  wxSizerItemList sizerChildren = sizer->GetChildren();

  for (int i = 0, iend = sizerChildren.size(); i != iend; ++i) {
    if (sizerChildren[i]->IsWindow()) {
      sizerChildren[i]->GetWindow()->Enable(enable);
    } else if (sizerChildren[i]->IsSizer()) {
      EnableSizer(sizerChildren[i]->GetSizer(), enable);
    }
  }
}

void MainWindow::UpdateWorkspaceStatus()
{
  GetStatusBar()->SetStatusText(wxGetApp().GetWorkspace().GetLocation(), STATUSBAR_PANE_DB_PATH);

  if (wxGetApp().GetWorkspace().IsReady()) {
    GetStatusBar()->SetStatusText(wxString::Format("Uncompleted: %d", wxGetApp().GetWorkspace().GetTaskRepository().CountUncompletedTasks()), STATUSBAR_PANE_DB_UNCOMPLETED_TASKS_COUNT);
  }
}

void MainWindow::UpdateShownCategories()
{
  static std::vector<CategorySmartPtr> categories;

  unsigned long selectedCategoryId;
  if (m_choiceCategory->GetSelection() > 0) {
    Category* selectedCategory = static_cast<Category*>(m_choiceCategory->GetClientData(m_choiceCategory->GetSelection()));
    selectedCategoryId = selectedCategory->GetId();
  } else {
    selectedCategoryId = -1;
  }

  categories = wxGetApp().GetWorkspace().GetCategoryRepository().FindAll();

  m_choiceCategory->Freeze();

  m_choiceCategory->Clear();
  m_choiceCategory->Append(_T("<All>"), (void*)nullptr);
  m_choiceCategory->SetSelection(0);

  for (auto categoryPtr : categories) {
    m_choiceCategory->Append(categoryPtr->GetName(), categoryPtr.get());

    if (selectedCategoryId != -1 && categoryPtr->GetId() == selectedCategoryId) {
      m_choiceCategory->SetSelection(m_choiceCategory->GetCount() - 1);
    }
  }

  m_choiceCategory->Thaw();
}

void MainWindow::UpdateShownTasks()
{
  static std::vector<todos_model_repository::TaskRepository::EntitySharedPtr> tasks;
  tasks = wxGetApp().GetWorkspace().GetTaskRepository().FindAll(m_settingsSort, m_settingsFilter);

  m_listTasks->Freeze();
  m_listTasks->Clear();

  for (auto taskPtr : tasks) {
    m_listTasks->Append(wxString::Format("[Priority %d] ", taskPtr->GetPriority()) + taskPtr->GetTitle(), taskPtr.get());
  }

  m_listTasks->Thaw();
}
