#include "Game.h"


#include <cassert>
#include <conio.h>
#include <iostream>
#include <thread>

#include "BattleManagerComponent.h"
#include "GameObject.h"

Game* Game::instance = nullptr;

void Game::Initialize()
{
	// Initialize time
	this->previousTimePoint = std::chrono::high_resolution_clock::now();

	// Create the Battle Manager game object
	// and add Battle Manager Component to it
	auto& battle = CreateNewGameObject();
	battle.AddComponent<BattleManagerComponent>(new BattleManagerComponent);
}

void Game::Run()
{
	// We can add callback, method, or anything else
	// Before call update and after
	
	// Update
	Update();	
}

void Game::Update()
{
	// Game loop
	while (!this->quitButtonPressed)
	{
		// Calculate delta time
		this->currentTimePoint = std::chrono::high_resolution_clock::now();
		this->elapsedTime = std::chrono::duration<double>(this->currentTimePoint - this->previousTimePoint).count();
		this->previousTimePoint = this->currentTimePoint;

		// Process quit input
 		this->quitButtonPressed = GetQuitButtonPressed();

		// Update all gameobjects (and these components)
		for (auto& gameObject : this->sceneObjects)
		{
			gameObject.second->Update(this->elapsedTime);
		}

		// If we've a render (3D, 2D, etc)
		// We call the render method here
		// Render()
	}
}


void Game::DeInitialize()
{
	// Delete all game objects and these components
	for(auto& gameObject : this->sceneObjects)
	{
		if (gameObject.second != nullptr)
		{
			delete gameObject.second;
			gameObject.second = nullptr;
		}
	}

	this->sceneObjects.clear();

	// Delete game instance
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

	gameObject->Start();
	
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