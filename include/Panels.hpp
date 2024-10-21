
#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <iostream>

class topPanel : public wxPanel{
    public:

        struct Action{
            const char* lock = "rundll32.exe user32.dll,LockWorkStation";
            const char* shutdown = "shutdown /s";
            const char* signout = "shutdown /f";
            const char* hibernate = "shutdown /h";
            const char* restart = "shutdown /r";
        };
        Action opEvent;

        wxTimer clock;
        wxDateTime CurrTime;
        wxButton *runButton, *abortButton;
        wxComboBox *listBox;
        wxArrayString choices;
        wxStaticText *hourText, *minText, *secText;
        wxSpinCtrl *spinHours, *spinMin, *spinSec;
        const char *messStr;
        int opPicked;
        bool isComplete;
        wxPanel *theParent;
        
        topPanel(wxPanel* parent);        
        void OnUpdateDisplayedTime(wxTimerEvent& event);
        void OnTimeStop(wxCommandEvent& event);
        void updateTime();
        void updateFunc();
        void onButton(wxCommandEvent &event);

};

class bottomPanel : public wxPanel{
    public:
        wxStaticText *mText, *timeText;

        bottomPanel(wxPanel* parent); 
};

enum{
    ID_Combo = 1,
    ID_B1 = 2,
    ID_B2 = 3

};