#pragma once
#include "draw.h"

void draw()
{
	td->clear();

	menu.draw(0, 0, *td);

	td->draw();
}