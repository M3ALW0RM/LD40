#include <Game.h>
#include "AssetsManager.h"

int main()
{
	Game game;
	if (game.Init())
	{
		game.Run();
		return 0;
	}
    return 1;
}

