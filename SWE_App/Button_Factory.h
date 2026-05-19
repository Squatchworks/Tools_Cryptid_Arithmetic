#pragma once
#include "wx/wx.h"
#include "Window.h"

class Button_Factory
{
public:

	static Button_Factory& GetInstance(Window* window = nullptr);

	wxButton* CreatNumberButton(wxWindow* parent, std::string btnLabel, wxPoint buttonLocation, wxSize sizeOfBtn);

	wxButton* CreateOperatorButton(wxWindow* parent, std::string btnLabel, wxPoint buttonLocation, wxSize sizeOfBtn);

	wxButton* CreateCalculateButton(wxWindow* parent, std::string btnLabel, wxPoint buttonLocation, wxSize sizeOfBtn);

	wxButton* CreateClearorDeleteButton(wxWindow* parent, std::string btnLabel, wxPoint buttonLocation, wxSize sizeOfBtn);

	wxTextCtrl* CreateTextBox(wxWindow* parent, wxPoint location, wxSize areaOfTxtBx);

	void SimulateNumberButtonClick(wxButton* button);

private:
	Button_Factory(Window* window) : window(window)
	{}

	Button_Factory(const Button_Factory&) = delete;
	Button_Factory& operator=(const Button_Factory&) = delete;

	Window* window;
};

