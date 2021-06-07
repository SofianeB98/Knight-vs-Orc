#include <iostream>

#include "Game.h"

// Main
int main()
{
	// Initialize the singleton
	Game& app = Game::Get();

	// Initalize the app
	app.Initialize();

	// Run the app (Update)
	app.Run();

	// Clear the app
	app.DeInitialize();
	
	return 0;

}