#include "Game.h"


#include <cassert>
#include <conio.h>
#include <iostream>
#include <thread>

Game* Game::instance = nullptr;

void Game::Initialize()
{
	this->previousTimePoint = std::chrono::high_resolution_clock::now();
}

void Game::Update()
{
	while (!this->quitButtonPressed)
	{
		this->currentTimePoint = std::chrono::high_resolution_clock::now();
		this->elapsedTime = std::chrono::duration<double>(this->currentTimePoint - this->previousTimePoint).count();
		this->previousTimePoint = this->currentTimePoint;

		for (auto& gameObject : this->sceneObjects)
		{
			gameObject.second->Update(this->elapsedTime);
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


GameObject& Game::CreateNewGameObject()
{
	GameObject* gameObject = new GameObject;

	this->sceneObjects.insert({ gameObject->GetId(), gameObject });

	return *gameObject;
}

void Game::DestroyGameObject(unsigned int _id)
{
	assert((int)_id >= 0 && "You're trying to destroy non-existent Game Object with negative id. Please enter a valid ID");

	if (this->sceneObjects.find(_id) == this->sceneObjects.end())
	{
		std::cout << "Specified Game Object ID doesn't exist. Please enter a valid ID" << std::endl;
		return;
	}

	if (this->sceneObjects[_id] != nullptr)
	{
		delete this->sceneObjects[_id];
		this->sceneObjects[_id] = nullptr;
	}

	this->sceneObjects.erase(_id);

}


Game::Game()
{

}


bool Game::GetQuitButtonPressed() const
{
	if (_kbhit())
	{
		int ch = _getch();
		if (ch == 27) // ESC 
			return true;
	}
	return false;
}