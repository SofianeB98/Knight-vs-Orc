#pragma once
#include <vector>

class GameObject
{
public:
friend class Component;
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

	template <typename T>
	T& AddComponent(T* _component);
	
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

template <typename T>
T& GameObject::AddComponent()
{
	static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

	// We search if the component exist into this components list
	// if true, return it
	if (T* objectComponent = GetComponent<T>())
		return *objectComponent;

	// else, create a new component and return its reference to modify it
	Component* component = new T;
	this->components.emplace_back(component);

	// When we add a new component, call the start method of it
	component->Start(*this);

	return *component;
}

template <typename T>
T& GameObject::AddComponent(T* _component)
{
	static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

	// We search if the component exist into this components list
	// if true, return it
	if (T* objectComponent = GetComponent<T>())
		return *objectComponent;

	// else, create a new component and return its reference to modify it
	this->components.emplace_back(_component);

	// When we add a new component, call the start method of it
	_component->Start(*this);

	return *_component;
}

template <typename T>
T* GameObject::GetComponent() const
{
	static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

	// Search the first component T
	auto found = std::find_if(this->components.begin(), this->components.end(), [](Component* component) {
		return dynamic_cast<T*>(component);
		});

	// If we not found a component, return null else return it
	return found == this->components.end() ? nullptr : static_cast<T*>(*found);
}