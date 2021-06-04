#include <iostream>

#include "Game.h"

int main() {

	Game& app = Game::Get();
	
	app.Initialize();
	app.Run();
	app.DeInitialize();
	
	return 0;

}