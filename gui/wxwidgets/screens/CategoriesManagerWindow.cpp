#include "CategoriesManagerWindow.h"

#include <gui/wxwidgets/components/TextLinkButton.h>

using windos_gui_screens::CategoriesManagerWindow;
using windos_gui_components::TextLinkButton;

wxBEGIN_EVENT_TABLE(CategoriesManagerWindow, wxDialog)
wxEND_EVENT_TABLE()

const wxSize CategoriesManagerWindow::MIN_WINDOW_SIZE(500, 400);

CategoriesManagerWindow::CategoriesManagerWindow(wxWindow* parent) : wxDialog(parent, wxID_ANY, _("Manage categories"), wxDefaultPosition, MIN_WINDOW_SIZE, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
  SetSizeHints(MIN_WINDOW_SIZE);
  SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

  InitializeWidgets();

  Centre(wxBOTH);
}

CategoriesManagerWindow::~CategoriesManagerWindow()
{
}

void CategoriesManagerWindow::InitializeWidgets()
{
  wxBoxSizer* sizerCategories = new wxBoxSizer(wxVERTICAL);

  m_searchBoxCategory = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
  sizerCategories->Add(m_searchBoxCategory, 0, wxALL | wxEXPAND, 5);

  m_listCategories = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_ALWAYS_SB | wxLB_SINGLE); 
  sizerCategories->Add(m_listCategories, 1, wxALL | wxEXPAND, 5);

  wxBoxSizer* sizerCategoriesActions = new wxBoxSizer(wxHORIZONTAL);

  TextLinkButton* btnCreateNewCategory = new TextLinkButton(this, wxID_ANY, wxT("Create new category..."), wxDefaultPosition, wxDefaultSize, 0);
  sizerCategoriesActions->Add(btnCreateNewCategory, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

  sizerCategories->Add(sizerCategoriesActions, 0, wxLEFT | wxRIGHT | wxALIGN_RIGHT, 5);

  SetSizer(sizerCategories);
  Layout();
}
