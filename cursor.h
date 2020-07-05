#pragma once
#include "textutils.h"
#include "filedata.h"
#include "editarea.h"
#include "vars/state.h"

class Cursor
{
private:
	FileData::Reference byte;
	int bit;
public:
	Cursor();
	
	void flattenBit();

	void moveUp();
	void moveLeft();
	void moveDown();
	void moveRight();

	FileData::Reference getByte() {return byte;}
	int getBit() {return bit;}

	void setPos(FileData::Reference pos);
};