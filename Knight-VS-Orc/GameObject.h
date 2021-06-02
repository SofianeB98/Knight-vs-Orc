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

	GameObject(const GameObject& _gameObject);

	GameObject& operator=(GameObject _gameObject);
#pragma endregion

	~GameObject();

#pragma region Game Logic Method
	/// <summary>
	/// Call when this object is created
	/// </summary>
	void Start();

	/// <summary>
	/// Update methode is called once per frame
	/// </summary>
	/// <param name="_dt"></param>
	void Update(double _dt);

	void SetActive(bool _val);
#pragma endregion 

#pragma region Getter
	bool IsActive() const;
	unsigned int GetId() const;
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
	bool isActive;
	std::vector<Component*> components;

	static unsigned int CURRENT_ID;
	
	unsigned int id;
	
	/// <summary>
	/// Destroy all components
	/// </summary>
	void Destroy();

	/// <summary>
	/// Called each time this object is set to "isActive"
	/// Trigger on enable on each component
	/// </summary>
	void OnEnable();

	/// <summary>
	/// Called each time this object is set to "is not Active"
	/// Trigger on disable on each component
	/// </summary>
	void OnDisable();


	void swap(GameObject& _gameObject);
};
