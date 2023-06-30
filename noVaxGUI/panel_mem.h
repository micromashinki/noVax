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
	void setTheme(const wxColour&, const wxColour&, const wxColour&, const wxColour&, const wxColour&);
	void setValue(int, int, const std::string&);

private:
	wxSize size;
	wxGrid* table = NULL;
	wxDECLARE_EVENT_TABLE();
};