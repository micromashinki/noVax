#pragma once
class MsgPanel : public wxPanel {
public:
	MsgPanel(const wxSize&);
	void setSurface();

	int GetWidth();
	int GetHeight();

	void setMessage(std::string);
private:
	wxSize size;
	wxTextCtrl* msg;
};