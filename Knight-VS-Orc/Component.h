#pragma once

class GameObject;
class Component
{
public:
#pragma region Constructor
	Component() = default;
#pragma endregion 

	virtual ~Component() = default;

#pragma region Game Logic Method
	virtual void Start(GameObject& _gameObject) = 0;

	/// <summary>
	/// Called by its game object container once per frame
	/// </summary>
	/// <param name="_gameObject"></param>
	/// <param name="_dt"></param>
	virtual void Update(GameObject& _gameObject, double _dt) = 0;
#pragma endregion 
	
protected:


private:
	
};
