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
SWE_App/
├── App.cpp / App.h — wxApp entry point
├── Window.cpp / Window.h — Main window and layout
├── Button_Factory.cpp / .h — Factory pattern for button creation
├── Calc_processor.cpp / .h — Expression parser and RPN evaluator (core logic)

The `Calc_processor` is a **Singleton** that handles all math logic independently from the UI layer. Expressions are tokenized, converted to RPN via the Shunting-Yard algorithm, then evaluated on a stack.

---

## How to Build

**Requirements:**
- Visual Studio 2022 (or compatible)
- wxWidgets 3.x installed and configured

**Steps:**
1. Clone the repo
2. Open `SWE_App.sln` in Visual Studio
3. Set wxWidgets paths in project properties if needed
4. Build → Run

---

## Screenshots

*Coming soon — build in progress*

---

## 🗺️ Roadmap

### v2.0 — Squatch Character UI *(planned)*
- Replace wxWidgets rendering layer with SFML or SDL2
- Animated Squatch character displayed at top of window
- Answers delivered via speech bubble animation
- Idle, calculating, and error reaction animations
- Optional: rebuild as WebAssembly app for browser-based portfolio embed

---

## Part of the SquatchWorks Portfolio

> This project is part of a series of progressively complex C++ and game development projects.  
> View more at [github.com/Squatchworks](https://github.com/Squatchworks)