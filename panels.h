#pragma once
#include "start.h"

class MemPanel : public wxPanel {
public:
	MemPanel(Okno*);
	int GetWidth();
	int GetHeight();
private:
	wxSize size;
};

class RegPanel : public wxPanel {
public:
	RegPanel(Okno*);
	int GetWidth();
	int GetHeight();
private:
	wxSize size;
};

class VarPanel : public wxPanel {
public:
	VarPanel(Okno*);
	int GetWidth();
	int GetHeight();
private:
	wxSize size;
};

class MsgPanel : public wxPanel {
public:
	MsgPanel(Okno*);
	int GetWidth();
	int GetHeight();
private:
	wxSize size;
};