#include "TextLinkButton.h"

using windos_gui_components::TextLinkButton;

wxBEGIN_EVENT_TABLE(TextLinkButton, wxButton)
  EVT_PAINT(TextLinkButton::OnPaint)
  EVT_ENTER_WINDOW(TextLinkButton::OnMouseOver)
  EVT_LEAVE_WINDOW(TextLinkButton::OnMouseOut)
wxEND_EVENT_TABLE()

const wxColor TextLinkButton::TextColor(4, 74, 124);

TextLinkButton::TextLinkButton(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name) : wxButton(parent, id, label, pos, size, style | wxBU_EXACTFIT, validator, name), m_mouseOver(false)
{

}

void TextLinkButton::OnPaint(wxPaintEvent &evt)
{
  wxPaintDC dc(this);

  dc.SetBackground(wxBrush(this->GetParent()->GetBackgroundColour(), wxBRUSHSTYLE_SOLID));
  dc.Clear();

  dc.SetTextForeground(TextLinkButton::TextColor);

  wxSize labelSize = dc.GetTextExtent(this->GetLabelText());
  wxSize buttonSize = this->GetSize();

  if (m_mouseOver) {
    wxFont defaultFont = dc.GetFont();
    defaultFont.SetUnderlined(true);

    dc.SetFont(defaultFont);
  }

  dc.DrawText(this->GetLabelText(), (buttonSize.x - labelSize.x) / 2, (buttonSize.y - labelSize.y) / 2);
}

void TextLinkButton::OnMouseOver(wxMouseEvent& event)
{
  m_mouseOver = true;
}

void TextLinkButton::OnMouseOut(wxMouseEvent& event)
{
  m_mouseOver = false;
}
