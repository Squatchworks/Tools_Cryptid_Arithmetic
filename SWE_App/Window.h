#pragma once
#include "wx/wx.h"

class Window : public wxFrame
{
protected:
	wxTextCtrl* TextBox = nullptr;
	wxButton* EqualButton = nullptr;
	wxButton* PointButton = nullptr;
	wxButton* ZeroButton = nullptr;
	wxButton* OneButton = nullptr;
	wxButton* TwoButton = nullptr;
	wxButton* ThreeButton = nullptr;
	wxButton* FourButton = nullptr;
	wxButton* FiveButton = nullptr;
	wxButton* SixButton = nullptr;
	wxButton* SevenButton = nullptr;
	wxButton* EightButton = nullptr;
	wxButton* NineButton = nullptr;
	wxButton* PlusButton = nullptr;
	wxButton* MinusButton = nullptr;
	wxButton* MultiplyButton = nullptr;
	wxButton* DivideButton = nullptr;
	wxButton* ModuloButton = nullptr;
	wxButton* MakeNegativeButton = nullptr;
	wxButton* ClearButton = nullptr;
	wxButton* DeleteButton = nullptr;
	wxButton* SinButton = nullptr;
	wxButton* CosButton = nullptr;
	wxButton* TanButton = nullptr;
	wxButton* ParenthesesOpen = nullptr;
	wxButton* ParenthesesClose = nullptr;

	char operater;
	double NumValue1, NumValue2;
	int tracker = 0;
public:
	Window(const wxString& title);
	~Window();

	std::streambuf* TextOutput = nullptr;

	void NumberButtonClicked(wxCommandEvent& evt);
	void OperatorButtonClicked(wxCommandEvent& evt);
	void EqualButtonClicked(wxCommandEvent& evt);
	
	void ClearButtonClicked(wxCommandEvent& evt);
	void DeleteButtonClicked(wxCommandEvent& evt);
	void Clear();

	void SimulateButtonClick(wxButton* button);

	wxTextCtrl* GetTextBox();
	wxButton* GetClearButton();
	wxButton* GetDeleteButton();

private:

	wxDECLARE_EVENT_TABLE();
};

