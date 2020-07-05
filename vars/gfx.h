#pragma once
#include <memory>
#include "../textdisp.h"
#include "../timer.h"
#include "../menu.h"
#include "../textutils.h"

enum DispMode
{
	M_BIN,
	M_HEX,
	M_TEXT
};

extern std::unique_ptr<Textdisp> td;
extern std::unique_ptr<Timer> timer;
extern Menu menu;
extern Box editArea;
extern DispMode dispMode;