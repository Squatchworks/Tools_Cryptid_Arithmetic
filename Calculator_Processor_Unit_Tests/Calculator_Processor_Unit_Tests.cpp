//#include "pch.h"
#include "CppUnitTest.h"
#include "../SWE_App/Calc_processor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorProcessorUnitTests
{
	Window* window = new Window("Test Window");

	std::queue<std::string> createQueue(std::vector<std::string> vec)
	{
		std::queue<std::string> queue;
		for (const std::string& elem : vec)
		{
			queue.push(elem);
		}
		return queue;
	}

	TEST_CLASS(CalculatorProcessorUnitTests)
	{
	public:
		TEST_METHOD(TestingTokenizeMethod1)
		{
			Calc_processor& processor = Calc_processor::GetInstance(window);

			struct TestCase
			{
				wxString equation;
				std::vector<std::string> expectedTokens;
			};

			std::vector<TestCase> testCases =
			{
				{ "6 + 9", {"6 " ,"+","9"}},
				{ "50 - 6 * 7", {"50 ","-","6 ","*","7"}},
				{"5 + 10 * ( 30 - 25 )", {"5 ","+","10 ","*","(","30 ","-","25 ",")"}},
				{ "( 5 - 2 ) * 30 / 3", {"(","5 " ,"-","2 ",")","*","30 ","/","3"}},
				{ "Sin ( 45 )", {"Sin ", "(", "45 ", ")"}},
				{ "3.14 * 55", {"3.14 ", "*", "55"}}
			};

			for (const auto& testCase : testCases)
			{
				std::vector<std::string> tokens = processor.tokenizeEquation(testCase.equation);

				Assert::AreEqual(testCase.expectedTokens.size(), tokens.size(), L"Token count mismatch");

				for (size_t i = 0; i < testCase.expectedTokens.size(); ++i)
				{
					Assert::AreEqual(testCase.expectedTokens[i], tokens[i], L"Token mismatch");
				}
			}
		}           

		TEST_METHOD(TestingApplyUnaryOperator2)
		{
			Calc_processor& processor = Calc_processor::GetInstance(window);

			std::string Unary = "u-";
			double number = 69;
			double expectedOutput = -69;

			Assert::AreEqual(expectedOutput, processor.applyUnaryOperator(Unary, number));
			Assert::AreNotEqual(number, processor.applyUnaryOperator(Unary, number));

		}

		TEST_METHOD(TestingCheckUnaryMethod3)
		{
			Calc_processor& processor = Calc_processor::GetInstance(window);

			std::string Unary = "u-";
			std::string falseUnary = "-";
			
			Assert::IsTrue(processor.checkUnaryOperator(Unary));
			Assert::IsFalse(processor.checkUnaryOperator(falseUnary));

		}

		TEST_METHOD(TestingNumCheck4)
		{
			Calc_processor& processor = Calc_processor::GetInstance(window);

			std::string Number = "69";
			std::string nonNumber = "sixty-Nine";

			Assert::IsTrue(processor.NumCheck(Number));
			Assert::IsFalse(processor.NumCheck(nonNumber));
		}

		TEST_METHOD(TestingAddition6)
		{
			Calc_processor& processor = Calc_processor::GetInstance(window);

			struct TestCase
			{
				double num1;
				double num2;
				double returnValue;
				std::string operater;
			};

			std::vector<TestCase> testCases =
			{
				{5.0, 6.0, 11.0, "+"},
				{11.0, 22.0, 33.0, "+"},
				{69.0, 758.5, 827.5, "+"}
			};

			for(TestCase& testCase : testCases)
			{
				Assert::AreEqual(testCase.returnValue, processor.applyOperator(testCase.operater, testCase.num1, testCase.num2));
			}
		}

		TEST_METHOD(TestingSubtraction7)
		{
			Calc_processor& processor = Calc_processor::GetInstance(window);

			struct TestCase
			{
				double num1;
				double num2;
				double returnValue;
				std::string operater;
			};

			std::vector<TestCase> testCases =
			{
				{5.0, 6.0, -1.0, "-"},
				{11.0, 22.0, -11.0, "-"},
				{758.5, 69.0, 689.5, "-"}
			};

			for (TestCase& testCase : testCases)
			{
				Assert::AreEqual(testCase.returnValue, processor.applyOperator(testCase.operater, testCase.num1, testCase.num2));
			}
		}

		TEST_METHOD(TestingMultiplication8)
		{
			Calc_processor& processor = Calc_processor::GetInstance(window);

			struct TestCase
			{
				double num1;
				double num2;
				double returnValue;
				std::string operater;
			};

			std::vector<TestCase> testCases =
			{
				{5.0, 6.0, 30.0, "*"},
				{11.0, 22.0, 242.0, "*"},
				{69.0, 758.5, 52336.5, "*"}
			};

			for (TestCase& testCase : testCases)
			{
				Assert::AreEqual(testCase.returnValue, processor.applyOperator(testCase.operater, testCase.num1, testCase.num2));
			}
		}

		TEST_METHOD(TestingModulo9)
		{
			Calc_processor& processor = Calc_processor::GetInstance(window);

			struct TestCase
			{
				double num1;
				double num2;
				double returnValue;
				std::string operater;
			};

			std::vector<TestCase> testCases =
			{
				{5.0, 6.0, 5.0, "%"},
				{11.0, 2.0, 1.0, "%"},
				{758.5, 69.0, 68.5, "%"}
			};

			for (TestCase& testCase : testCases)
			{
				Assert::AreEqual(testCase.returnValue, processor.applyOperator(testCase.operater, testCase.num1, testCase.num2));
			}
		}

		TEST_METHOD(TestingDivision10)
		{
			Calc_processor& processor = Calc_processor::GetInstance(window);

			struct TestCase
			{
				double num1;
				double num2;
				double returnValue;
				std::string operater;
			};

			std::vector<TestCase> testCases =
			{
				{5.0, 3.0, 1.6666666666666667, "/"},
				{10.0, 2.0, 5.0, "/"},
				{758.5, 69.0, 10.992753623188406, "/"}
			};

			for (TestCase& testCase : testCases)
			{
				Assert::AreEqual(testCase.returnValue, processor.applyOperator(testCase.operater, testCase.num1, testCase.num2));
			}
		}

		TEST_METHOD(TestingTrigFunctions11)
		{
			Calc_processor& processor = Calc_processor::GetInstance(window);

			struct TestCase
			{
				std::string operater;
				double number;
				double returnValue;
			};

			std::vector<TestCase> testCases =
			{
				{"Sin ", 30.0, -0.98803162409286183},
				{"Cos ", 60.0, -0.95241298041515632},
				{"Tan ", 45.0, 1.6197751905438615}
			};

			for (TestCase& testCase : testCases)
			{
				Assert::AreEqual(testCase.returnValue, processor.applyFunction(testCase.operater, testCase.number));
			}
		}
	};
}
