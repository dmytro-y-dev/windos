#ifndef WINDOS_GUI_SCREENS_MAINWINDOW_H
#define WINDOS_GUI_SCREENS_MAINWINDOW_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace windos_gui_screens {
  class MainWindow: public wxFrame
  {
  public:
    MainWindow();
    ~MainWindow();

  private:
    static const int STATUSBAR_PANES_SIZES[];

    static const int STATUSBAR_PANE_DB_PATH;
    static const int STATUSBAR_PANE_DB_ISMODIFIED;

    static const wxSize MIN_WINDOW_SIZE;

  private:
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
    wxCheckBox* m_checkboxShowCompletedTasks;

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

    void ButtonManageCategories(wxCommandEvent &event);
    void ButtonCreateTask(wxCommandEvent &event);

    void UpdateCategoriesList();

    void InitializeWidgets();
    void InitializeIcon();
    void InitializeMenubar();
    void InitializeStatusbar();
  };
}


#endif //WINDOS_GUI_SCREENS_MAINWINDOW_H