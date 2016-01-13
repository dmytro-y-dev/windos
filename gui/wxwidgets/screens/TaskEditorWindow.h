#ifndef WINDOS_GUI_SCREENS_TASKEDITORWINDOW_H
#define WINDOS_GUI_SCREENS_TASKEDITORWINDOW_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/calctrl.h>

#include <model/entity/task/Task.h>

namespace windos_gui_screens {
  class TaskEditorWindow: public wxDialog
  {
  private:
    typedef todos_model_entity::Task Task;

  public:
    TaskEditorWindow(wxWindow* parent, Task& attachedTask);
    ~TaskEditorWindow();

  private:
    static const wxSize MIN_WINDOW_SIZE;

    Task& m_attachedTask;

    wxTextCtrl* m_editTitle;
    wxChoice* m_choiceCategory;
    wxChoice* m_choicePriority;
    wxCheckBox* m_checkboxRemindAboutEvent;
    wxCheckBox* m_checkboxCompleted;
    wxCalendarCtrl* m_calendarDueDate;
    wxCalendarCtrl* m_calendarReminderDate;
    wxTextCtrl* m_listCommentaries;
    wxTextCtrl* m_editCommentary;
    wxButton* m_buttonSaveTask;

  private:
    wxDECLARE_EVENT_TABLE();

    void InitializeWidgets();
  };
}


#endif //WINDOS_GUI_SCREENS_TASKEDITORWINDOW_H