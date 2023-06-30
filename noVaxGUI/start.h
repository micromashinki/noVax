#pragma once

extern Cprocessor cp;
extern MemPanel* mempanel;
extern RegPanel* regpanel;
extern MsgPanel* msgpanel;

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

	void openFile(wxCommandEvent&);
private:
	wxSize size;
	
	wxMenu* menuFile;
	wxMenu* menuFile2;
	wxMenu* menuFile3;
	wxMenu* menuFile4;

	wxDECLARE_EVENT_TABLE();
};

