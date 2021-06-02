#include "Game.h"

#include <conio.h>
#include <thread>

Game* Game::instance = nullptr;

void Game::Initialize()
{	
	this->previousTimePoint = std::chrono::high_resolution_clock::now();
}

void Game::Update()
{
	while(!this->quitButtonPressed)
	{
		this->currentTimePoint = std::chrono::high_resolution_clock::now();
		this->elapsedTime = std::chrono::duration<double>(this->currentTimePoint - this->previousTimePoint).count();
		this->previousTimePoint = this->currentTimePoint;

		for(auto& gameObject : this->sceneObjects)
		{
			gameObject.Update(this->elapsedTime);
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		
		this->quitButtonPressed = GetQuitButtonPressed();
	}
}


void Game::DeInitialize()
{
	if (Game::instance != nullptr)
	{
		delete Game::instance;
		Game::instance = nullptr;
	}
}

Game& Game::Get()
{
	if (Game::instance == nullptr)
		Game::instance = new Game;

	return *instance;
}


Game::Game()
{
	
}


bool Game::GetQuitButtonPressed() const
{
	if (_kbhit())
	{
		int ch = _getch();
		if (ch == 27)			// ESC 
			return true;
	}
	return false;
}