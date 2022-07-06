#pragma once
#include "start.h"

class MemPanel : public wxPanel {
public:
	MemPanel(Okno*);
};

class RegPanel : public wxPanel {
public:
	RegPanel(Okno*);
};

class VarPanel : public wxPanel {
public:
	VarPanel(Okno*);
};

class MsgPanel : public wxPanel {
public:
	MsgPanel(Okno*);
};