#pragma once

class GameObject;
/// <summary>
/// Base class for every component
/// A component handle behavior for a gameobject
/// </summary>
class Component
{
public:
#pragma region Constructor
	Component() = default;
#pragma endregion 

	virtual ~Component() = default;

#pragma region Game Logic Method
	/// <summary>
	/// Called by its game object when the game object is enable
	/// </summary>
	/// <param name="_gameObject"></param>
	virtual void OnEnable(GameObject& _gameObject) = 0;
	
	/// <summary>
	/// Called when this component is created
	/// </summary>
	/// <param name="_gameObject"></param>
	virtual void Start(GameObject& _gameObject) = 0;

	/// <summary>
	/// Called by its game object container once per frame
	/// </summary>
	/// <param name="_gameObject"></param>
	/// <param name="_dt"></param>
	virtual void Update(GameObject& _gameObject, double _dt) = 0;

	/// <summary>
	/// Called by its game object when the game object is disable
	/// </summary>
	/// <param name="_gameObject"></param>
	virtual void OnDisable(GameObject& _gameObject) = 0;
#pragma endregion 
	
protected:

private:
	
};
