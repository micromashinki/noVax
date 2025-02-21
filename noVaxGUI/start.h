#pragma once

extern Cprocessor cp;
extern MemPanel* mempanel;
extern RegPanel* regpanel;
extern MsgPanel* msgpanel;

void changeRF();

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
	void makeStep(wxCommandEvent&);
	void executeProgram(wxCommandEvent&);

	void openFile(wxCommandEvent&);
	void saveFile(wxCommandEvent&);
private:
	wxSize size;
	
	wxMenu* menuFile;
	wxMenu* menuFile2;
	wxMenu* menuFile3;
	wxMenu* menuFile4;

	wxDECLARE_EVENT_TABLE();
};

