#include "panels.h"

bool InitClass::OnInit() {
    Okno* frame = new Okno("EblR-22", wxSize(1089, 700));
    frame->Show(true);
	return true;
}

Okno::Okno(const wxString& str, const wxSize& s) : wxFrame (NULL, wxID_ANY, str, wxDefaultPosition, s) {
    size = s;
    SetMinSize(s);
    //SetMaxSize(s);
    MemPanel* mempanel = new MemPanel(this);
    RegPanel* regpanel = new RegPanel(this);
    wxPanel* panel_vars = new wxPanel(this, wxID_ANY, wxPoint((size.GetWidth() / 1.5) + 10, (size.GetHeight() - 250) / 1.5 + 5), wxSize(size.GetWidth() - size.GetWidth() / 1.5 - 26, (size.GetHeight() - 250) - (size.GetHeight() - 250) / 1.5 - 5));
    /*wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, ")))");
    SetMenuBar(menuBar);*/
}
int Okno::GetWidth() { return size.GetWidth(); }
int Okno::GetHeight() { return size.GetHeight();}

wxIMPLEMENT_APP(InitClass);

/*TODO:
* - оформить панельки в отдельные классы
* - заполнить панель с оперативкой
* - заполнить панель с регистрами
* - заполнить панель с переменными (?)
* - создать и заполнить панель с сообщениями
* - разобраться с обработкой всех событий
* - соединить интерфейс с вычислительной частью
* - разобраться с рисовкой и оформить тёмную тему
*/