#pragma once
#include <wx/app.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/scrolbar.h>
#include <wx/grid.h>
#include <wx/msgdlg.h>

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
};

