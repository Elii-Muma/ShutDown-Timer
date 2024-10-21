#pragma once
#include <wx/wx.h>
#include "Panels.hpp"

class MyFrame : public wxFrame{
    public:
        topPanel *tp;
        bottomPanel *bp;
        wxPanel *mamaParent;
        
        MyFrame(); 
    private:
        void menuItems();
        void OnHello(wxCommandEvent &event);
        void OnExit(wxCommandEvent &event);
        void OnAbout(wxCommandEvent &event);
};

enum{
    ID_Hello = 1
};