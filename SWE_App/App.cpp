#include "App.h"
#include "Window.h" 


bool App::OnInit()
{
    window = new Window("My Calculator");
    window->Show(true);
    return true;
}

wxIMPLEMENT_APP(App);