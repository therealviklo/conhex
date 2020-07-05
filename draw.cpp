#pragma once
#include "draw.h"

wchar_t boolToBin(bool b)
{
	if (b) return L'1';
	else return L'0';
}

wchar_t nibbleToHex(uint8_t nibble)
{
	if (nibble < 10) return L'0' + nibble;
	else return L'A' + nibble - 10;
}

void drawData()
{
	FileData::Reference currByte = startOfView; // Vscode tycker att det här är fel men det är det inte
	switch (dispMode)
	{
		case M_BIN:
		{
			int x = 0;
			int y = 0;
			int w = (editArea.right - editArea.left) / 10 * 10; // Det här avrundar neråt
			int h = editArea.bottom - editArea.top;
			while (currByte && y < h)
			{
				for (int i = 7; i >= 4; i--)
				{
					td->set(x + editArea.left, y + editArea.top, boolToBin((*currByte) & (1 << i)), BackgroundColour::black | ForegroundColour::white);
					x++;
				}
				td->set(x + editArea.left, y + editArea.top, L'-', BackgroundColour::black | ForegroundColour::white);
				x++;
				for (int i = 3; i >= 0; i--)
				{
					td->set(x + editArea.left, y + editArea.top, boolToBin((*currByte) & (1 << i)), BackgroundColour::black | ForegroundColour::white);
					x++;
				}
				td->set(x + editArea.left, y + editArea.top, L' ', BackgroundColour::black | ForegroundColour::white);
				x++;
				if (x >= w)
				{
					x %= w;
					y++;
				}
				currByte.next();
			}
		}
		break;
		case M_HEX:
		{
			int x = 0;
			int y = 0;
			int w = (editArea.right - editArea.left) / 3 * 3;
			int h = editArea.bottom - editArea.top;
			while (currByte && y < h)
			{
				td->set(x + editArea.left, y + editArea.top, nibbleToHex(((*currByte) >> 4) & 0xf), BackgroundColour::black | ForegroundColour::white);
				x++;
				td->set(x + editArea.left, y + editArea.top, nibbleToHex((*currByte) & 0xf), BackgroundColour::black | ForegroundColour::white);
				x++;
				td->set(x + editArea.left, y + editArea.top, L' ', BackgroundColour::black | ForegroundColour::white);
				x++;
				if (x >= w)
				{
					x %= w;
					y++;
				}
				currByte.next();
			}
		}
		break;
		case M_TEXT:
		{
			int x = 0;
			int y = 0;
			int w = editArea.right - editArea.left;
			int h = editArea.bottom - editArea.top;
			while (currByte && y < h)
			{
				td->set(x + editArea.left, y + editArea.top, *currByte > 0x1f && *currByte != 0x7f ? *currByte : L' ', BackgroundColour::black | ForegroundColour::white);
				x++;
				if (x >= w)
				{
					x %= w;
					y++;
				}
				currByte.next();
			}
		}
		break;
		default:
		break;
	}
}

void draw()
{
	td->clear();

	drawData();

	menu.draw(0, 0, *td);

	td->draw();
}