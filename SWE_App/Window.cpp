
#include <wx/tokenzr.h>
#include <vector>
#include <cmath>
#include "Button_Factory.h"
#include "Calc_processor.h"

wxBEGIN_EVENT_TABLE(Window, wxFrame)
	EVT_BUTTON(10001, EqualButtonClicked)
	EVT_BUTTON(10019, ClearButtonClicked)
	EVT_BUTTON(10020, DeleteButtonClicked)
wxEND_EVENT_TABLE()

Window::Window(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxPoint(100, 100), wxSize(490, 380))
{
	// --- Branding Colors ---
	wxColour bgDark(18, 18, 20);        // near-black background
	wxColour accentGreen(30, 180, 100); // forest green operators
	wxColour accentAmber(220, 160, 40); // amber numbers
	wxColour accentRed(200, 50, 50);    // red for CLR/DEL
	wxColour textLight(220, 220, 210);  // off-white text

	this->SetBackgroundColour(bgDark);
	this->SetTitle("Cryptid Arithmetic");

	Button_Factory& buttonFactory = Button_Factory::GetInstance(this);

	TextBox = buttonFactory.GetInstance().CreateTextBox(this, wxPoint(210, 10), wxSize(250, 200));
	EqualButton = buttonFactory.GetInstance().CreateCalculateButton(this, "=", wxPoint(110, 210), wxSize(50, 50));
	PointButton = buttonFactory.GetInstance().CreatNumberButton(this, ".", wxPoint(60, 210), wxSize(50, 50));
	ZeroButton = buttonFactory.GetInstance().CreatNumberButton(this, "0", wxPoint(10, 210), wxSize(50, 50));
	OneButton = buttonFactory.GetInstance().CreatNumberButton(this, "1", wxPoint(10, 160), wxSize(50, 50));
	TwoButton = buttonFactory.GetInstance().CreatNumberButton(this, "2", wxPoint(60, 160), wxSize(50, 50));
	ThreeButton = buttonFactory.GetInstance().CreatNumberButton(this, "3", wxPoint(110, 160), wxSize(50, 50));
	FourButton = buttonFactory.GetInstance().CreatNumberButton(this, "4", wxPoint(10, 110), wxSize(50, 50));
	FiveButton = buttonFactory.GetInstance().CreatNumberButton(this, "5", wxPoint(60, 110), wxSize(50, 50));
	SixButton = buttonFactory.GetInstance().CreatNumberButton(this, "6", wxPoint(110, 110), wxSize(50, 50));
	SevenButton = buttonFactory.GetInstance().CreatNumberButton(this, "7", wxPoint(10, 60), wxSize(50, 50));
	EightButton = buttonFactory.GetInstance().CreatNumberButton(this, "8", wxPoint(60, 60), wxSize(50, 50));
	NineButton = buttonFactory.GetInstance().CreatNumberButton(this, "9", wxPoint(110, 60), wxSize(50, 50));
	PlusButton = buttonFactory.GetInstance().CreateOperatorButton(this, " + ", wxPoint(10, 10), wxSize(50, 50));
	MinusButton = buttonFactory.GetInstance().CreateOperatorButton(this, " - ", wxPoint(60, 10), wxSize(50, 50));
	MultiplyButton = buttonFactory.GetInstance().CreateOperatorButton(this, " * ", wxPoint(110, 10), wxSize(50, 50));
	DivideButton = buttonFactory.GetInstance().CreateOperatorButton(this, " / ", wxPoint(160, 10), wxSize(50, 50));
	ModuloButton = buttonFactory.GetInstance().CreateOperatorButton(this, " % ", wxPoint(160, 60), wxSize(50, 50));
	MakeNegativeButton = buttonFactory.GetInstance().CreateOperatorButton(this, "-", wxPoint(160, 110), wxSize(50, 50));
	ClearButton = buttonFactory.GetInstance().CreateClearorDeleteButton(this, "CLR", wxPoint(160, 160), wxSize(50, 50));
	DeleteButton = buttonFactory.GetInstance().CreateClearorDeleteButton(this, "DEL", wxPoint(160, 210), wxSize(50, 50));
	SinButton = buttonFactory.GetInstance().CreateOperatorButton(this, "Sin ", wxPoint(210, 210), wxSize(50, 50));
	CosButton = buttonFactory.GetInstance().CreateOperatorButton(this, "Cos ", wxPoint(260, 210), wxSize(50, 50));
	TanButton = buttonFactory.GetInstance().CreateOperatorButton(this, "Tan ", wxPoint(310, 210), wxSize(50, 50));
	ParenthesesOpen = buttonFactory.GetInstance().CreatNumberButton(this, "(", wxPoint(360, 210), wxSize(50, 50));
	ParenthesesClose = buttonFactory.GetInstance().CreatNumberButton(this, " )", wxPoint(410, 210), wxSize(50, 50));

	// --- Apply Colors ---
	// Number buttons — amber
	for (wxButton* btn : { ZeroButton, OneButton, TwoButton, ThreeButton,
						   FourButton, FiveButton, SixButton, SevenButton,
						   EightButton, NineButton, PointButton, ParenthesesOpen, ParenthesesClose })
	{
		btn->SetBackgroundColour(wxColour(40, 38, 30));
		btn->SetForegroundColour(accentAmber);
	}

	// Operator buttons — green
	for (wxButton* btn : { PlusButton, MinusButton, MultiplyButton, DivideButton,
						   ModuloButton, MakeNegativeButton, SinButton, CosButton, TanButton })
	{
		btn->SetBackgroundColour(wxColour(20, 40, 30));
		btn->SetForegroundColour(accentGreen);
	}

	// Equal button — bright green
	EqualButton->SetBackgroundColour(wxColour(20, 140, 70));
	EqualButton->SetForegroundColour(textLight);

	// CLR / DEL — red
	ClearButton->SetBackgroundColour(wxColour(60, 20, 20));
	ClearButton->SetForegroundColour(accentRed);
	DeleteButton->SetBackgroundColour(wxColour(60, 20, 20));
	DeleteButton->SetForegroundColour(accentRed);

	// TextBox styling
	TextBox->SetBackgroundColour(wxColour(12, 12, 14));
	TextBox->SetForegroundColour(textLight);

	TextOutput = std::cout.rdbuf();
	std::cout.rdbuf(TextBox);
}

