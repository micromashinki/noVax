#include "panels.h"
#include <wx/textctrl.h>

MsgPanel::MsgPanel(const wxSize& size) : wxPanel() {this->size = size;}


void MsgPanel::setSurface() {
    msg = new wxTextCtrl(this, wxID_ANY, "(null)", wxPoint(0, 0), size, wxTE_READONLY| wxTE_MULTILINE);
    msg->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial"));
    msg->SetBackgroundColour(wxCANCEL_DEFAULT);
}

void MsgPanel::setMessage(std::string str) {
    msg->SetValue(wxString(str));
}

void MsgPanel::setTheme(const wxColour& back, const wxColour& text) {
    msg->SetBackgroundColour(back);
    msg->SetForegroundColour(text);
}

int MsgPanel::GetWidth() { return size.GetWidth(); }
int MsgPanel::GetHeight() { return size.GetHeight(); }