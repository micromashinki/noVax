#pragma once
class MemPanel : public wxPanel {
public:
	MemPanel(const wxSize&);
	void setSurface();

	int GetWidth();
	int GetHeight();
	void checkValue(wxGridEvent&);
	void denyResizeCol(wxGridSizeEvent&);
	void denyResizeRow(wxGridSizeEvent&);
	void setTheme(const wxColour&, const wxColour&, const wxColour&, const wxColour& text = wxColour(102, 255, 0));

private:
	wxSize size;
	wxGrid* table = NULL;
	wxDECLARE_EVENT_TABLE();
};