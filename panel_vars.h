#pragma once
class VarPanel : public wxPanel {
public:
	VarPanel(Okno*);
	int GetWidth();
	int GetHeight();
private:
	wxSize size;
};