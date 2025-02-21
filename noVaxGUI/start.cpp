﻿#include "panels.h"
#include <wx/filedlg.h>

Cprocessor cp;
MemPanel* mempanel;
RegPanel* regpanel;
Okno* frame;
MsgPanel* msgpanel;

enum {
    ID_Step = 1,
    ID_Dark = 2,
    ID_About = 3,
    ID_Open = 4,
    ID_Save = 5,
    ID_Start = 6
};

bool InitClass::OnInit() {
    frame = new Okno("VAX-22", wxSize(1089, 700));
    frame->Show(true);
	return true;
}

Okno::Okno(const wxString& str, const wxSize& s) : wxFrame (NULL, wxID_ANY, str, wxDefaultPosition, s) {
    size = s;
    //kostyl dlya raZmeroV okna
    if (wxPlatformInfo::Get().GetDesktopEnvironment().ToStdString() == "GNOME") {
        SetMinSize(wxSize(1089+34, 700+50));
        SetMaxSize(wxSize(1089+34, 700+50));
    }
    else {
        SetMinSize(s);
        SetMaxSize(s);
    }
    mempanel = new MemPanel(wxSize(GetWidth() / 1.5, GetHeight() - 250));
    mempanel->Create(this, wxID_ANY, wxPoint(0, 0), wxSize(mempanel->GetWidth(), mempanel->GetHeight()));
    mempanel->setSurface();

    regpanel = new RegPanel(wxSize((GetWidth() - GetWidth() / 1.5) - 26, GetHeight() - 250));
    regpanel->setCallbackFunc(std::bind(&changeRF));
    regpanel->Create(this, wxID_ANY, wxPoint((GetWidth() / 1.5) + 8, 0), wxSize(regpanel->GetWidth(), regpanel->GetHeight()));
    regpanel->setSurface();

    msgpanel = new MsgPanel(wxSize(GetWidth() - 16, GetHeight() - (GetHeight() - 250) - 66));
    msgpanel->Create(this, wxID_ANY, wxPoint(0, GetHeight() - 250 + 6 ), wxSize(msgpanel->GetWidth(), msgpanel->GetHeight()));
    msgpanel->setSurface();

    menuFile = new wxMenu;
    menuFile->Append(ID_Open, "Open");
    menuFile->Append(ID_Save, "Save\tCtrl+S");

    menuFile2 = new wxMenu;
    menuFile2->Append(ID_Start, "Start\tF6");
    menuFile2->Append(ID_Step, "Step\tF5");

    menuFile3 = new wxMenu;
    menuFile3->AppendCheckItem(ID_Dark, "Change theme\tCtrl+T");

    menuFile4 = new wxMenu;
    menuFile4->Append(ID_About, "About\tCtrl+A");



    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "File");
    menuBar->Append(menuFile2, "Program");
    menuBar->Append(menuFile3, "Settings");
    menuBar->Append(menuFile4, "About");
    SetMenuBar(menuBar);
    SetBackgroundColour(LINES_AND_LABELS_DEFAULT);
}

int Okno::GetWidth() { return size.GetWidth(); }
int Okno::GetHeight() { return size.GetHeight();}

void Okno::setDark(wxCommandEvent& e) {
    if (menuFile3->IsChecked(ID_Dark)) {
        //(66, 163, 0) || (62, 183, 0) SO_DARK
        mempanel->setTheme(PANEL_DARK, SO_DARK, LINES_AND_LABELS_DEFAULT, LINES_AND_LABELS_DEFAULT, LINES_AND_LABELS_DEFAULT);
        regpanel->setTheme(PANEL_DARK, PANEL_DEFAULT, SO_DARK, LINES_AND_LABELS_DEFAULT, PANEL_DARK, LINES_AND_LABELS_DEFAULT, LINES_AND_LABELS_DEFAULT);
        msgpanel->setTheme(PANEL_DARK, LINES_AND_LABELS_DEFAULT);
        SetBackgroundColour(LINES_AND_LABELS_DEFAULT);
    }
    else {
       // regpanel->setTheme(wxColour(0, 0, 0), wxColour(0, 0, 0), wxColour(0, 0, 0), wxColour(0, 0, 0), wxColour(0, 0, 0), wxColour(0, 0, 0));
        mempanel->setTheme(LINES_AND_LABELS_DEFAULT, CELLS_DEFAULT, LINES_AND_LABELS_DEFAULT, TEXT_LABEL_DEFAULT, TEXT_DEFAULT);
       regpanel->setTheme(PANEL_DEFAULT, LINES_AND_LABELS_DEFAULT, CELLS_DEFAULT, LINES_AND_LABELS_DEFAULT, TEXT_LABEL_DEFAULT, LINES_AND_LABELS_DEFAULT, TEXT_DEFAULT);
       msgpanel->setTheme(PANEL_DEFAULT, TEXT_DEFAULT);
    }
    Refresh();
}

