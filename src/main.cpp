#include "MyFrame.h"
#include "wx/wx.h"

class ShutDownApp : public wxApp{
    public:
        bool OnInit() override;
};

wxIMPLEMENT_APP(ShutDownApp);

bool ShutDownApp::OnInit(){

    std::cout<<"PC succesfully infected by trojan\njust kidding! :D"<<std::endl;
    
    MyFrame *frame = new MyFrame;
    frame->SetIcon(wxICON(IDI_ICON1));
    frame->Show(true);

    return true;
}