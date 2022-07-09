#pragma once
class RegPanel : public wxPanel {
public:
	RegPanel(Okno*);
	int GetWidth();
	int GetHeight();
private:
	wxSize size;
};