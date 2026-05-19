//#include "pch.h"
#include "CppUnitTest.h"
#include "../SWE_App/Button_Factory.h"
#include "../SWE_App/Window.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ButtonFactoryTesting
{
	Window* window = new Window("Test Window");
	Button_Factory& buttonFactory = Button_Factory::GetInstance(window);

	TEST_CLASS(ButtonFactoryTesting)
	{
	 public:
		
/*1*/	TEST_METHOD(TestingCreationOfSingleton)
		{
			Button_Factory& _instance1 = Button_Factory::GetInstance(window);

			Assert::IsTrue(&buttonFactory == &_instance1, L"Button_Factory instances are not the same");
		} 

/*2*/	TEST_METHOD(TestingCreationOfNumberButton)
		{
			wxButton* button = buttonFactory.CreatNumberButton(window, "2", wxPoint(50, 50), wxSize(5, 5));
			std::string check = "2";
			Assert::AreEqual(check, button->GetLabel().ToStdString());
		}  

/*3*/	TEST_METHOD(TestingCreationOfOperatorButton)
		{
		wxButton* button = buttonFactory.CreateOperatorButton(window, "*", wxPoint(50, 60), wxSize(75, 50));
		std::string btnsLabel = "*";
		Assert::AreEqual(btnsLabel, button->GetLabel().ToStdString());
		}

/*4*/	TEST_METHOD(TestingCreationOfClearButton)
		{
		wxButton* button =	buttonFactory.CreateClearorDeleteButton(window, "CLR", wxPoint(1, 1), wxSize(5, 5));
		std::string label = "CLR";
		Assert::AreEqual(label, button->GetLabel().ToStdString());
		}

/*5*/	TEST_METHOD(TestingCreationOfTextBox)
		{
		wxTextCtrl* textBox = buttonFactory.CreateTextBox(window, wxPoint(55, 65), wxSize(77, 88));
		Assert::IsNotNull(textBox);
		}

/*6*/	TEST_METHOD(TestingThatButtonDisplaysProperly)
		{
		std::stringstream buffer;
		std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

		wxButton* button = buttonFactory.CreatNumberButton(window, "0", wxPoint(0, 0), wxSize(5, 5));

		buttonFactory.SimulateNumberButtonClick(button);

		std::cout.rdbuf(oldCoutBuffer);

		std::string output = buffer.str();
		std::string expected = "0";

		Assert::AreEqual(expected, output);
		}

/*7*/	TEST_METHOD(TestingCreationOfEqualButton)
		{
		wxButton* button = buttonFactory.CreateCalculateButton(window, "=", wxPoint(33, 44), wxSize(3, 3));
		std::string label = "=";
		Assert::AreEqual(label, button->GetLabel().ToStdString());
		}

/*8*/	TEST_METHOD(TestingThatTextControlDisplaysCorrectButtonPress)
		{
		wxButton* button = buttonFactory.CreatNumberButton(window, "69", wxPoint(0, 0), wxSize(6, 9));

		window->SimulateButtonClick(button);

		wxTextCtrl* textBoxFromWindow = window->GetTextBox();
		std::string expectedOutput = "69";

		Assert::AreEqual(expectedOutput, textBoxFromWindow->GetValue().ToStdString());
		}

/*9*/	TEST_METHOD(TestingThatClearReturnsEmptyTextBox)
		{
		wxButton* CLRButton = window->GetClearButton();
		
		window->GetTextBox()->SetValue("This is Awesome!");
		wxCommandEvent clearEvent(wxEVT_BUTTON, CLRButton->GetId());
		CLRButton->ProcessCommand(clearEvent);
		
		std::string emptyString = "";

		Assert::AreEqual(emptyString, window->GetTextBox()->GetValue().ToStdString());
		}

/*10*/	TEST_METHOD(TestingThatDeleteButtonDeletesOneCharacter)
		{
		std::string value = "Programming Rulez!";
		
		wxButton* DeleteButton = window->GetDeleteButton();
		window->GetTextBox()->SetValue(value);
		wxCommandEvent DeleteEvent(wxEVT_BUTTON, DeleteButton->GetId());
		DeleteButton->ProcessCommand(DeleteEvent);

		std::string returnString = value.substr(0, value.size() - 1);
		
		Assert::AreEqual(returnString, window->GetTextBox()->GetValue().ToStdString());
		}

	};

	
}
