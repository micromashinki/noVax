#include "panels.h"

VarPanel::VarPanel(Okno* o) : wxPanel() {
    size = wxSize(o->GetWidth() - o->GetWidth() / 1.5 - 26, (o->GetHeight() - 250) - (o->GetHeight() - 250) / 1.5 - 5);
    Create(o, wxID_ANY, wxPoint((o->GetWidth() / 1.5) + 10, (o->GetHeight() - 250) / 1.5 + 5), size);
}
int VarPanel::GetWidth() { return size.GetWidth(); }
int VarPanel::GetHeight() { return size.GetHeight(); }