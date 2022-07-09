#pragma once
class MemPanel : public wxPanel {
public:
	MemPanel(Okno*);
	int GetWidth();
	int GetHeight();
	void checkValue(wxGridEvent&);
	void denyResizeCol(wxGridSizeEvent&);
	void denyResizeRow(wxGridSizeEvent&);
private:
	wxSize size;
	wxGrid* table;
	wxDECLARE_EVENT_TABLE();
};