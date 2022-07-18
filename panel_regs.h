#pragma once
class RegPanel : public wxPanel {
public:
	RegPanel(const wxSize&);
	void setSurface();

	int GetWidth();
	int GetHeight();
	void checkValue(wxGridEvent&);
	void denyResizeCol(wxGridSizeEvent&);
	void denyResizeRow(wxGridSizeEvent&);
	void setTheme(const wxColour&, const wxColour&, const wxColour&, const wxColour& text = wxColour(102, 255, 0));
private:
	wxSize size;
	wxGrid* first_col = NULL;
	wxGrid* sec_col = NULL;
	wxDECLARE_EVENT_TABLE();
};