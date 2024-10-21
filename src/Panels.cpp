#include "Panels.hpp"
#include "MyFrame.h"

MyFrame *com;

topPanel::topPanel(wxPanel *parent) 
        : wxPanel(parent, -1, wxPoint(10,10), wxSize(-1, -1), wxBORDER_SUNKEN){

            theParent = parent;
            this->SetBackgroundColour(wxColor(140, 140, 230));
            
            opPicked = -1;            

            runButton = new wxButton(this, ID_B1, "run", wxPoint(10, 100));
            Connect(ID_B1, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(topPanel::onButton));

            abortButton = new wxButton(this, ID_B2, "abort", wxPoint(100, 100));
            Connect(ID_B2, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(topPanel::OnTimeStop));

            choices.Add("shutdown");
            choices.Add("sign out");
            choices.Add("restart");
            choices.Add("hibernate");
            choices.Add("lock");

            listBox = new wxComboBox(this, ID_Combo, "what do you want?", wxPoint(10, 10), wxSize(200, 50), choices);

            hourText = new wxStaticText(this, wxID_ANY, wxT("H"), wxPoint(10, 40));
            hourText ->SetForegroundColour(wxColor(220, 220, 220));
            hourText ->SetFont(wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
            spinHours = new wxSpinCtrl(this, wxID_ANY, wxT("0"), wxPoint(10, 55), wxDefaultSize, wxSP_WRAP);
            spinHours->SetMin(0);
            spinHours->SetMax(23);

            minText = new wxStaticText(this, wxID_ANY, wxT("M"), wxPoint(70, 40));
            minText ->SetForegroundColour(wxColor(220, 220, 220));
            minText ->SetFont(wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
            spinMin = new wxSpinCtrl(this, wxID_ANY, wxT("0"), wxPoint(70,55), wxDefaultSize, wxSP_WRAP);
            spinMin->SetMin(0);
            spinMin->SetMax(59);

            secText = new wxStaticText(this, wxID_ANY, wxT("S"), wxPoint(130, 40));
            secText ->SetForegroundColour(wxColor(220, 220, 220));
            secText ->SetFont(wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
            spinSec = new wxSpinCtrl(this, wxID_ANY, wxT("0"), wxPoint(130, 55), wxDefaultSize, wxSP_WRAP);
            spinSec->SetMin(0);
            spinSec->SetMax(59);
            
            //clock.SetOwner(this);
            isComplete = false;
            clock.Bind(wxEVT_TIMER, &topPanel::OnUpdateDisplayedTime, this);
}

void topPanel::onButton(wxCommandEvent &event){
    std::cout<< "pressed" <<std::endl;

    CurrTime = wxDateTime::Now();

    com = (MyFrame *) theParent->GetParent();

    int hours = spinHours->GetValue();
    int min = spinMin->GetValue();
    int sec = spinSec->GetValue();

    std::cout<<"value is: " << spinHours->GetValue() << std::endl;

    //std::cout<<"selected: " << listBox->GetStringSelection() << std::endl;
    //system("rundll32.exe user32.dll,LockWorkStation");
    switch(listBox->GetSelection()){
        case 0:
            com->bp->mText->SetLabel(wxString::Format("PC will shutdown after %dhrs, %dminutes and %dseconds", hours, min, sec));
            opPicked = 0;
            std::cout<<"shutdown selected\n";
            break;
        case 1:
            com->bp->mText->SetLabel(wxString::Format("PC will signout after %dhrs, %dminutes and %dseconds", hours, min, sec));
            opPicked = 1;
            std::cout<<"sign out selected\n";
            break;
        case 2:
            com->bp->mText->SetLabel(wxString::Format("PC will restart after %dhrs, %dminutes and %dseconds", hours, min, sec));
            opPicked = 2;
            std::cout<<"restart selected\n";
            break;
        case 3:
            com->bp->mText->SetLabel(wxString::Format("PC will hibernate after %dhrs, %dminutes and %dseconds", hours, min, sec));
            opPicked = 3;
            std::cout<<"hibernate selected\n";
            break;
        case 4:
            com->bp->mText->SetLabel(wxString::Format("PC will lock after %dhrs, %dminutes and %dseconds", hours, min, sec));
            opPicked = 4;
            std::cout<<"lock selected\n";
            break;

        default:
            break;
    }

    CurrTime.SetHour(hours);
    CurrTime.SetMinute(min);
    CurrTime.SetSecond(sec);

    com->bp->timeText->SetLabel(CurrTime.Format("%H:%M:%S"));
    clock.Start(1000);
    updateTime();
}

void topPanel::OnTimeStop(wxCommandEvent& event){
    clock.Stop();
    updateTime();
}

void topPanel::OnUpdateDisplayedTime(wxTimerEvent& event){
    updateTime();
}

void topPanel::updateTime(){
    if(clock.IsRunning()){
        // wxDateTime nowTime = wxDateTime::Now(); 
        // wxTimeSpan elapsedTime = CurrTime-nowTime;
        // com->bp->timeText->SetLabel(elapsedTime.Format("%H:%M:%S"));

        if(opPicked == -1){
            wxLogMessage("Please Select an Action");
            clock.Stop();
        }else{
            CurrTime = CurrTime - wxTimeSpan(0, 0, 1);
            com->bp->timeText->SetLabel(CurrTime.Format("%H:%M:%S"));
            if(CurrTime.GetHour() == 0 && CurrTime.GetMinute() == 0 && CurrTime.GetSecond() <= 10 ){
                com->bp->timeText->SetForegroundColour(wxColor(255, 50, 50));

                if(CurrTime.GetHour() == 0 && CurrTime.GetMinute() == 0 && CurrTime.GetSecond() == 0 ){
                    com->bp->mText->SetLabel(wxT("BYE!"));
                    std::cout<<"time to explode\n";
                    isComplete = true;
                    if(opPicked == 0){
                        system(opEvent.shutdown);
                    }else if(opPicked == 1){
                        system(opEvent.signout);
                    }else if(opPicked == 2){
                        system(opEvent.restart);
                    }else if(opPicked == 3){
                        system(opEvent.hibernate);
                    }else if(opPicked == 4){
                        system(opEvent.lock);
                    }
                    clock.Stop();
                }
            }else
        com->bp->timeText->SetForegroundColour(wxColor(0, 0, 0));

        }
    }else{
        com->bp->timeText->SetForegroundColour(wxColor(0, 0, 0));
        com->bp->timeText->SetLabel("99:99:99");
    }


}

bottomPanel::bottomPanel(wxPanel *parent) 
            : wxPanel(parent, -1, wxPoint(10,10), wxSize(-1, -1), wxBORDER_SUNKEN){

            mText = new wxStaticText(this, wxID_ANY, wxT("Waiting for Action"), wxPoint(10, 5));
            mText->SetFont(wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

            wxString timeStr;
            timeText = new wxStaticText(this, wxID_ANY, wxT("99:99:99"), wxPoint(10, 35));
            timeText->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_HEAVY));
}