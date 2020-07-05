#pragma once
#include "editarea.h"

int editAreaWidth()
{
	switch (dispMode)
	{
		case M_BIN:
		{
			return (editArea.right - editArea.left) / 10 * 10; // Det här avrundar neråt
		}
		break;
		case M_HEX:
		{
			return (editArea.right - editArea.left) / 3 * 3;
		}
		break;
		case M_TEXT:
		{
			return editArea.right - editArea.left;
		}
		break;
	}
	return 1;
}

int editAreaHeight()
{
	return editArea.bottom - editArea.top;
}

int moveUnitsInRow()
{
	switch (dispMode)
	{
		case M_BIN:
		{
			return editAreaWidth() / 10 * 8;
		}
		break;
		case M_HEX:
		{
			return editAreaWidth() / 3 * 2;
		}
		break;
		case M_TEXT:
		{
			return editAreaWidth();
		}
		break;
	}
	return 1;
}

int bytesInRow()
{
	switch (dispMode)
	{
		case M_BIN:
		{
			return editAreaWidth() / 10;
		}
		break;
		case M_HEX:
		{
			return editAreaWidth() / 3;
		}
		break;
		case M_TEXT:
		{
			return editAreaWidth();
		}
		break;
	}
	return 1;
}