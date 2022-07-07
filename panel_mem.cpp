#include "panels.h"

MemPanel::MemPanel(Okno* o) : wxPanel() {
    size = wxSize(o->GetWidth() / 1.5, o->GetHeight() - 250);
    Create(o, wxID_ANY, wxPoint(0, 0), size);
    wxGrid* table = new wxGrid(this, wxID_ANY, wxPoint(0, 0), wxSize(GetWidth(), GetHeight()));
    table->CreateGrid(100, 16);
}
int MemPanel::GetWidth() { return size.GetWidth(); }
int MemPanel::GetHeight() { return size.GetHeight(); }