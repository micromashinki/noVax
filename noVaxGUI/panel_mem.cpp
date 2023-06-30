#include "panels.h"

MemPanel::MemPanel(const wxSize& size) : wxPanel() {this->size = size;}

void MemPanel::setSurface() {
    int rows = 128;
    int col = 16;
    table = new wxGrid(this, wxID_ANY, wxPoint(0, 0), size);
    table->CreateGrid(rows, col);
    table->SetRowLabelSize(85);
    table->SetColLabelSize(25);
    table->SetMargins(100, -15);

    table->SetRowLabelAlignment(wxALIGN_RIGHT, wxALIGN_CENTRE);
    table->SetLabelFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MAX, false, "Arial"));
    table->SetLabelBackgroundColour(LINES_AND_LABELS_DEFAULT);
    table->SetLabelTextColour(TEXT_LABEL_DEFAULT);
    table->SetGridLineColour(LINES_AND_LABELS_DEFAULT);
    wxFont* font = new wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier New");
    char b[] = { '0', '0', '0', '0', '0', '0', '0', '0' };
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
            table->SetCellBackgroundColour(i, j, CELLS_DEFAULT);
            table->SetCellTextColour(i, j, TEXT_DEFAULT);

        }
        table->SetRowLabelValue(i, wxString(std::string(b, sizeof(b) - 1) + "0"));
        b[6]++;
        if (b[6] == '9' + 1) b[6] = 'A';
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
        for (int i = 0; i < (int)str.Length(); i++) {
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
        cp.setMemoryCell(k*16+j, std::stoi(str.ToStdString(), 0, 16));
    }
}



void MemPanel::denyResizeCol(wxGridSizeEvent& e) {
    table->SetColSize(e.GetRowOrCol(), 39);
    e.Veto();
}



void MemPanel::denyResizeRow(wxGridSizeEvent& e) {
    table->SetRowSize(e.GetRowOrCol(), 25);
    e.Veto();
}



void MemPanel::setTheme(const wxColour& label, const wxColour& cell, const wxColour& grid, const wxColour& text, const wxColour& text_cell) {
    table->SetLabelBackgroundColour(label);
    table->SetLabelTextColour(text);
    for (int i = 0; i < table->GetNumberRows(); i++) {
        for (int j = 0; j < table->GetNumberCols(); j++) {
            table->SetCellBackgroundColour(i, j, cell);
            table->SetCellTextColour(i, j, text_cell);
        }
    }
    table->SetGridLineColour(grid);
}



void MemPanel::setValue(int i, int j, const std::string& str) {
    if ((str.length() > 5) or (str.empty())) { return; }
    if (str.length() == 1) table->SetCellValue(i, j, wxString("0" + str));
    else table->SetCellValue(i, j, wxString(str));
}


wxBEGIN_EVENT_TABLE(MemPanel, wxPanel)
EVT_GRID_CELL_CHANGING(MemPanel::checkValue)
EVT_GRID_COL_SIZE(MemPanel::denyResizeCol)
EVT_GRID_ROW_SIZE(MemPanel::denyResizeRow)
wxEND_EVENT_TABLE()