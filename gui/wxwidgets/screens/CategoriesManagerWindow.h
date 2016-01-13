#ifndef WINDOS_GUI_SCREENS_CATEGORIESMANAGERWINDOW_H
#define WINDOS_GUI_SCREENS_CATEGORIESMANAGERWINDOW_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace windos_gui_screens {
  class CategoriesManagerWindow: public wxDialog
  {
  public:
    CategoriesManagerWindow(wxWindow* parent);
    ~CategoriesManagerWindow();

  private:
    static const wxSize MIN_WINDOW_SIZE;

    wxTextCtrl* m_searchBoxCategory;
    wxListBox* m_listCategories;

  private:
    wxDECLARE_EVENT_TABLE();

    void InitializeWidgets();
  };
}


#endif //WINDOS_GUI_SCREENS_CATEGORIESMANAGERWINDOW_H