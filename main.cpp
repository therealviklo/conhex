#include <iostream>
#include "textdisp.h"
#include "timer.h"
#include "vars/gfx.h"

std::unique_ptr<Textdisp> td;
std::unique_ptr<Timer> timer;

int main()
{
	td = std::make_unique<Textdisp>();
	timer = std::make_unique<Timer>(60);
	
	while (true)
	{
		td->clear();

		td->set(1, 1, L'd', BackgroundColour::black | ForegroundColour::white);

		td->draw();
	}
}