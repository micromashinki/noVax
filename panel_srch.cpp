#include "panels.h"
#include <wx/srchctrl.h>

SrchPanel::SrchPanel(const wxSize& size) : wxPanel() {this->size = size;}

void SrchPanel::setSurface() {

    wxColor back = wxColor(210, 225, 255);
    wxColor lines = wxColor(122, 189, 222);
    wxColor cells = wxColor(230, 230, 250);
    wxColor white = wxColor(255, 255, 255);

    
    this->SetBackgroundColour(back);
    wxSearchCtrl* search = wxSearchCtrl();
}

int SrchPanel::GetWidth() { return size.GetWidth(); }
int SrchPanel::GetHeight() { return size.GetHeight(); }