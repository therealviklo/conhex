#include <iostream>
#include "textdisp.h"
#include "timer.h"
#include "draw.h"
#include "processinput.h"
#include "utilsstr.h"
#include "vars/gfx.h"
#include "vars/input.h"
#include "vars/state.h"
#include "vars/file.h"

// gfx
std::unique_ptr<Textdisp> td;
std::unique_ptr<Timer> timer;
Menu menu(Menu::options_t{
	{
		L"Arkiv",
		{
			L"Spara",
			L"Avsluta"
		}
	}
});
Box editArea;
// input
std::unique_ptr<Textinp> ti;
// state
bool running = true;
// file
Filehandler filehandler;

int main(int argc, char* argv[])
{
	try
	{
		SetConsoleCP(1252);
		SetConsoleOutputCP(1252);

		if (argc == 2)
		{
			filehandler.open(argv[1]);
		}
		else
		{
			std::wcerr << L"Vänligen specificera vilken fil som ska öppnas." << std::endl;
			return 1;
		}

		// gfx
		td = std::make_unique<Textdisp>();
		timer = std::make_unique<Timer>(60);
		editArea = {0, 1, td->getWidth() - 1, td->getHeight() - 1};
		// input
		ti = std::make_unique<Textinp>();
		
		while (running)
		{
			processInput();

			draw();
		}

		return 0;
	}
	catch (const std::exception& e)
	{
		MessageBoxA(NULL, e.what(), "Fel", MB_OK | MB_ICONERROR);
	}
	catch (...)
	{
		MessageBoxW(NULL, L"Okänt fel", L"Fel", MB_OK | MB_ICONERROR);
	}
	return 1;
}