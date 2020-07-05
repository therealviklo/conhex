#pragma once
#include "cursor.h"

Cursor::Cursor()
	: byte(nullptr),
	  bit(0) {}

void Cursor::flattenBit()
{
	switch (dispMode)
	{
		case M_BIN:
		break;
		case M_HEX:
		{
			if (bit > 3) bit = 4;
			else bit = 0;
		}
		break;
		case M_TEXT:
		{
			bit = 0;
		}
		break;
	}
}

void Cursor::moveUp()
{
	int w = moveUnitsInRow();
	for (int i = 0; i < w; i++)
		moveLeft();
}

void Cursor::moveLeft()
{
	flattenBit();
	switch (dispMode)
	{
		case M_BIN:
		{
			if (bit == 0)
			{
				if (byte.peekPrev() != nullptr)
				{
					byte.prev();
					bit = 7;
				}
				else
				{
					return;
				}
			}
			else
			{
				bit--;
			}
		}
		break;
		case M_HEX:
		{
			if (bit == 0)
			{
				if (byte.peekPrev() != nullptr)
				{
					byte.prev();
					bit = 4;
				}
				else
				{
					return;
				}
			}
			else
			{
				bit = 0;
			}
		}
		break;
		case M_TEXT:
		{
			if (byte.peekPrev() != nullptr)
			{
				byte.prev();
			}
			else
			{
				return;
			}
		}
		break;
	}
}

void Cursor::moveDown()
{
	int w = moveUnitsInRow();
	for (int i = 0; i < w; i++)
		moveRight();
}

void Cursor::moveRight()
{
	flattenBit();
	switch (dispMode)
	{
		case M_BIN:
		{
			if (bit == 7)
			{
				if (byte.peekNext() != nullptr)
				{
					byte.next();
					bit = 0;
				}
				else
				{
					return;
				}
			}
			else
			{
				bit++;
			}
		}
		break;
		case M_HEX:
		{
			if (bit == 4)
			{
				if (byte.peekNext() != nullptr)
				{
					byte.next();
					bit = 0;
				}
				else
				{
					return;
				}
			}
			else
			{
				bit = 4;
			}
		}
		break;
		case M_TEXT:
		{
			if (byte.peekNext() != nullptr)
			{
				byte.next();
			}
			else
			{
				return;
			}
		}
		break;
	}
}

void Cursor::setPos(FileData::Reference pos)
{
	byte = pos;
	bit = 0;
}