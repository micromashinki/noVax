#pragma once

class InitClass : public wxApp {
public:
	virtual bool OnInit();
};

class Okno : public wxFrame {
public:
	Okno(const wxString&, const wxSize&);
	int GetWidth();
	int GetHeight();
private:
	wxSize size;
	MemPanel* mempanel;
	RegPanel* regpanel;
	SrchPanel* srchpanel;
	MsgPanel* msgpanel;
};

