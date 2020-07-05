#pragma once
#include "processfile.h"

void loadFileData()
{
	filehandler.setPos(0);
	filedata.clear();
	FileData::Reference r = filedata.start();
	while (true)
	{
		try
		{
			uint8_t byte = filehandler.readByte();
			r = filedata.insertAfter(r);
			if (r) *r = byte;
		}
		catch (std::runtime_error)
		{
			break;
		}
	}
	startOfView = filedata.start();
}