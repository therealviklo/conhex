#pragma once
#include "editarea.h"
#include "vars/gfx.h"
#include "vars/file.h"
#include "vars/state.h"
#include "vars/cursor.h"

wchar_t boolToBin(bool b);
wchar_t nibbleToHex(uint8_t nibble);

void drawData();
void draw();