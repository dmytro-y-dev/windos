#ifndef WINDOS_GUI_COMPONENTS_TEXTLINKBUTTON_H
#define WINDOS_GUI_COMPONENTS_TEXTLINKBUTTON_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace windos_gui_components {
  class TextLinkButton: public wxButton
  {
  public:
    TextLinkButton(wxWindow *parent, wxWindowID id, const wxString &label=wxEmptyString, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxButtonNameStr);

  private:
    static const wxColor DefaultTextColor;
    static const wxColor DisabledTextColor;

    bool m_mouseOver;

  private:
    wxDECLARE_EVENT_TABLE();

    void OnPaint(wxPaintEvent &evt);
    void OnEraseBackground(wxEraseEvent& event);

    void OnMouseOver(wxMouseEvent& event);
    void OnMouseOut(wxMouseEvent& event);
  };
}


#endif //WINDOS_GUI_COMPONENTS_TEXTLINKBUTTON_H