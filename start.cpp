#include "panels.h"

Cprocessor cp;

enum {
    ID_Step = 1,
    ID_Dark = 2,
    ID_About = 3
};

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

    menuFile = new wxMenu;
    menuFile->Append(ID_Step, "ПУСК");
    menuFile->AppendSeparator();
    menuFile->AppendCheckItem(ID_Dark, "ТёМнАя тЕмА");
    menuFile->Append(ID_About, "О программе");

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "пердеш гавнёж");
    SetMenuBar(menuBar);
}

int Okno::GetWidth() { return size.GetWidth(); }
int Okno::GetHeight() { return size.GetHeight();}

void Okno::setDark(wxCommandEvent& e) {
    if (menuFile->IsChecked(ID_Dark)) {
        mempanel->setTheme(wxColour(0, 0, 0), wxColour(30, 30, 30), wxColour(102, 255, 0), wxColour(102, 255, 0));
    }
    else {
        mempanel->setTheme(wxColour(44, 117, 255), wxColour(255, 255, 255), wxColour(0, 0, 0), wxColour(255, 255, 255));
    }
}

void Okno::showAbout(wxCommandEvent& e) {
    std::string creators;
    creators += "Создатели:\n";
    creators += "Лёха-кабан\n";
    creators += "Душнильный менеджер говна (Жидкий)\n";
    creators += "Кислый\n";
    creators += "Слабченко (Пивной сомелье)\n";
    creators += "\n\n\t\t\t========(c) Micromashinki, 2022========";
    wxMessageBox(creators, "Пошёл нахуй");
}

void Okno::startProgram(wxCommandEvent&) {
    wxMessageBox("No est' odin nyuans", ")))");
}

wxBEGIN_EVENT_TABLE(Okno, wxFrame)
    EVT_MENU(ID_Step, Okno::startProgram)
    EVT_MENU(ID_Dark, Okno::setDark)
    EVT_MENU(ID_About, Okno::showAbout)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(InitClass);