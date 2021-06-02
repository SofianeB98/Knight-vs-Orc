#pragma once
#include <vector>

class Component;
class GameObject
{
public:
#pragma region Constructor
	/// <summary>
	/// Create a default Game Object and reserve its components
	/// </summary>
	GameObject();
#pragma endregion

	~GameObject();

#pragma region Game Logic Method
	/// <summary>
	/// 
	/// </summary>
	void Start();

	/// <summary>
	/// Update methode is called once per frame
	/// </summary>
	/// <param name="_dt"></param>
	void Update(double _dt);
#pragma endregion 
	
#pragma region Component Method
	/// <summary>
	/// Add Component method add the typename component to the
	/// Game object components, if doesn't have it, else return the
	/// Existing component
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	template <typename T>
	T& AddComponent();

	/// <summary>
	/// Return the specified component type if exist
	/// else return nullptr
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	template <typename T>
	T* GetComponent() const;
#pragma endregion 
	
private:
	std::vector<Component*> components;

	/// <summary>
	/// Destroy all components
	/// </summary>
	void Destroy();
};
