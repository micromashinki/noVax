#include "panels.h"

MsgPanel::MsgPanel(const wxSize& size) : wxPanel() {this->size = size;}

int MsgPanel::GetWidth() { return size.GetWidth(); }
int MsgPanel::GetHeight() { return size.GetHeight(); }