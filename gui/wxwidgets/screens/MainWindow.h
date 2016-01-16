#ifndef WINDOS_GUI_SCREENS_MAINWINDOW_H
#define WINDOS_GUI_SCREENS_MAINWINDOW_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <model/repository/task/TaskFilterSettings.h>
#include <model/repository/task/TaskSortSettings.h>

namespace windos_gui_screens {
  class MainWindow: public wxFrame
  {
  public:
    MainWindow();
    ~MainWindow();

  private:
    typedef todos_model_repository::TaskFilterSettings TaskFilterSettings;
    typedef todos_model_repository::TaskSortSettings TaskSortSettings;

  private:
    static const int STATUSBAR_PANES_SIZES[];

    static const int STATUSBAR_PANE_DB_PATH;
    static const int STATUSBAR_PANE_DB_UNCOMPLETED_TASKS_COUNT;

    static const wxSize MIN_WINDOW_SIZE;

    wxCheckBox* m_checkboxShowCompletedTasks;
    wxMenuItem* m_menuitemShowCompletedTasks;
    wxMenuItem* m_menuitemSortByTitle;
    wxMenuItem* m_menuitemSortByFinishDate;
    wxMenuItem* m_menuitemSortByPublicationDate;
    wxMenuItem* m_menuitemSortOrderAscending;
    wxMenuItem* m_menuitemSortOrderDescending;

    wxChoice* m_choiceCategory;
    wxChoice* m_choiceSortBy;
    wxChoice* m_choiceOrderBy;
    wxTextCtrl* m_searchBoxTask;
    wxListBox* m_listTasks;

    TaskFilterSettings m_settingsFilter;
    TaskSortSettings m_settingsSort;

  private:
    wxDECLARE_EVENT_TABLE();

    void MenuDatabaseNew(wxCommandEvent &event);
    void MenuDatabaseOpen(wxCommandEvent &event);
    void MenuDatabaseSave(wxCommandEvent &event);
    void MenuDatabaseSaveAs(wxCommandEvent &event);
    void MenuDatabaseExit(wxCommandEvent &event);

    void MenuViewTasksShowCompleted(wxCommandEvent &event);
    void MenuViewTasksSortByTitle(wxCommandEvent &event);
    void MenuViewTasksSortByFinishDate(wxCommandEvent &event);
    void MenuViewTasksSortByPublicationDate(wxCommandEvent &event);
    void MenuViewTasksSortOrderAsc(wxCommandEvent &event);
    void MenuViewTasksSortOrderDesc(wxCommandEvent &event);

    void MenuToolsSettings(wxCommandEvent &event);

    void MenuHelpURLLatestSourceCode(wxCommandEvent &event);
    void MenuHelpURLLatestReleases(wxCommandEvent &event);
    void MenuHelpAbout(wxCommandEvent &event);

    void ChoiceFilterCategory(wxCommandEvent &event);
    void ChoiceSortField(wxCommandEvent &event);
    void ChoiceSortOrder(wxCommandEvent &event);

    void ButtonManageCategories(wxCommandEvent &event);
    void ButtonCreateTask(wxCommandEvent &event);

    void InitializeWidgets();
    void InitializeIcon();
    void InitializeMenubar();
    void InitializeStatusbar();

    void EnableTasksView(bool enable = true);
    void EnableSizer(wxSizer* sizer, bool enable = true);

    void UpdateWorkspaceStatus();

    void UpdateShownCategories();
    void UpdateShownTasks();
  };
}


#endif //WINDOS_GUI_SCREENS_MAINWINDOW_H