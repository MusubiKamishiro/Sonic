#include "Game.h"

int main(void)
{
	Game& game = Game::Instance();
	game.Initialize();
	game.Run();
	game.Terminate();
	return 0;
}