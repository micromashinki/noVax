#pragma once
class MsgPanel : public wxPanel {
public:
	MsgPanel(const wxSize&);
	void setSurface();

	int GetWidth();
	int GetHeight();
private:
	wxSize size;
};