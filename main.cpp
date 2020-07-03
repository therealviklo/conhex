#include <iostream>
#include "textdisp.h"
#include "timer.h"

int main()
{
	Textdisp td;
	Timer timer(60);

	while (true)
	{
		td.clear();

		td.set(1, 1, L'd', BackgroundColour::black | ForegroundColour::white);

		td.draw();
	}
}