#pragma once

#include <chrono>
#include <map>

#include "GameObject.h"

class Game
{
public:
	
	void Initialize();
	void Update();
	void DeInitialize();

	static Game& Get();
	
private:
	Game();
	
	static Game* instance;
	
	std::map<unsigned int, GameObject> sceneObjects;

	using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
	TimePoint currentTimePoint;
	TimePoint previousTimePoint;
	double elapsedTime;

	bool quitButtonPressed;

	bool GetQuitButtonPressed() const;
	
};
