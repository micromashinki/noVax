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
	void setRFCell(uint32_t);
	void setRFCell();

private:
	wxSize size;
	int RF_coord = 0;
	bool dark = false;
	wxGrid* table = NULL;
	wxDECLARE_EVENT_TABLE();
};