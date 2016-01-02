#ifndef WINDOS_GUI_MAINWINDOW_H
#define WINDOS_GUI_MAINWINDOW_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace windos_gui {
  class MainWindow: public wxFrame
  {
  public:
    MainWindow();
    ~MainWindow();

  private:
    static const int STATUSBAR_PANE_DATABASE_PATH;
    static const int STATUSBAR_PANE_CODEPAGE;
    static const int STATUSBAR_PANE_ISMODIFIED;
    static const int STATUSBAR_PANE_ERROR_MESSAGE;
    static const int STATUSBAR_PANE_FILEPATH;

  private:
    wxDECLARE_EVENT_TABLE();

    void InitializeMenubar();
  };
}


#endif //WINDOS_GUI_MAINWINDOW_H