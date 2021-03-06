#pragma once
#include "textutils.h"
#include "textdisp.h"
#include "textimage.h"
#include "timer.h"
#include <vector>
#include <string>
#include <memory>

struct MenuResult
{
	bool successful;
	std::wstring menu;
	std::wstring option;
};

class Menu
{
public:
	typedef std::vector<std::pair<std::wstring, std::vector<std::wstring>>> options_t;
private:
	options_t options;
	int menuSelectedOption;
	int listSelectedOption;
	bool isInMenu;

	Box getCoveredArea(int x, int y);
public:
	Menu(options_t options);

	bool inMenu() {return isInMenu;}

	void draw(int x, int y, Textdisp& textdisp);    
	MenuResult enterMenu(int x, int y, Textdisp& textdisp, Timer& timer);

	bool moveCursor(bool wPressed, bool aPressed, bool sPressed, bool dPressed);
};