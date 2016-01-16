#ifndef WINDOS_GUI_APPLICATION_H
#define WINDOS_GUI_APPLICATION_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <model/workspace/Workspace.h>

namespace windos_gui {
  class Application : public wxApp
  {
  private:
    typedef todos_model_workspace::Workspace Workspace;

  public:
    virtual bool OnInit();
    virtual int OnExit();

    wxString GetApplicationDirectory() const;
    Workspace& GetWorkspace();

  private:
    wxString m_applicationDirectory;
    Workspace m_workspace;
  };

  Application& wxGetApp();
}

#endif //WINDOS_GUI_APPLICATION_H