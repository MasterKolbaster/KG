#include "NewGraphics.h"

int main()
{
	NewGraphics game;

	if (!game.ConstructConsole(240, 160, 4, 4))
		game.Loop();

	return 0;
}
