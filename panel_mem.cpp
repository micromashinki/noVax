#include "panels.h"

MemPanel::MemPanel(Okno* o) : wxPanel() {
    size = wxSize(o->GetWidth() / 1.5, o->GetHeight() - 250);
    Create(o, wxID_ANY, wxPoint(0, 0), size);
    wxGrid* table = new wxGrid(this, wxID_ANY, wxPoint(0, 0), wxSize(GetWidth(), GetHeight()));
    int rows = 128;
    int col = 16;
    table->CreateGrid(rows, col);
    table->SetRowLabelSize(85);
    table->SetRowLabelAlignment(wxALIGN_RIGHT, wxALIGN_CENTRE);

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