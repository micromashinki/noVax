#include "panels.h"

bool InitClass::OnInit() {
    Okno* frame = new Okno("EblR-22", wxSize(1089, 700));
    frame->Show(true);
	return true;
}

Okno::Okno(const wxString& str, const wxSize& s) : wxFrame (NULL, wxID_ANY, str, wxDefaultPosition, s) {
    size = s;
    SetMinSize(s);
    //SetMaxSize(s);
    MemPanel* mempanel = new MemPanel(this);
    RegPanel* regpanel = new RegPanel(this);
    VarPanel* varpanel = new VarPanel(this);
    MsgPanel* msgpanel = new MsgPanel(this);
    /*wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, ")))");
    SetMenuBar(menuBar);*/
}
int Okno::GetWidth() { return size.GetWidth(); }
int Okno::GetHeight() { return size.GetHeight();}

wxIMPLEMENT_APP(InitClass);