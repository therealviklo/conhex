#include <iostream>
#include "textdisp.h"
#include "timer.h"
#include "vars/gfx.h"
#include "vars/input.h"

// gfx
std::unique_ptr<Textdisp> td;
std::unique_ptr<Timer> timer;
// input
std::unique_ptr<Textinp> ti;

int main()
{
	try
	{
		// gfx
		td = std::make_unique<Textdisp>();
		timer = std::make_unique<Timer>(60);
		// input
		ti = std::make_unique<Textinp>();
		
		while (true)
		{
			td->clear();

			td->set(1, 1, L'd', BackgroundColour::black | ForegroundColour::white);

			td->draw();
		}
	}
	catch (const std::exception& e)
	{
		MessageBoxA(NULL, e.what(), "Fel", MB_OK | MB_ICONERROR);
	}
	catch (...)
	{
		MessageBoxW(NULL, L"Okänt fel", L"Fel", MB_OK | MB_ICONERROR);
	}
}