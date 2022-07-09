#include "panels.h"

MemPanel::MemPanel(Okno* o) : wxPanel() {
    size = wxSize(o->GetWidth() / 1.5, o->GetHeight() - 250);
    wxFont* font = new wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier New");
    Create(o, wxID_ANY, wxPoint(0, 0), size);
    table = new wxGrid(this, wxID_ANY, wxPoint(0, 0), wxSize(GetWidth(), GetHeight()));
    int rows = 128;
    int col = 16;
    table->CreateGrid(rows, col);
    table->SetRowLabelSize(85);
    table->SetRowLabelAlignment(wxALIGN_RIGHT, wxALIGN_CENTRE);
    table->SetLabelFont(wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MAX, false, "Arial"));
    table->SetLabelBackgroundColour(wxColour(44, 117, 255));
    table->SetLabelTextColour(wxColour(255, 255, 255));

    char b[] = {'0', '0', '0', '0', '0', '0', '0', '0'};
    short loc = 0;
    bool format = false;
    for (int i = 0; i < rows; i++) {
        table->SetRowSize(i, 25);
        if (i == 1) format = true;
        for (int j = 0; j < col; j++) {
            if (!format) {
                table->SetColSize(j, 39);
                if (j == 10) b[7] = 'A';
                table->SetColLabelValue(j, wxString(b[7]));
                b[7]++;
            }
            table->SetCellValue(i, j, wxString("00"));
            table->SetCellFont(i, j, *font);
            table->SetCellAlignment(i, j, wxALIGN_CENTRE, wxALIGN_CENTRE);
        }
        table->SetRowLabelValue(i, wxString(std::string(b, sizeof(b)-1) + "0"));
        b[6]++;
        if (b[6] == '9'+1) b[6] = 'A';
        else if (b[6] > 'F') {
            b[6] = '0';
            short c = 5;
            bool perenos = true;
            while ((c > 0) and perenos) {
                b[c]++;
                if (b[c] > 'F') b[c] = '0';
                else {
                    if (b[c] == '9' + 1) b[c] = 'A';
                    perenos = false;
                }
                c--;
            }
            if (c == 0) {
                b[0]++;
                if (b[c] == '9' + 1) b[c] = 'A';
                else if (b[c] > 'F') {
                    for (int j = 0; j < 7; j++) b[c] = 'F';
                    break;
                }
            }
        }
    }
}

int MemPanel::GetWidth() { return size.GetWidth(); }
int MemPanel::GetHeight() { return size.GetHeight(); }


void MemPanel::checkValue(wxGridEvent& e) {
    bool invalid = false;
    wxString str = e.GetString();
    int k = e.GetRow();
    int j = e.GetCol();
    if ((str.Length() > 2) or (str.IsEmpty())) {
        invalid = true;
        e.Veto();
    }
    else {
        for (int i = 0; i < str.Length(); i++) {
            if ((str[i] < '0') or (str[i] > '9')) {
                if ((str[i] < 'A') or (str[i] > 'F')) {
                    if ((str[i] < 'a') or (str[i] > 'f')) { 
                        e.Veto();
                        invalid = true;
                        break;
                    }
                    else {
                        if (str[i] == 'a') { str[i] = 'A'; }
                        else if (str[i] == 'b') { str[i] = 'B'; }
                        else if (str[i] == 'c') { str[i] = 'C'; }
                        else if (str[i] == 'd') { str[i] = 'D'; }
                        else if (str[i] == 'e') { str[i] = 'E'; }
                        else if (str[i] == 'f') { str[i] = 'F'; }
                    }
                }
            }
        }
    }
    if (!invalid) {
        e.Veto();
        if (str.length() == 1) { table->SetCellValue(k, j, wxString("0" + str)); }
        else table->SetCellValue(k, j, wxString(str));
    }
}

void MemPanel::denyResizeCol(wxGridSizeEvent& e) {
    table->SetColSize(e.GetRowOrCol(), 39);
    e.Veto();

    //DELETE THIS ON PRODUCTION
    wxMessageBox("Так нельзя!\nОтсоси");
    //DELETE THIS ON PRODUCTION
}

void MemPanel::denyResizeRow(wxGridSizeEvent& e) {
    table->SetRowSize(e.GetRowOrCol(), 25);
    e.Veto();

    //DELETE THIS ON PRODUCTION
    wxMessageBox("Так нельзя!\nОтсоси");
    //DELETE THIS ON PRODUCTION
}

wxBEGIN_EVENT_TABLE(MemPanel, wxPanel)
EVT_GRID_CELL_CHANGING(MemPanel::checkValue)
EVT_GRID_COL_SIZE(MemPanel::denyResizeCol)
EVT_GRID_ROW_SIZE(MemPanel::denyResizeRow)
wxEND_EVENT_TABLE()