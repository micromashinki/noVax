#include "panels.h"

MsgPanel::MsgPanel(const wxSize& size) : wxPanel() {this->size = size;}


void MsgPanel::setSurface() {
    msg = new wxTextCtrl(this, wxID_ANY, "(null)", wxPoint(0, 0), size, wxTE_READONLY| wxTE_MULTILINE);
    msg->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MAX, false, "Arial"));
    msg->SetBackgroundColour(PANEL_DEFAULT);
}

void MsgPanel::setMessage(std::string str) {
    msg->SetValue(wxString(str));

}

int MsgPanel::GetWidth() { return size.GetWidth(); }
int MsgPanel::GetHeight() { return size.GetHeight(); }