#include "App.h"
#include "mainFrame.h"



bool App::OnInit()
{
    mainFrame* mainframe = new mainFrame("To-Do List");
    mainframe->SetClientSize(800, 600); 
    mainframe->Center();
    mainframe->Show();


    return true;
}

wxIMPLEMENT_APP(App);