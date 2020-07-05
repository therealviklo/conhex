#pragma once
#include "processinput.h"

void processInput()
{
	if (ti->pressed(VK_MENU) || ti->pressed('M'))
	{
		MenuResult menuResult = menu.enterMenu(0, 0, *td, *timer);
		if (menuResult.successful)
		{
			if (menuResult.menu == L"Arkiv")
			{
				if (menuResult.option == L"Spara")
				{

				}
				else if (menuResult.option == L"Avsluta")
				{
					running = false;
				}
			}
			else if (menuResult.menu == L"Läge")
			{
				if (menuResult.option == L"Binärt")
				{
					dispMode = M_BIN;
				}
				else if (menuResult.option == L"Hexadecimalt")
				{
					dispMode = M_HEX;
				}
				else if (menuResult.option == L"Tecken")
				{
					dispMode = M_TEXT;
				}
			}
		}
	}
}