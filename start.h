#pragma once

extern Cprocessor cp;

class InitClass : public wxApp {
public:
	virtual bool OnInit();
};

class Okno : public wxFrame {
public:
	Okno(const wxString&, const wxSize&);
	int GetWidth();
	int GetHeight();

	void setDark(wxCommandEvent&);
	void showAbout(wxCommandEvent&);
	void startProgram(wxCommandEvent&);
private:
	wxSize size;
	wxMenu* menuFile;
	MemPanel* mempanel;
	RegPanel* regpanel;
	SrchPanel* srchpanel;
	MsgPanel* msgpanel;
	wxDECLARE_EVENT_TABLE();
};