void Okno::showAbout(wxCommandEvent& e) {
    std::string creators;
    creators += "Creators:\n";
    creators += "Лёха-кабан\n";
    creators += "Душнильный менеджер говна (Жидкий)\n";
    creators += "Кислый\n";
    creators += "Слабченко (Пивной сомелье)\n";
    creators += "Мшка\n";
    creators += "\n\n\t\t\t========(c) Micromashinki, 2022========";
    wxMessageBox(creators, "О программе");
}

void Okno::makeStep(wxCommandEvent& e) {
    Cprocessor::SDescriptionLastCommand tmp;
    try {
        tmp = cp.step();
    }
    catch(...) {
        wxMessageBox("Не работает!\nКто виноват?");
    }
    std::vector<uint32_t> cells = tmp.changeCell;
    std::string desc = tmp.description;
    for (int i = 0; i < cells.size(); i++) {
        int a = cells[i];
        mempanel->setValue(a / 16, a % 16, int_to_hex(cp.getMemory()[a]));
    }
    std::vector<uint32_t> sasha_i_lesha_uebani= cp.getRegister();
    for (int i = 0; i < 16; i++) {
        regpanel->setValue(i, int_to_hex(sasha_i_lesha_uebani[i]));
    }
    mempanel->setRFCell(sasha_i_lesha_uebani[15]);
    msgpanel->setMessage(desc);
    Refresh();
}

void Okno::executeProgram(wxCommandEvent& e) {
    std::vector<Cprocessor::SDescriptionLastCommand> tmp1;
    try {
        tmp1 = cp.execute();
    }
    catch(...) {
        wxMessageBox("Не работает!\nКто виноват?");
    }
    std::string desc;
    uint32_t last_val;
    for(Cprocessor::SDescriptionLastCommand tmp : tmp1){
        std::vector<uint32_t> cells = tmp.changeCell;
        desc += tmp.description;
        desc += '\n';

        for (int i = 0; i < cells.size(); i++) {
            int a = cells[i];
            mempanel->setValue(a / 16, a % 16, int_to_hex(cp.getMemory()[a]));
        }
        std::vector<uint32_t> poshel_nakhuy_ueban = cp.getRegister();
        for (int i = 0; i < 16; i++) {
            regpanel->setValue(i, int_to_hex(poshel_nakhuy_ueban[i]));
        }
        last_val = poshel_nakhuy_ueban[15];
    }
    mempanel->setRFCell(last_val);
    msgpanel->setMessage(desc);
    Refresh();
}

void Okno::openFile(wxCommandEvent& e) {
    wxFileDialog* fd = new wxFileDialog(this, wxString("Open v11 file"), "", "", "*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (fd->ShowModal() == wxID_CANCEL) return;
    cp.load(fd->GetPath().ToStdString());
    std::vector<uint8_t> mem = cp.getMemory();
    for (int i = 0; i < (128 * 16); i++) {
        mempanel->setValue(i / 16, i % 16, int_to_hex(mem[i]));
    }
    std::vector<uint32_t> fedya_ueban = cp.getRegister();
    for (int i = 0; i < 16; i++) {
        regpanel->setValue(i, int_to_hex(fedya_ueban[i]));
    }
    mempanel->setRFCell(fedya_ueban[15]);
    Refresh();
}

void Okno::saveFile(wxCommandEvent& e) {
    wxFileDialog* fd = new wxFileDialog(this, wxString("Save v11 file"), "", "", "*.v11|*.v11", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (fd->ShowModal() == wxID_CANCEL) return;
    cp.save(fd->GetPath().ToStdString()); //hui znaet, rabotaet ili net
}

void changeRF(){
    mempanel->setRFCell(cp.getRegister()[15]);
    frame->Refresh();
}


wxBEGIN_EVENT_TABLE(Okno, wxFrame)
    EVT_MENU(ID_Step, Okno::makeStep)
    EVT_MENU(ID_Dark, Okno::setDark)
    EVT_MENU(ID_About, Okno::showAbout)
    EVT_MENU(ID_Open, Okno::openFile)
    EVT_MENU(ID_Save, Okno::saveFile)
    EVT_MENU(ID_Start, Okno::executeProgram)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(InitClass);