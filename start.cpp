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
    mempanel = new MemPanel(wxSize(GetWidth() / 1.5, GetHeight() - 250));
    mempanel->Create(this, wxID_ANY, wxPoint(0, 0), wxSize(mempanel->GetWidth(), mempanel->GetHeight()));
    mempanel->setSurface();

    regpanel = new RegPanel(wxSize((GetWidth() - GetWidth() / 1.5) - 26, ((GetHeight() - 250) / 1.5) - 5));
    regpanel->Create(this, wxID_ANY, wxPoint((GetWidth() / 1.5) + 10, 0), wxSize(regpanel->GetWidth(), regpanel->GetHeight()));
    regpanel->setSurface();

    srchpanel = new SrchPanel(wxSize(GetWidth() - GetWidth() / 1.5 - 26, (GetHeight() - 250) - (GetHeight() - 250) / 1.5 - 5));
    srchpanel->Create(this, wxID_ANY, wxPoint(GetWidth() / 1.5 + 10, (GetHeight() - 250) / 1.5 + 5), wxSize(srchpanel->GetWidth(), srchpanel->GetHeight()));
    //srchpanel->setSurface();

    msgpanel = new MsgPanel(wxSize(GetWidth() - 16, GetHeight() - (GetHeight() - 250) - 50));
    msgpanel->Create(this, wxID_ANY, wxPoint(0, GetHeight() - 250 + 10), wxSize(msgpanel->GetWidth(), msgpanel->GetHeight()));
    //msgpanel->setSurface();

    /*wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, ")))");
    SetMenuBar(menuBar);*/
}
int Okno::GetWidth() { return size.GetWidth(); }
int Okno::GetHeight() { return size.GetHeight();}

wxIMPLEMENT_APP(InitClass);