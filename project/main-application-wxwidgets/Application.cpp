#include <wx/stdpaths.h>

#include "Application.h"
#include "MainWindow.h"

using windos_gui::Application;

wxIMPLEMENT_APP(Application);

bool Application::OnInit()
{
  // Initialize libpng for wxWidgets

  wxImage::AddHandler(new wxPNGHandler());

  // Get current executable directory

  m_applicationDirectory = wxStandardPaths::Get().GetExecutablePath();
  m_applicationDirectory = m_applicationDirectory.substr(0, m_applicationDirectory.rfind(this->argv[0]));

  // Create main window

  MainWindow* mainWindow = new MainWindow();
  mainWindow->Show(true);

  return true;
}

int Application::OnExit()
{
  return wxApp::OnExit();
}

wxString Application::GetApplicationDirectory() const
{
  return m_applicationDirectory;
}

Application& windos_gui::wxGetApp()
{
  return ::wxGetApp();
}