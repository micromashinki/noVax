#include "panels.h"
     

RegPanel::RegPanel(const wxSize& size) : wxPanel() {this->size = size;}

void RegPanel::setSurface() {

     table_panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(180, 600));
     table2_panel = new wxPanel(this, wxID_ANY, wxPoint(180, 0), wxSize(195, 600));

    separation_panel = new wxPanel(this, wxID_ANY, wxPoint(0, 50), wxSize(GetWidth(), 2));
    separation_panel2 = new wxPanel(this, wxID_ANY, wxPoint(20, 0), wxSize(2, GetHeight()));
    separation_panel3 = new wxPanel(this, wxID_ANY, wxPoint(23, 0), wxSize(2, GetHeight()));
    separation_panel4 = new wxPanel(this, wxID_ANY, wxPoint(0, 53), wxSize(GetWidth(), 2));
    separation_panel5 = new wxPanel(this, wxID_ANY, wxPoint(0, 303), wxSize(GetWidth(), 2));
    separation_panel6 = new wxPanel(this, wxID_ANY, wxPoint(0, 306), wxSize(GetWidth(), 2));
    separation_panel7 = new wxPanel(this, wxID_ANY, wxPoint(0, 416), wxSize(GetWidth(), 2));
    separation_panel8 = new wxPanel(this, wxID_ANY, wxPoint(0, 419), wxSize(GetWidth(), 2));

    wxColor back = wxColor(210, 225, 255);
    wxColor lines = wxColor(122, 189, 222);
    wxColor cells = wxColor(230, 230, 250);
    wxColor white = wxColor(255, 255, 255);
   
    
    
    

    table_panel->SetBackgroundColour(back);  // night theme 15, 0, 41
    table2_panel->SetBackgroundColour(back); // 54, 75, 105  || 204, 204, 255
    separation_panel-> SetBackgroundColour(lines);
    separation_panel2->SetBackgroundColour(lines);
    separation_panel3->SetBackgroundColour(lines);
    separation_panel4->SetBackgroundColour(lines);
    separation_panel5->SetBackgroundColour(lines);
    separation_panel6->SetBackgroundColour(lines);
    separation_panel7->SetBackgroundColour(lines);
    separation_panel8->SetBackgroundColour(lines);

    first_col = new wxGrid(table_panel, wxID_ANY, wxPoint(40, 75), wxSize(130, 208));
    sec_col = new wxGrid(table2_panel,  wxID_ANY,  wxPoint(10, 75), wxSize(130, 208));

     n_flag = new wxTextCtrl(this, wxID_ANY, "N = 0", wxPoint(40, 15), wxSize(50, 20), wxTE_READONLY);
     z_flag = new wxTextCtrl(this, wxID_ANY, "Z = 0", wxPoint(120, 15), wxSize(50, 20), wxTE_READONLY);
     v_flag = new wxTextCtrl(this, wxID_ANY, "V = 0", wxPoint(190, 15), wxSize(50, 20), wxTE_READONLY);
     c_flag = new wxTextCtrl(this, wxID_ANY, "C = 0", wxPoint(270, 15), wxSize(50, 20), wxTE_READONLY);

    n_flag->SetBackgroundColour(cells);
    z_flag->SetBackgroundColour(cells);
    v_flag->SetBackgroundColour(cells);
    c_flag->SetBackgroundColour(cells);

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
        first_col->SetCellBackgroundColour(i, 0, cells);
        first_col->SetRowLabelValue(i, wxString(_("R") + std::to_string(i)));
        first_col->SetCellAlignment(i, 0, wxALIGN_CENTRE, wxALIGN_CENTRE);
        first_col->SetCellValue(i, 0, wxString("00000000"));
        
    }
    first_col->SetRowLabelSize (30);
    first_col->SetLabelFont((wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MAX, false, "Arial")));
    first_col->SetLabelTextColour(white);
    first_col->SetLabelBackgroundColour(lines);
    first_col->SetGridLineColour(lines);
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
        sec_col->SetCellBackgroundColour(i, 1,cells);
        sec_col->SetRowLabelValue(i, wxString(_("R") + hex[i]));
        sec_col->SetCellAlignment(i, 1, wxALIGN_CENTRE, wxALIGN_CENTRE);
        sec_col->SetCellValue(i, 1, wxString("00000000"));
    }
    sec_col->SetRowLabelSize(30);
    sec_col->SetColSize(0, 0);
    sec_col->SetColSize(1, 100);
    sec_col->HideCol(0);
    sec_col->SetLabelFont((wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MAX, false, "Arial")));
    sec_col->SetLabelTextColour(white);
    sec_col->SetLabelBackgroundColour(lines);
    sec_col->SetGridLineColour(lines);
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
             first_col->SetCellValue(k, j, wxString(str) );
             cp.setRegisterCell(k, std::stoul(str.ToStdString(), 0, 16)); //work)))
        }
        else {
            sec_col->SetCellValue(k, j, wxString(str));
            cp.setRegisterCell(k + 8, std::stoul(str.ToStdString(), 0, 16));
            
        }
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

