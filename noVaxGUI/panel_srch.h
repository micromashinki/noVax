#pragma once
class SrchPanel : public wxPanel {
public:
	SrchPanel(const wxSize&);
	void setSurface();
	int GetWidth();
	int GetHeight();
private:
	wxSize size;
};