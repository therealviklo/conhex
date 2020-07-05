#include <iostream>
#include "textdisp.h"
#include "timer.h"
#include "draw.h"
#include "processinput.h"
#include "utilsstr.h"
#include "filedata.h"
#include "processfile.h"
#include "vars/gfx.h"
#include "vars/input.h"
#include "vars/state.h"
#include "vars/file.h"
#include "vars/cursor.h"

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
	},
	{
		L"Läge",
		{
			L"Binärt",
			L"Hexadecimalt",
			L"Tecken"
		}
	}
});
Box editArea;
// input
std::unique_ptr<Textinp> ti;
// state
bool running = true;
DispMode dispMode = M_HEX;
// file
Filehandler filehandler;
FileData filedata;
FileData::Reference startOfView = nullptr;
// cursor
Cursor cursor;

int main(int argc, char* argv[])
{
	try
	{
		SetConsoleCP(1252);
		SetConsoleOutputCP(1252);

		if (argc == 2)
		{
			filehandler.open(argv[1]);
			loadFileData();
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