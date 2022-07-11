#include "panels.h"
#include <wx/textctrl.h>


RegPanel::RegPanel(Okno* o) : wxPanel() {
    size = wxSize((o->GetWidth() - o->GetWidth() / 1.5) - 26, ((o->GetHeight() - 250) / 1.5) - 5);
    
    Create(o, wxID_ANY, wxPoint((o->GetWidth() / 1.5) + 10, 0), size);
    wxPanel* table_panel  = new wxPanel( this, wxID_ANY, wxPoint(0, 0), wxSize(175, 300));
    wxPanel* table2_panel = new wxPanel(this, wxID_ANY, wxPoint(175,0), wxSize(200, 300));
    table_panel->SetBackgroundColour(wxColor(255,140,105));
    table2_panel->SetBackgroundColour(wxColor(230, 230, 250));
    wxGrid* first_col = new wxGrid(table_panel, wxID_ANY, wxPoint(0, 50), wxSize(GetWidth(), GetHeight()));
    wxGrid* sec_col = new wxGrid(table2_panel, wxID_ANY, wxPoint(0, 50), wxSize(GetWidth(), GetHeight()));
    wxTextCtrl* t_flag = new wxTextCtrl( this, wxID_ANY, "T = 0", wxPoint(20,  15), wxSize(50, 20), wxTE_READONLY );
    wxTextCtrl* n_flag = new wxTextCtrl( this, wxID_ANY, "N = 0", wxPoint(80,  15), wxSize(50, 20), wxTE_READONLY );
    wxTextCtrl* z_flag = new wxTextCtrl( this, wxID_ANY, "Z = 0", wxPoint(140, 15), wxSize(50, 20), wxTE_READONLY );
    wxTextCtrl* v_flag = new wxTextCtrl( this, wxID_ANY, "V = 0", wxPoint(200, 15), wxSize(50, 20), wxTE_READONLY );
    wxTextCtrl* c_flag = new wxTextCtrl( this, wxID_ANY, "C = 0", wxPoint(260, 15), wxSize(50, 20), wxTE_READONLY );
    int rows = 8;
    int col = 1;
    first_col->CreateGrid(rows, col);
    first_col->SetRowLabelSize(25);
    first_col->SetColLabelSize(0);
    for (int i = 0; i < 8; i++) {
       first_col-> SetRowLabelValue(i, wxString(_("R")+std::to_string(i)));
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
    void RegPanel::denyResizeCol(wxGridSizeEvent & e) {
        table->SetColSize(e.GetRowOrCol(), 39);
        e.Veto();

        //DELETE THIS ON PRODUCTION
        wxMessageBox("??? ??????!\n??????");
        //DELETE THIS ON PRODUCTION
    }

    void RegPanel::denyResizeRow(wxGridSizeEvent & e) {
        table->SetRowSize(e.GetRowOrCol(), 25);
        e.Veto();

        //DELETE THIS ON PRODUCTION
        wxMessageBox("??? ??????!\n??????");
        //DELETE THIS ON PRODUCTION
    }
   
}
int RegPanel::GetWidth() { return size.GetWidth(); }
int RegPanel::GetHeight() { return size.GetHeight(); }

wxBEGIN_EVENT_TABLE(RegPanel, wxPanel)
EVT_GRID_CELL_CHANGING(RegPanel::checkValue)
EVT_GRID_COL_SIZE(RegPanel::denyResizeCol)
EVT_GRID_ROW_SIZE(RegPanel::denyResizeRow)
wxEND_EVENT_TABLE()