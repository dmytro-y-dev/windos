#ifndef WINDOS_GUI_APPLICATION_H
#define WINDOS_GUI_APPLICATION_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace windos_gui {
  class Application : public wxApp
  {
  public:
    virtual bool OnInit();
    virtual int OnExit();

    wxString GetApplicationDirectory() const;

  private:
    wxString m_applicationDirectory;
  };

  Application& wxGetApp();
}

#endif //WINDOS_GUI_APPLICATION_H