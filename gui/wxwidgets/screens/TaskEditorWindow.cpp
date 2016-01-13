#include "TaskEditorWindow.h"

using windos_gui_screens::TaskEditorWindow;

wxBEGIN_EVENT_TABLE(TaskEditorWindow, wxDialog)
wxEND_EVENT_TABLE()

const wxSize TaskEditorWindow::MIN_WINDOW_SIZE(700, 500);

TaskEditorWindow::TaskEditorWindow(wxWindow* parent, Task& attachedTask) : wxDialog(parent, wxID_ANY, _("Task properties"), wxDefaultPosition, MIN_WINDOW_SIZE, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER), m_attachedTask(attachedTask)
{
  SetSizeHints(MIN_WINDOW_SIZE);
  SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

  InitializeWidgets();

  Centre(wxBOTH);
}

TaskEditorWindow::~TaskEditorWindow()
{
}

void TaskEditorWindow::InitializeWidgets()
{
  wxBoxSizer* sizerTask;
  sizerTask = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* sizerTaskProperties;
  sizerTaskProperties = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* sizerTitle;
  sizerTitle = new wxBoxSizer(wxHORIZONTAL);

  wxStaticText* labelTitle = new wxStaticText(this, wxID_ANY, wxT("Title:"), wxDefaultPosition, wxDefaultSize, 0);
  labelTitle->Wrap(-1);
  sizerTitle->Add(labelTitle, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  m_editTitle = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
  sizerTitle->Add(m_editTitle, 1, wxALL | wxEXPAND, 5);

  m_buttonSaveTask = new wxButton(this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0);
  sizerTitle->Add(m_buttonSaveTask, 0, wxALL, 5);

  sizerTaskProperties->Add(sizerTitle, 0, wxEXPAND, 5);

  wxBoxSizer* sizerTaskSpecificProperties;
  sizerTaskSpecificProperties = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer* sizerTaskCoreProperties;
  sizerTaskCoreProperties = new wxBoxSizer(wxVERTICAL);

  wxStaticText* labelCategory = new wxStaticText(this, wxID_ANY, wxT("Category:"), wxDefaultPosition, wxDefaultSize, 0);
  labelCategory->Wrap(-1);
  sizerTaskCoreProperties->Add(labelCategory, 0, wxALL, 5);

  wxArrayString m_choiceCategoryChoices;
  m_choiceCategory = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceCategoryChoices, 0);
  m_choiceCategory->SetSelection(0);
  sizerTaskCoreProperties->Add(m_choiceCategory, 0, wxALL | wxEXPAND, 5);

  wxStaticText* labelPriority = new wxStaticText(this, wxID_ANY, wxT("Priority:"), wxDefaultPosition, wxDefaultSize, 0);
  labelPriority->Wrap(-1);
  sizerTaskCoreProperties->Add(labelPriority, 0, wxALL, 5);

  wxArrayString m_choicePriorityChoices;
  m_choicePriority = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choicePriorityChoices, 0);
  m_choicePriority->SetSelection(0);
  sizerTaskCoreProperties->Add(m_choicePriority, 0, wxALL, 5);

  m_checkboxRemindAboutEvent = new wxCheckBox(this, wxID_ANY, wxT("Remind about task"), wxDefaultPosition, wxDefaultSize, 0);
  sizerTaskCoreProperties->Add(m_checkboxRemindAboutEvent, 0, wxALL, 5);

  m_checkboxCompleted = new wxCheckBox(this, wxID_ANY, wxT("Task is completed"), wxDefaultPosition, wxDefaultSize, 0);
  sizerTaskCoreProperties->Add(m_checkboxCompleted, 0, wxALL, 5);

  sizerTaskSpecificProperties->Add(sizerTaskCoreProperties, 1, wxEXPAND, 5);

  wxBoxSizer* sizerTaskDueDate;
  sizerTaskDueDate = new wxBoxSizer(wxVERTICAL);

  wxStaticText* labelDueDate = new wxStaticText(this, wxID_ANY, wxT("Due date:"), wxDefaultPosition, wxDefaultSize, 0);
  labelDueDate->Wrap(-1);
  sizerTaskDueDate->Add(labelDueDate, 0, wxALL, 5);

  m_calendarDueDate = new wxCalendarCtrl(this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SHOW_HOLIDAYS);
  sizerTaskDueDate->Add(m_calendarDueDate, 0, wxALL, 5);


  sizerTaskSpecificProperties->Add(sizerTaskDueDate, 0, wxEXPAND, 5);

  wxBoxSizer* sizerTaskReminderDate;
  sizerTaskReminderDate = new wxBoxSizer(wxVERTICAL);

  wxStaticText* labelReminderDate = new wxStaticText(this, wxID_ANY, wxT("Reminder date:"), wxDefaultPosition, wxDefaultSize, 0);
  labelReminderDate->Wrap(-1);
  sizerTaskReminderDate->Add(labelReminderDate, 0, wxALL, 5);

  m_calendarReminderDate = new wxCalendarCtrl(this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SHOW_HOLIDAYS);
  sizerTaskReminderDate->Add(m_calendarReminderDate, 0, wxALL, 5);

  sizerTaskSpecificProperties->Add(sizerTaskReminderDate, 0, wxEXPAND, 5);
  sizerTaskProperties->Add(sizerTaskSpecificProperties, 0, wxEXPAND, 5);

  sizerTask->Add(sizerTaskProperties, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

  wxBoxSizer* sizerCommentaries;
  sizerCommentaries = new wxBoxSizer(wxVERTICAL);

  m_listCommentaries = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
  sizerCommentaries->Add(m_listCommentaries, 2, wxALL | wxEXPAND, 5);

  wxBoxSizer* sizerCommentariesEditor;
  sizerCommentariesEditor = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* sizerCommentariesActions;
  sizerCommentariesActions = new wxBoxSizer(wxHORIZONTAL);

  wxButton* buttonSend = new wxButton(this, wxID_ANY, wxT("Send (Ctrl+Enter)"), wxDefaultPosition, wxDefaultSize, 0);
  sizerCommentariesActions->Add(buttonSend, 1, wxALL | wxEXPAND, 5);

  wxButton* buttonAttachFile = new wxButton(this, wxID_ANY, wxT("Attach file"), wxDefaultPosition, wxDefaultSize, 0);
  sizerCommentariesActions->Add(buttonAttachFile, 0, wxALL, 5);

  m_editCommentary = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
  sizerCommentariesEditor->Add(m_editCommentary, 1, wxALL | wxEXPAND, 5);

  sizerCommentariesEditor->Add(sizerCommentariesActions, 0, wxEXPAND, 5);

  sizerCommentaries->Add(sizerCommentariesEditor, 1, wxEXPAND, 5);

  sizerTask->Add(sizerCommentaries, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);

  this->SetSizer(sizerTask);
  this->Layout();
}

