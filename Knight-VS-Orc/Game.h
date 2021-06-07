#pragma once

#include <chrono>
#include <map>


class GameObject;
class Game
{
public:
	// Game class is a singleton, only 1 instance exist
	// We delete copy constructor and operator =
	Game(const Game& _g) = delete;
	Game& operator=(Game _g) = delete;

#pragma region Game Logic Method
	void Initialize();
	void Run();
	void DeInitialize();
#pragma endregion

	/// <summary>
	/// Return the singleton instance
	/// </summary>
	/// <returns></returns>
	static Game& Get();

#pragma region Gameobject Method
	/// <summary>
	/// Create a new game object and return a reference to
	/// Add component to it
	/// </summary>
	/// <returns></returns>
	GameObject& CreateNewGameObject();

	/// <summary>
	/// Destroy the specific gameobject by its id
	/// </summary>
	/// <param name="_id"></param>
	void DestroyGameObject(unsigned int _id);
#pragma endregion 
	
private:
	Game();
	
	static Game* instance;

	// Stock all game object by id
	std::map<unsigned int, GameObject*> sceneObjects;

#pragma region Time field
	using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
	TimePoint currentTimePoint;
	TimePoint previousTimePoint;
	double elapsedTime;
#pragma endregion

	// Bool to handle quit app callback
	bool quitButtonPressed;
	bool GetQuitButtonPressed() const;

	/// <summary>
	/// Game loop of the app
	/// </summary>
	void Update();
};
