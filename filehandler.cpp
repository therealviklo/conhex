#pragma once
#include "filehandler.h"

Filehandler::Filehandler()
{
	currFile = nullptr;
}

Filehandler::~Filehandler()
{
	if (currFile) fclose(currFile);
}

void Filehandler::open(std::string filename)
{
	if (currFile) fclose(currFile);

	currFile = fopen(filename.c_str(), "r+b");
	if (currFile == nullptr) // Något gick fel, men det kan vara att filen inte finns
	{
		currFile = fopen(filename.c_str(), "w+b"); // Därför försöker vi skapa den
		if (currFile == nullptr) // Det fungerade inte heller
		{
			// currFile är redan nullptr, så vi behöver inte ändra den
			throw std::runtime_error("Failed to open file");
		}
		else
		{
			this->filename = filename;
		}
	}
	else
	{
		this->filename = filename;
	}
}

void Filehandler::close()
{
	if (currFile)
	{
		fclose(currFile);
		filename = "";
	}
}

uint8_t Filehandler::readByte()
{
	if (currFile)
	{
		int byte = fgetc(currFile);
		if (byte == EOF) throw std::runtime_error("Unable to read from file");
		return (uint8_t)byte;
	}
	else
	{
		throw std::runtime_error("No file is open");
	}
}

uint8_t Filehandler::readByte(long pos)
{
	setPos(pos);
	if (currFile)
	{
		int byte = fgetc(currFile);
		if (byte == EOF) throw std::runtime_error("Unable to read from file");
		return (uint8_t)byte;
	}
	else
	{
		throw std::runtime_error("No file is open");
	}
}

void Filehandler::writeByte(uint8_t byte)
{
	if (currFile)
	{
		if (fputc(byte, currFile) == EOF) throw std::runtime_error("Unable to write to file");
	}
	else
	{
		throw std::runtime_error("No file is open");
	}
}

void Filehandler::writeByte(uint8_t byte, long pos)
{
	setPos(pos);
	if (currFile)
	{
		if (fputc(byte, currFile) == EOF) throw std::runtime_error("Unable to write to file");
	}
	else
	{
		throw std::runtime_error("No file is open");
	}
}

void Filehandler::setPos(long pos)
{
	if (currFile)
	{
		if (fseek(currFile, pos, SEEK_SET)) throw std::runtime_error("Unable to set position");
	}
}

long Filehandler::getPos()
{
	if (currFile)
	{
		long pos = ftell(currFile);
		if (pos == -1L) throw std::runtime_error("Unable to get position");
		return pos;
	}
	else
	{
		throw std::runtime_error("No file is open");
	}
}

void Filehandler::clear()
{
	if (currFile)
	{
		fclose(currFile);
		currFile = fopen(filename.c_str(), "w+b");
		if (currFile == nullptr)
		{
			filename = "";
			throw std::runtime_error("Unable to clear file");
		}
	}
	else
	{
		throw std::runtime_error("No file is open");
	}
}