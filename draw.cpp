#pragma once
#include "draw.h"

#define WoB (BackgroundColour::black | ForegroundColour::white)
#define BoW (BackgroundColour::white | ForegroundColour::black)

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
	int x = 0;
	int y = 0;
	int w = editAreaWidth();
	int h = editAreaHeight();
	switch (dispMode)
	{
		case M_BIN:
		{
			while (currByte && y < h)
			{
				for (int i = 7; i >= 4; i--)
				{
					WORD colour = cursor.getByte() == currByte && cursor.getBit() == 7 - i ? BoW : WoB;
					td->set(x + editArea.left, y + editArea.top, boolToBin((*currByte) & (1 << i)), colour);
					x++;
				}
				td->set(x + editArea.left, y + editArea.top, L'-', WoB);
				x++;
				for (int i = 3; i >= 0; i--)
				{
					WORD colour = cursor.getByte() == currByte && cursor.getBit() == 7 - i ? BoW : WoB;
					td->set(x + editArea.left, y + editArea.top, boolToBin((*currByte) & (1 << i)), colour);
					x++;
				}
				td->set(x + editArea.left, y + editArea.top, L' ', WoB);
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
			while (currByte && y < h)
			{
				WORD colour = cursor.getByte() == currByte && cursor.getBit() == 0 ? BoW : WoB;
				td->set(x + editArea.left, y + editArea.top, nibbleToHex(((*currByte) >> 4) & 0xf), colour);
				x++;
				colour = cursor.getByte() == currByte && cursor.getBit() == 4 ? BoW : WoB;
				td->set(x + editArea.left, y + editArea.top, nibbleToHex((*currByte) & 0xf), colour);
				x++;
				td->set(x + editArea.left, y + editArea.top, L' ', WoB);
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
			while (currByte && y < h)
			{
				WORD colour = cursor.getByte() == currByte ? BoW : WoB;
				td->set(x + editArea.left, y + editArea.top, *currByte > 0x1f && *currByte != 0x7f ? *currByte : L' ', colour);
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
	}
}

void draw()
{
	td->clear();

	drawData();

	menu.draw(0, 0, *td);

	td->draw();
}