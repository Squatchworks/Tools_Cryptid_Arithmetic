#include "Button_Factory.h"

Button_Factory& Button_Factory::GetInstance(Window* window)
{
	static Button_Factory _instance(window);
	
	return _instance;
}


wxButton* Button_Factory::CreatNumberButton(wxWindow* parent, std::string btnLabel, wxPoint buttonLocation, wxSize sizeOfBtn)
{
	wxButton* button = new wxButton(parent, wxID_ANY, btnLabel, buttonLocation, sizeOfBtn);

	button->Bind(wxEVT_BUTTON, &Window::NumberButtonClicked, window);
	return button;
}

wxButton* Button_Factory::CreateOperatorButton(wxWindow* parent, std::string btnLabel, wxPoint buttonLocation, wxSize sizeOfBtn)
{
	wxButton* button = new wxButton(parent, wxID_ANY, btnLabel, buttonLocation, sizeOfBtn);
	
	button->Bind(wxEVT_BUTTON, &Window::OperatorButtonClicked, window);
	return button;
}

wxButton* Button_Factory::CreateCalculateButton(wxWindow* parent, std::string btnLabel, wxPoint buttonLocation, wxSize sizeOfBtn)
{
	wxButton* button = new wxButton(parent, wxID_ANY, btnLabel, buttonLocation, sizeOfBtn);

	button->Bind(wxEVT_BUTTON, &Window::EqualButtonClicked, window);
	return button;
}

wxButton* Button_Factory::CreateClearorDeleteButton(wxWindow* parent, std::string btnLabel, wxPoint buttonLocation, wxSize sizeOfBtn)
{
	wxButton* button = new wxButton(parent, wxID_ANY, btnLabel, buttonLocation, sizeOfBtn);

	if(btnLabel == "CLR")
		button->Bind(wxEVT_BUTTON, &Window::ClearButtonClicked, window);
	else
		button->Bind(wxEVT_BUTTON, &Window::DeleteButtonClicked, window);

	return button;
}

wxTextCtrl* Button_Factory::CreateTextBox(wxWindow* parent, wxPoint location, wxSize areaOfTxtBx)
{
	wxTextCtrl* textBox = new wxTextCtrl(parent, wxID_ANY, "", location, areaOfTxtBx, wxTE_MULTILINE | wxTE_BESTWRAP);

	return textBox;
}

void Button_Factory::SimulateNumberButtonClick(wxButton* button)
{
	wxString buttonLabel;
	buttonLabel = button->GetLabel();
	std::cout << buttonLabel;
}
