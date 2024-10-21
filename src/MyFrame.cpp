#include "MyFrame.h"

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Event Timer", wxDefaultPosition, wxSize(400, 300)){

    //set the icon
    //wxIcon icon("clockIcon.ico", wxBITMAP_TYPE_ICO);
    //SetIcon(icon);

    menuItems();

    mamaParent = new wxPanel(this, wxID_ANY);

    wxBoxSizer *hbox = new wxBoxSizer(wxVERTICAL);

    tp = new topPanel(mamaParent);
    bp = new bottomPanel(mamaParent);

    hbox->Add(tp, 2, wxEXPAND | wxALL, 2);
    hbox->Add(bp, 1, wxEXPAND | wxALL, 2);

    mamaParent->SetSizer(hbox);
    this->Center();
}

void MyFrame::menuItems(){

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "Hi...\tCtrl-H", 
                    "First Menu Item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar( menuBar );
 
    CreateStatusBar();
    SetStatusText("Welcome to the Event Timer!");
 
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("Ever Fall asleep listening to music and\nyou find music playing when you wake up!?\nwell, now you can easily schedule a shutdown!",
                 "About Event Timer", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
        wxLogMessage("Thank You For Using Event Timer!");
}