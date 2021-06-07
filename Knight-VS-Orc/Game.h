#pragma once

#include <chrono>
#include <map>


class GameObject;
class Game
{
public:
	Game(const Game& _g) = delete;
	Game& operator=(Game _g) = delete;
	
	void Initialize();
	void Run();
	void DeInitialize();

	static Game& Get();

	GameObject& CreateNewGameObject();
	void DestroyGameObject(unsigned int _id);
	
private:
	Game();
	
	static Game* instance;
	
	std::map<unsigned int, GameObject*> sceneObjects;

	using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
	TimePoint currentTimePoint;
	TimePoint previousTimePoint;
	double elapsedTime;

	bool quitButtonPressed;

	bool GetQuitButtonPressed() const;
	void Update();
	
};
