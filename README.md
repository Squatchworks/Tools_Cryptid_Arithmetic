# 🧮 Cryptid Arithmetic

> A C++ desktop calculator built with wxWidgets — featuring a full expression parser, operator precedence, trig functions, and error handling.

**By [Jacob Blackburn](https://github.com/Squatchworks) · SquatchWorks**

---

## Features

- Full mathematical expression evaluation (not just button-by-button)
- Correct operator precedence (`*` and `/` before `+` and `-`)
- Shunting-Yard algorithm converts infix expressions to Reverse Polish Notation (RPN)
- Trig functions: **Sin**, **Cos**, **Tan**
- Unary minus support (e.g. `-5 * 3`)
- Parenthesis grouping
- Division and modulo by zero error handling
- Clear (`CLR`) and Delete (`DEL`) controls

---

## Tech Stack

| Layer | Technology |
|-------|-----------|
| Language | C++ |
| GUI Framework | [wxWidgets](https://www.wxwidgets.org/) |
| Architecture | Singleton processor, Factory pattern for buttons |
| Build System | Visual Studio (`.sln` / `.vcxproj`) |

---

## Architecture
