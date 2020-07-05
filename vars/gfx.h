#pragma once
#include <memory>
#include "../textdisp.h"
#include "../timer.h"
#include "../menu.h"
#include "../textutils.h"
#include "../cursor.h"

extern std::unique_ptr<Textdisp> td;
extern std::unique_ptr<Timer> timer;
extern Menu menu;
extern Box editArea;