void RegPanel::setValue(int i, const std::string& str) {
    if ((str.length() > 8) or (str.empty())) { return; }
    if( i > 7) sec_col->SetCellValue(i-8, 1, str);
    else first_col->SetCellValue(i, 0, str);
    n_flag->SetValue("N = " + std::to_string(cp.getNFlag()));
    z_flag->SetValue("Z = " + std::to_string(cp.getZFlag()));
    v_flag->SetValue("V = " + std::to_string(cp.getVFlag()));
    c_flag->SetValue("C = " + std::to_string(cp.getCFlag()));
 
}

void RegPanel::setTheme(const wxColour& back, const wxColour& lines, const wxColour& cell, const wxColour& grid, const wxColour& text, const wxColour& labeck, const wxColour& texl) {
    table_panel->SetBackgroundColour(back);  // night theme 15, 0, 41
    table2_panel->SetBackgroundColour(back); // 54, 75, 105  || 204, 204, 255
    separation_panel->SetBackgroundColour(lines);
    separation_panel2->SetBackgroundColour(lines);
    separation_panel3->SetBackgroundColour(lines);
    separation_panel4->SetBackgroundColour(lines);
    separation_panel5->SetBackgroundColour(lines);
    separation_panel6->SetBackgroundColour(lines);
    separation_panel7->SetBackgroundColour(lines);
    separation_panel8->SetBackgroundColour(lines);
    n_flag->SetBackgroundColour(cell);
    z_flag->SetBackgroundColour(cell);
    v_flag->SetBackgroundColour(cell);
    c_flag->SetBackgroundColour(cell);
    for (int i = 0; i < 8; i++) {
        first_col->SetCellBackgroundColour(i, 0, cell);
        sec_col->SetCellBackgroundColour(i, 1, cell);
        first_col->SetCellTextColour(i, 0, texl);
        sec_col->SetCellTextColour(i, 1, texl);
    }
    first_col->SetLabelTextColour(text);
    first_col->SetLabelBackgroundColour(labeck);
    first_col->SetGridLineColour(grid);
    sec_col->SetLabelTextColour(text);
    sec_col->SetLabelBackgroundColour(labeck);
    sec_col->SetGridLineColour(grid);
    n_flag->SetForegroundColour(texl);
    z_flag->SetForegroundColour(texl);
    v_flag->SetForegroundColour(texl);
    c_flag->SetForegroundColour(texl);
}


wxBEGIN_EVENT_TABLE(RegPanel, wxPanel)
EVT_GRID_CELL_CHANGING(RegPanel::checkValue)
EVT_GRID_COL_SIZE(RegPanel::denyResizeCol)
EVT_GRID_ROW_SIZE(RegPanel::denyResizeRow)
wxEND_EVENT_TABLE()