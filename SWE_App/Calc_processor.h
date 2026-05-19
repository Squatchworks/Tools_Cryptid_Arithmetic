#pragma once
#include "wx/wx.h"
#include "Window.h"
#include <wx/tokenzr.h>
#include <vector>
#include <cmath>
#include <queue>

class Calc_processor
{
public:
	static Calc_processor& GetInstance(Window* window = nullptr);

	std::queue<std::string> ProcessEquation(const wxString& equation);
	double evaluateRPNequation(std::queue<std::string>& outputqueue);

	std::vector<std::string> tokenizeEquation(const wxString& equation);

	bool NumCheck(const std::string& Number);
	bool checkOperator(const std::string& operater);
	int CheckPrecedence(const std::string& operater);
	bool isLeftAssociative(const std::string& operater);
	bool checkFunction(const std::string& function);
	bool checkUnaryOperator(const std::string& character);

	double applyUnaryOperator(const std::string& operater, double number);
	double applyFunction(const std::string& func, double value);
	double applyOperator(const std::string& operater, double Num1, double Num2);

private:
	Calc_processor(Window* window) : window(window)
	{}
	Calc_processor(const Calc_processor&) = delete;
	Calc_processor& operator=(const Calc_processor&) = delete;

	Window* window;
};

