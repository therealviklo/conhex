#pragma once
#include "textdisp.h"

WORD invertColour(WORD colour)
{
	return colour ^ FOREGROUND_RED ^ FOREGROUND_GREEN ^ FOREGROUND_BLUE ^ FOREGROUND_INTENSITY ^ BACKGROUND_RED ^ BACKGROUND_GREEN ^ BACKGROUND_BLUE ^ BACKGROUND_INTENSITY;
}

bool keyPressed(int key)
{
	return 0b100000000 & GetKeyState(key);
}

bool keyToggled(int key)
{
	return 1 & GetKeyState(key);
}

bool consoleIsActiveWindow()
{
	return GetConsoleWindow() == GetForegroundWindow();
}

Textdisp::Textdisp(int width, int height)
{
	this->width = width;
	this->height = height;
	screen = new CHAR_INFO[width*height];
	clear();
	stdScreenBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
	screenBuffer = CreateConsoleScreenBuffer( 
	   GENERIC_WRITE,
	   FILE_SHARE_WRITE,
	   NULL,
	   CONSOLE_TEXTMODE_BUFFER,
	   NULL);
	SetConsoleActiveScreenBuffer(screenBuffer);
}

Textdisp::~Textdisp()
{
	delete[] screen;
	SetConsoleActiveScreenBuffer(stdScreenBuffer);
	CloseHandle(stdScreenBuffer);
	CloseHandle(screenBuffer);
}

void Textdisp::clear()
{
	for (int i = 0; i < width*height; i++)
	{
		screen[i] = {{' '}, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY};
	}
}

void Textdisp::set(int x, int y, WCHAR c, WORD attributes)
{
	if (x >= 0 &&
		x < width &&
		y >= 0 &&
		y < height)
	{
		screen[x+y*width] = {{c}, attributes};
	}
}

WCHAR Textdisp::getChar(int x, int y)
{
	if (x >= 0 &&
		x < width &&
		y >= 0 &&
		y < height)
	{
		return screen[x+y*width].Char.UnicodeChar;
	}
	else
	{
		return 0;
	}
}

WORD Textdisp::getAttributes(int x, int y)
{
	if (x >= 0 &&
		x < width &&
		y >= 0 &&
		y < height)
	{
		return screen[x+y*width].Attributes;
	}
	else
	{
		return 0;
	}
}

void Textdisp::draw()
{
	SMALL_RECT destRect;
	destRect.Left = 0;
	destRect.Top = 0;
	destRect.Right = width;
	destRect.Bottom = height;
	WriteConsoleOutput(screenBuffer, screen, {(SHORT)width, (SHORT)height}, {0, 0}, &destRect);
}

SinglePressKey::SinglePressKey(int c, int interval, int minInterval, double decrease)
{
	this->c = c;
	this->interval = interval;
	this->minInterval = minInterval;
	this->effectiveInterval = interval;
	this->decrease = decrease;
	pressedTime = 0;
	toggled = keyToggled(c);
}

bool SinglePressKey::pressed()
{
	if (keyPressed(c) && keyToggled(c) != toggled)
	{
		toggled = keyToggled(c);
		return true;
	}
	return false;
}

bool SinglePressKey::down()
{
	toggled = keyToggled(c);
	if (keyPressed(c))
	{
		if (pressedTime % int(effectiveInterval) == 0)
		{
			if (effectiveInterval > minInterval) effectiveInterval -= decrease;
			pressedTime = (pressedTime + 1) % int(effectiveInterval);
			return true;
		}
		else
		{
			if (effectiveInterval > minInterval) effectiveInterval -= decrease;
			pressedTime = (pressedTime + 1) % int(effectiveInterval);
			return false;
		}
	}
	else
	{
		pressedTime = 0;
		effectiveInterval = interval;
		return false;
	}
}