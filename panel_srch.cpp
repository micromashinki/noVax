#include "panels.h"

SrchPanel::SrchPanel(const wxSize& size) : wxPanel() {this->size = size;}
int SrchPanel::GetWidth() { return size.GetWidth(); }
int SrchPanel::GetHeight() { return size.GetHeight(); }