#pragma once
#include "processinput.h"

bool cursorOnScreen()
{
	int w = bytesInRow();
	int h = editAreaHeight();
	auto byte = startOfView;
	for (int i = 0; byte != nullptr && i < w * h; i++)
	{
		if (byte == cursor.getByte()) return true;
		byte.next();
	}
	return false;
}

void moveScreenUp()
{
	startOfView.tryMove(-bytesInRow());
}

void moveScreenDown()
{
	startOfView.tryMove(bytesInRow());
}

void recalculateStartOfView()
{
	startOfView = filedata.start();
	while (startOfView && !cursorOnScreen()) moveScreenDown();
}

void typeChar(char c)
{
	if (cursor.getByte())
	{
		switch (dispMode)
		{
			case M_BIN:
			{
				switch (c)
				{
					case '0':
					{
						unsigned int bit = 1 << (7 - cursor.getBit());
						if (*cursor.getByte() & bit) *cursor.getByte() ^= bit;
					}
					break;
					case '1':
					{
						unsigned int bit = 1 << (7 - cursor.getBit());
						*cursor.getByte() |= bit;
					}
					break;
				}
			}
			break;
			case M_HEX:
			{
				for (char d = '0'; d <= '9'; d++)
				{
					if (d == c)
					{
						unsigned int bits = 0b1111 << (4 - cursor.getBit());
						*cursor.getByte() &= ~bits;
						*cursor.getByte() += (c - '0') << (4 - cursor.getBit());
					}
				}
				for (char d = 'A'; d <= 'Z'; d++)
				{
					if (d == c)
					{
						unsigned int bits = 0b1111 << (4 - cursor.getBit());
						*cursor.getByte() &= ~bits;
						*cursor.getByte() += (c - 'A' + 10) << (4 - cursor.getBit());
					}
				}
			}
			break;
		}
		cursor.moveRight();
	}
}

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
					filehandler.clear();
					filehandler.setPos(0);
					for (auto i = filedata.start(); i != nullptr; i.next())
					{
						filehandler.writeByte(*i);
					}
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
				cursor.flattenBit();
				recalculateStartOfView();
			}
			else if (menuResult.menu == L"Gå till")
			{
				if (menuResult.option == L"Offset")
				{
					try
					{
						FileData::Reference r = filedata.start();
						unsigned long offset = std::stoul(promptTextInputBoxA437("Offset", *td, *timer), nullptr, 0);
						for (unsigned long i = 0; i < offset; i++)
						{
							r.next();
						}
						if (r) cursor.setPos(r);
					}
					catch (std::out_of_range) {}
				}
			}
		}
	}

	if (ti->typed(VK_UP))
	{
		cursor.moveUp();
		if (!cursorOnScreen()) moveScreenUp();
	}
	if (ti->typed(VK_LEFT))
	{
		cursor.moveLeft();
		if (!cursorOnScreen()) moveScreenUp();
	}
	if (ti->typed(VK_DOWN))
	{
		cursor.moveDown();
		if (!cursorOnScreen()) moveScreenDown();
	}
	if (ti->typed(VK_RIGHT))
	{
		cursor.moveRight();
		if (!cursorOnScreen()) moveScreenDown();
	}

	if (ti->pressed('T')) // T för "bas Två"
	{
		dispMode = M_BIN;
		cursor.flattenBit();
		recalculateStartOfView();
	}
	if (ti->pressed('H')) // H för "Hexadecimalt"
	{
		dispMode = M_HEX;
		cursor.flattenBit();
		recalculateStartOfView();
	}
	if (ti->pressed('K')) // K för "Karaktär"
	{
		dispMode = M_TEXT;
		cursor.flattenBit();
		recalculateStartOfView();
	}

	switch (dispMode)
	{
		case M_BIN:
		{
			if (ti->typed('0')) typeChar('0');
			if (ti->typed('1')) typeChar('1');
		}
		break;
		case M_HEX:
		{
			for (char c = '0'; c <= '9'; c++)
			{
				if (ti->typed(c)) typeChar(c);
			}
			for (char c = 'A'; c <= 'F'; c++)
			{
				if (ti->typed(c)) typeChar(c);
			}
		}
		break;
	}
}