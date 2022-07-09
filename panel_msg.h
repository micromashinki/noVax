#pragma once
class MsgPanel : public wxPanel {
public:
	MsgPanel(Okno*);
	int GetWidth();
	int GetHeight();
private:
	wxSize size;
};