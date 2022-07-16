#include "panels.h"
#include <wx/textctrl.h>


RegPanel::RegPanel(const wxSize& size) : wxPanel() {this->size = size;}

void RegPanel::setSurface() {
    wxPanel* table_panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(150, 300));
    wxPanel* table2_panel = new wxPanel(this, wxID_ANY, wxPoint(151, 0), wxSize(200, 300));
    table_panel->SetBackgroundColour(wxColor(255, 140, 105));
    table2_panel->SetBackgroundColour(wxColor(230, 230, 250));
    wxGrid* first_col = new wxGrid(table_panel, wxID_ANY, wxPoint(25, 75), wxSize(GetWidth(), GetHeight()));
    wxGrid* sec_col = new wxGrid(table2_panel, wxID_ANY, wxPoint(25, 75), wxSize(GetWidth(), GetHeight()));
    wxTextCtrl* t_flag = new wxTextCtrl(this, wxID_ANY, "T = 0", wxPoint(20, 15), wxSize(50, 20), wxTE_READONLY);
    wxTextCtrl* n_flag = new wxTextCtrl(this, wxID_ANY, "N = 0", wxPoint(80, 15), wxSize(50, 20), wxTE_READONLY);
    wxTextCtrl* z_flag = new wxTextCtrl(this, wxID_ANY, "Z = 0", wxPoint(140, 15), wxSize(50, 20), wxTE_READONLY);
    wxTextCtrl* v_flag = new wxTextCtrl(this, wxID_ANY, "V = 0", wxPoint(200, 15), wxSize(50, 20), wxTE_READONLY);
    wxTextCtrl* c_flag = new wxTextCtrl(this, wxID_ANY, "C = 0", wxPoint(260, 15), wxSize(50, 20), wxTE_READONLY);
    int rows = 8;
    int col = 1;
    first_col->CreateGrid(rows, col);
    first_col->SetRowLabelSize(25);
    first_col->SetColLabelSize(0);
    for (int i = 0; i < 8; i++) {
        first_col->SetRowLabelValue(i, wxString(_("R") + std::to_string(i)));
    }
    first_col->SetRowLabelAlignment(wxALIGN_RIGHT, wxALIGN_CENTRE);
    sec_col->CreateGrid(rows, col);
    sec_col->SetRowLabelSize(25);
    sec_col->SetColLabelSize(0);
    sec_col->SetRowLabelAlignment(wxALIGN_RIGHT, wxALIGN_CENTRE);
    char hex[] = { '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    for (int i = 0; i < 8; i++) {
        sec_col->SetRowLabelValue(i, wxString(_("R") + hex[i]));
    }
}


int RegPanel::GetWidth() { return size.GetWidth(); }
int RegPanel::GetHeight() { return size.GetHeight(); }

void RegPanel::checkValue(wxGridEvent& e) {
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
        if (str.length() == 1) { first_col->SetCellValue(k, j, wxString("0" + str)); }
        else  first_col->SetCellValue(k, j, wxString(str));
        /*int a;
        if (k == 0) a = j;
        else a = k*16+j;
        setMemoryCell(a, std::stoi(str.ToStdString(), 0, 16));*/
        //setTheme(wxColour(0, 0, 0), wxColour(30, 30, 30), wxColour(102, 255, 0));
    }
}

void RegPanel::denyResizeCol(wxGridSizeEvent& e) {
    first_col->SetColSize(e.GetRowOrCol(), 39);
    sec_col->SetColSize(e.GetRowOrCol(), 39);
    e.Veto();

}


void RegPanel::denyResizeRow(wxGridSizeEvent& e) {
    first_col->SetRowSize(e.GetRowOrCol(), 25);
    sec_col->SetRowSize(e.GetRowOrCol(), 25);
    e.Veto();
}

/*
wxBEGIN_EVENT_TABLE(RegPanel, wxPanel)
EVT_GRID_CELL_CHANGING(RegPanel::checkValue)
EVT_GRID_COL_SIZE(RegPanel::denyResizeCol)
EVT_GRID_ROW_SIZE(RegPanel::denyResizeRow)
wxEND_EVENT_TABLE()*/