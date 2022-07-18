#include "panels.h"
#include <wx/textctrl.h>


RegPanel::RegPanel(const wxSize& size) : wxPanel() {this->size = size;}

void RegPanel::setSurface() {
    wxPanel* table_panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(195, 300));
    wxPanel* table2_panel = new wxPanel(this, wxID_ANY, wxPoint(150, 0), wxSize(195, 300));
    wxPanel* separation_panel = new wxPanel(this, wxID_ANY, wxPoint(0, 50), wxSize(GetWidth(), 2));
    wxPanel* separation_panel2 = new wxPanel(this, wxID_ANY, wxPoint(20, 0), wxSize(2, GetHeight()));
    wxPanel* separation_panel3 = new wxPanel(this, wxID_ANY, wxPoint(23, 0), wxSize(2, GetHeight()));
    wxPanel* separation_panel4 = new wxPanel(this, wxID_ANY, wxPoint(0, 53), wxSize(GetWidth(), 2));
    table_panel->SetBackgroundColour(wxColor(204, 204, 255));  // night theme 15, 0, 41
    table2_panel->SetBackgroundColour(wxColor(204, 204, 255)); // 54, 75, 105
    separation_panel->SetBackgroundColour(wxColor(122, 189, 222));
    separation_panel2->SetBackgroundColour(wxColor(122, 189, 222));
    separation_panel3->SetBackgroundColour(wxColor(122, 189, 222));
    separation_panel4->SetBackgroundColour(wxColor(122, 189, 222));
    first_col = new wxGrid(table_panel, wxID_ANY, wxPoint(40, 75), wxSize(130, 208));
    sec_col = new wxGrid(table2_panel,  wxID_ANY,  wxPoint(40, 75), wxSize(130, 208));

    wxTextCtrl* n_flag = new wxTextCtrl(this, wxID_ANY, "N = 0", wxPoint(40, 15), wxSize(50, 20), wxTE_READONLY);
    wxTextCtrl* z_flag = new wxTextCtrl(this, wxID_ANY, "Z = 0", wxPoint(110, 15), wxSize(50, 20), wxTE_READONLY);
    wxTextCtrl* v_flag = new wxTextCtrl(this, wxID_ANY, "V = 0", wxPoint(180, 15), wxSize(50, 20), wxTE_READONLY);
    wxTextCtrl* c_flag = new wxTextCtrl(this, wxID_ANY, "C = 0", wxPoint(250, 15), wxSize(50, 20), wxTE_READONLY);
    int rows = 8;
    int col = 2;
    wxFont* fonty = new wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier New");
    first_col->CreateGrid(rows, col);
    first_col->SetRowLabelSize(25);
    first_col->SetColLabelSize(0);
    first_col->SetColLabelValue(0,'A');
    for (int i = 0; i < 8; i++) {
        first_col->SetCellFont(i, 0, *fonty);
        first_col->SetRowSize(i, 26);
        first_col->HideCol(1);
        first_col->SetCellBackgroundColour(i, 0, wxColour(230, 230, 250));
        first_col->SetRowLabelValue(i, wxString(_("R") + std::to_string(i)));
        first_col->SetCellAlignment(i, 0, wxALIGN_CENTRE, wxALIGN_CENTRE);
        
    }
    first_col->SetRowLabelSize (30);
    first_col->SetLabelFont((wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MAX, false, "Arial")));
    first_col->SetLabelTextColour(wxColour(255, 255, 255));
    first_col->SetLabelBackgroundColour(wxColour(122, 189, 222));
   

    first_col->SetColSize(0, 100);
    first_col->SetColSize(1, 0);
    first_col->SetRowLabelAlignment(wxALIGN_RIGHT, wxALIGN_CENTRE);


    sec_col->CreateGrid(rows, col);
    sec_col->SetRowLabelSize(25);
    sec_col->SetColLabelSize(0);
    sec_col->SetColLabelValue(0, 'B');
    sec_col->SetRowLabelAlignment(wxALIGN_RIGHT, wxALIGN_CENTRE);
    char hex[] = { '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    for (int i = 0; i < 8; i++) {
        sec_col->SetCellFont(i, 1, *fonty);
        sec_col->SetRowSize(i, 26);
        sec_col->SetCellBackgroundColour(i, 1, wxColour(230, 230, 250));
        sec_col->SetRowLabelValue(i, wxString(_("R") + hex[i]));
        sec_col->SetCellAlignment(i, 1, wxALIGN_CENTRE, wxALIGN_CENTRE);
    }
    sec_col->SetRowLabelSize(30);
    sec_col->SetColSize(0, 0);
    sec_col->SetColSize(1, 100);
    sec_col->HideCol(0);
    sec_col->SetLabelFont((wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MAX, false, "Arial")));
    sec_col->SetLabelTextColour(wxColour(255, 255, 255));
    sec_col->SetLabelBackgroundColour(wxColour(122, 189, 222));
}


int RegPanel::GetWidth() { return size.GetWidth(); }
int RegPanel::GetHeight() { return size.GetHeight(); }

void RegPanel::checkValue(wxGridEvent& e) {
 
    bool invalid = false;
    wxString str = e.GetString();
    int k = e.GetRow();
    int j = e.GetCol();
    
    
    if ((str.Length() > 8) or (str.IsEmpty())) {
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
                        str[i] = std::toupper(str[i]);
                    }
                }
            }
        }
    }
    if (!invalid) {
        e.Veto();
        if (j == 0) {
             first_col->SetCellValue(k, j, wxString(str));
            // cp.setRegisterCell(k * 16 + j, std::stoi(str.ToStdString(), 0, 16));
        }
        else
             sec_col->SetCellValue(k, j, wxString(str));
        // cp.setRegisterCell(k * 16 + j, std::stoi(str.ToStdString(), 0, 16));
    }
   
}


void RegPanel::denyResizeCol(wxGridSizeEvent& e) {
    first_col->SetColSize(0, 100);
    sec_col->SetColSize(1, 100);
    e.Veto();

}


void RegPanel::denyResizeRow(wxGridSizeEvent& e) {
    first_col->SetRowSize(e.GetRowOrCol(), 26);
    sec_col->SetRowSize(e.GetRowOrCol(), 26);
    e.Veto();
}


wxBEGIN_EVENT_TABLE(RegPanel, wxPanel)
EVT_GRID_CELL_CHANGING(RegPanel::checkValue)
EVT_GRID_COL_SIZE(RegPanel::denyResizeCol)
EVT_GRID_ROW_SIZE(RegPanel::denyResizeRow)
wxEND_EVENT_TABLE()