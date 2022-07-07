#include "panels.h"

RegPanel::RegPanel(Okno* o) : wxPanel() {
    size = wxSize((o->GetWidth() - o->GetWidth() / 1.5) - 26, ((o->GetHeight() - 250) / 1.5) - 5);
    Create(o, wxID_ANY, wxPoint((o->GetWidth() / 1.5) + 10, 0), size);
}
int RegPanel::GetWidth() { return size.GetWidth(); }
int RegPanel::GetHeight() { return size.GetHeight(); }