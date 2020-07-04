#pragma once
#include "utilsstr.h"

std::string intToString(int t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

std::wstring intToWString(int t)
{
	std::wstringstream ss;
	ss << t;
	return ss.str();
}