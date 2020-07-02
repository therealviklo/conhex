#pragma once
#include <Windows.h>

#pragma comment(lib, "User32.lib")

namespace ForegroundColour
{
	enum ForegroundColour_t
	{
		black             = 0,
		darkblue          = FOREGROUND_BLUE,
		darkgreen         = FOREGROUND_GREEN,
		darkcyan          = FOREGROUND_GREEN | FOREGROUND_BLUE,
		darkred           = FOREGROUND_RED,
		darkmagenta       = FOREGROUND_RED | FOREGROUND_BLUE,
		darkyellow        = FOREGROUND_RED | FOREGROUND_GREEN,
		grey              = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		darkgrey          = FOREGROUND_INTENSITY,
		blue              = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		green             = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		cyan              = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		red               = FOREGROUND_INTENSITY | FOREGROUND_RED,
		magenta           = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		yellow            = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		white             = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	};
}

namespace BackgroundColour
{
	enum BackgroundColour_t
	{
		black             = 0,
		darkblue          = BACKGROUND_BLUE,
		darkgreen         = BACKGROUND_GREEN,
		darkcyan          = BACKGROUND_GREEN | BACKGROUND_BLUE,
		darkred           = BACKGROUND_RED,
		darkmagenta       = BACKGROUND_RED | BACKGROUND_BLUE,
		darkyellow        = BACKGROUND_RED | BACKGROUND_GREEN,
		grey              = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
		darkgrey          = BACKGROUND_INTENSITY,
		blue              = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
		green             = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
		cyan              = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
		red               = BACKGROUND_INTENSITY | BACKGROUND_RED,
		magenta           = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
		yellow            = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
		white             = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	};
}

WORD invertColour(WORD colour);

bool keyPressed(int key);
bool keyToggled(int key);

bool consoleIsActiveWindow();

class Textdisp
{
private:
	CHAR_INFO* screen;
	int width;
	int height;
	HANDLE screenBuffer;
	HANDLE stdScreenBuffer;
public:
	Textdisp(int width, int height);
	~Textdisp();

	Textdisp(const Textdisp&) = delete;
	Textdisp& operator=(const Textdisp&) = delete;

	int getWidth() { return width; };
	int getHeight() { return height; };

	void clear();
	void set(int x, int y, WCHAR c, WORD attributes);
	WCHAR getChar(int x, int y);
	WORD getAttributes(int x, int y);

	void draw();
};

class SinglePressKey
{
private:
	bool toggled;
	int c;
	int interval;
	int minInterval;
	double effectiveInterval;
	double decrease;
	int pressedTime;
public:
	SinglePressKey(int c, int interval = 1, int minInterval = 1, double decrease = 1);

	//är endast true en gång efter att tangenten har tryckts ner
	bool pressed();
	//är true var "intervalade" gång den körs
	bool down();
};