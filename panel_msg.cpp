#include "panels.h"

MsgPanel::MsgPanel(const wxSize& size) : wxPanel() {this->size = size;}


void MsgPanel::setSurface() {

    wxColor back = wxColor(210, 225, 255);
    wxColor lines = wxColor(122, 189, 222);
    wxColor cells = wxColor(230, 230, 250);
    wxColor white = wxColor(255, 255, 255);

	wxPanel* panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(GetWidth(), GetHeight()));
    panel->SetBackgroundColour(back);
}

int MsgPanel::GetWidth() { return size.GetWidth(); }
int MsgPanel::GetHeight() { return size.GetHeight(); }