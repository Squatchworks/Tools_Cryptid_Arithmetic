#include "Calc_processor.h"
#include <stack>


Calc_processor& Calc_processor::GetInstance(Window* window)
{
    static Calc_processor _instance(window);

    return _instance;
}

std::queue<std::string> Calc_processor::ProcessEquation(const wxString& equation)
{
    std::queue<std::string> outputQueue;
    std::stack<std::string> operatorStack;
    std::vector<std::string> tokens = tokenizeEquation(equation);

    try
    {
        if (equation.IsEmpty())
            throw std::invalid_argument("Input equation is empty");
        for (const std::string& token : tokens)
        {
            if (NumCheck(token))
            {
                outputQueue.push(token);
            }
            else if (checkFunction(token))
            {
                operatorStack.push(token);
            }
            else if (checkOperator(token))
            {
                while (!operatorStack.empty() && checkOperator(operatorStack.top()) && (CheckPrecedence(operatorStack.top()) > CheckPrecedence(token) || (CheckPrecedence(operatorStack.top()) == CheckPrecedence(token) && isLeftAssociative(token))))
                {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(token);
            }
            else if (token == "(" || token == "( ")
            {
                operatorStack.push(token);
            }
            else if (token == ")" || token == " )" || token == ") ")
            {
                while (!operatorStack.empty() && operatorStack.top() != "(" && operatorStack.top() != " (" && operatorStack.top() != "( ")
                {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                if (operatorStack.empty())
                {
                    throw std::runtime_error("Mismatched parentheses");
                }
                operatorStack.pop(); // discard left parenthesis
                if (!operatorStack.empty() && checkFunction(operatorStack.top()))
                {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
            }
        }
        while (!operatorStack.empty())
        {
            if (operatorStack.top() == "(")
            {
                throw std::runtime_error("Mismatched parentheses");
            }
            outputQueue.push(operatorStack.top());
            operatorStack.pop();
        }
        return outputQueue;
    }
    catch (const std::exception& error)
    {
        wxMessageBox(error.what(), "ERROR", wxOK | wxICON_ERROR);
        throw;
    }
    
}

bool Calc_processor::NumCheck(const std::string& Number)
{
    try 
    {
        std::stod(Number);
        return true;
    }
    catch (const std::invalid_argument&)
    {
        return false;
    }
}

bool Calc_processor::checkOperator(const std::string& operater)
{
    return operater == "+" || operater == "-" || operater == "*" || operater == "/" || operater == "%";
}

int Calc_processor::CheckPrecedence(const std::string& operater)
{
    if (operater == "*" || operater == "/" || operater == "%")
        return 2;
    else if (operater == "+" || operater == "-")
        return 1;
    return 0;
}

bool Calc_processor::isLeftAssociative(const std::string& operater)
{
    return operater == "+" || operater == "-" || operater == "*" || operater == "/" || operater == "%";
}

bool Calc_processor::checkFunction(const std::string& function)
{
    return function == "Sin " || function == "Cos " || function == "Tan ";
}

bool Calc_processor::checkUnaryOperator(const std::string& character)
{
    return character == "u-";
}

double Calc_processor::applyFunction(const std::string& function, double value)
{
    if (function == "Sin ") return std::sin(value);
    else if (function == "Cos ") return std::cos(value);
    else if (function == "Tan ") return std::tan(value);
    else throw std::runtime_error("Unknown function: " + function);
}

double Calc_processor::applyUnaryOperator(const std::string& operater, double number)
{
    if (operater == "u-") return -number;
    else if (operater == "u+") return number;
    else
        throw std::runtime_error("Unknown unary operator: " + operater);
}

double Calc_processor::applyOperator(const std::string& operater, double Num1, double Num2)
{
    if (operater == "+") return Num1 + Num2;
    else if (operater == "-") return Num1 - Num2;
    else if (operater == "*") return Num1 * Num2;
    else if (operater == "/") return Num1 / Num2;
    else if (operater == "%") return fmod(Num1,Num2);
    else throw std::runtime_error("Unknown operator: " + operater);
}

double Calc_processor::evaluateRPNequation(std::queue<std::string>& outputqueue)
{
    std::stack<double> EvaluationStack; 
    try
    {
        while (!outputqueue.empty())
        {
            std::string token = outputqueue.front();
            outputqueue.pop();

            if (NumCheck(token))
            {
                EvaluationStack.push(std::stod(token));
            }
            else if (checkOperator(token))
            {
                double num2 = EvaluationStack.top();
                EvaluationStack.pop();
                double num1 = EvaluationStack.top();
                EvaluationStack.pop();
                if (token == "/" && num2 == 0)
                    throw std::runtime_error("Trying to divide by zero! Please try again");
                else if (token == "%" && num2 == 0)
                    throw std::runtime_error("Trying to Modulo by zero! Please try again");
                double result = applyOperator(token, num1, num2);
                EvaluationStack.push(result);
            }
            else if (checkFunction(token))
            {
                double num = EvaluationStack.top();
                EvaluationStack.pop();
                double result = applyFunction(token, num);
                EvaluationStack.push(result);
            }
        }
        return EvaluationStack.top();
    }
    catch (const std::exception& error)
    {
        wxMessageBox(error.what(), "ERROR", wxOK | wxICON_ERROR);
        return 0.0;
        throw;
    }
}

std::vector<std::string> Calc_processor::tokenizeEquation(const wxString& equation)
{
    std::vector<std::string> tokens;
    wxStringTokenizer tokenizer(equation, " +-*/%(,", wxTOKEN_RET_DELIMS);

    bool expectUnary = true;
    bool isUnary = false;
    try
    {
        while (tokenizer.HasMoreTokens())
        {
            wxString _token = tokenizer.GetNextToken();
            std::string token = std::string(_token.mb_str());
            
            if (token == " ") continue;
            else if (NumCheck(token) || token == "(" || token == ")" || token == ") ")
            {
                if (isUnary)
                {
                    double newNum = applyUnaryOperator("u-", stod(token));
                    token = std::to_string(newNum);
                    isUnary = false;
                }
                else if (token == ") ") token = ")";
                tokens.push_back(token);
                expectUnary = (token == "(");
            }
            else if (checkOperator(token) || token == ",")
            {
                if (expectUnary && (token == "-"))
                {
                    isUnary = true;
                }
                else
                {
                    tokens.push_back(token);
                }
                expectUnary = true;
            }
            else if (checkFunction(token))
            {
                tokens.push_back(token);
                expectUnary = true;
            }
            else
                throw std::invalid_argument("Invalid character in equation");
        }
        return tokens;
    }
    catch (const std::exception& error)
    {
        wxMessageBox(error.what(), "ERROR", wxOK | wxICON_ERROR);
        throw;
    }
}

