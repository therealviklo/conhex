#pragma once
#include "editarea.h"
#include "textmessagebox.h"
#include "vars/input.h"
#include "vars/state.h"
#include "vars/gfx.h"
#include "vars/file.h"
#include "vars/cursor.h"

bool cursorOnScreen();

void moveScreenUp();
void moveScreenDown();

void recalculateStartOfView();

void typeChar(char c);

void processInput();