Window::~Window()
{

}

void Window::NumberButtonClicked(wxCommandEvent& evt)
{
	wxString buttonLabel;
	wxButton* clickedButton = wxDynamicCast(evt.GetEventObject(), wxButton);
	if (clickedButton)
	{
		buttonLabel = clickedButton->GetLabel();
	}
	std::cout << buttonLabel;
	evt.Skip();
}

void Window::OperatorButtonClicked(wxCommandEvent& evt)
{
	wxString buttonLabel;
	wxButton* clickedButton = wxDynamicCast(evt.GetEventObject(), wxButton);
	if (clickedButton)
	{
		buttonLabel = clickedButton->GetLabel();
	}
	std::cout << buttonLabel;
	evt.Skip();
}

void Window::EqualButtonClicked(wxCommandEvent& evt)
{
	try
	{
		wxString expression = TextBox->GetValue();
		Calc_processor& processor = Calc_processor::GetInstance(this);
		std::queue<std::string> RPNEquation = processor.ProcessEquation(expression);
		double result = processor.evaluateRPNequation(RPNEquation);
		TextBox->Clear();
		std::cout << result;
		evt.Skip();
	}
	catch (const std::exception& error)
	{
		Clear();
		TextBox->SetFocus();
	}
}

void Window::ClearButtonClicked(wxCommandEvent& evt)
{
	TextBox->Clear();
	evt.Skip();
}

void Window::DeleteButtonClicked(wxCommandEvent& evt)
{
	wxString TextFromTextBox = TextBox->GetValue();

	if (!TextFromTextBox.empty())
	{
		TextFromTextBox.RemoveLast();
		TextBox->SetValue(TextFromTextBox);
	}
	evt.Skip();
}

void Window::Clear()
{
	TextBox->Clear();
	TextBox->SetFocus();
}

void Window::SimulateButtonClick(wxButton* button)
{
	wxString buttonLabel = button->GetLabel();
	std::cout << buttonLabel;
}

wxTextCtrl* Window::GetTextBox()
{
	return TextBox;
}

wxButton* Window::GetClearButton()
{
	return ClearButton;
}

wxButton* Window::GetDeleteButton()
{
	return DeleteButton;
}
