#include "panels.h"

MemPanel::MemPanel(Okno* o) : wxPanel() {
    Create(o, wxID_ANY, wxPoint(0, 0), wxSize(o->GetWidth() / 1.5, o->GetHeight() - 250));
    /*wxScrollBar* membar = new wxScrollBar(panel_mem, wxID_ANY, wxPoint(size.GetWidth() / 1.5 - 15, 0), wxSize(15, size.GetHeight() - 200), wxSB_VERTICAL);*/
}

RegPanel::RegPanel(Okno* o) : wxPanel() {
    Create(o, wxID_ANY, wxPoint((o->GetWidth() / 1.5) + 10, 0), wxSize((o->GetWidth() - o->GetWidth() / 1.5) - 26, ((o->GetHeight() - 250) / 1.5) - 5));
}