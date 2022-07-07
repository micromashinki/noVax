#include "panels.h"

MsgPanel::MsgPanel(Okno* o) : wxPanel() {
    size = wxSize(o->GetWidth() - 16, o->GetHeight() - (o->GetHeight() - 250) - 50);
    Create(o, wxID_ANY, wxPoint(0, o->GetHeight() - 250 + 10), size);
}
int MsgPanel::GetWidth() { return size.GetWidth(); }
int MsgPanel::GetHeight() { return size.GetHeight(); }