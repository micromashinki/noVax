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
	void setTheme(const wxColour& back, const wxColour& label, const wxColour& cell, const wxColour& grid, const wxColour& text, const wxColour& labeck, const wxColour& texl);
	void setValue(int i, const std::string& str);
	void setCallbackFunc(std::function<void()>);
private:
	wxSize size;
	wxGrid* first_col = NULL;
	wxGrid* sec_col = NULL;
	wxTextCtrl* n_flag;
	wxTextCtrl* z_flag;
	wxTextCtrl* v_flag;
	wxTextCtrl* c_flag;
	wxPanel* table_panel;
	wxPanel* table2_panel;
	wxPanel* separation_panel = NULL;
	wxPanel* separation_panel2 = NULL;
	wxPanel* separation_panel3 = NULL;
	wxPanel* separation_panel4;
	wxPanel* separation_panel5;
	wxPanel* separation_panel6;
	wxPanel* separation_panel7;
	wxPanel* separation_panel8;
	std::function<void()> callback = nullptr;
	wxDECLARE_EVENT_TABLE();
};