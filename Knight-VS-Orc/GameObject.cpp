#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
{
	this->components.reserve(5);
}

GameObject::~GameObject()
{
	Destroy();
}



void GameObject::Start()
{
	for (auto& component : this->components)
	{
		component->Start(*this);
	}
}

void GameObject::Update(double _dt)
{
	for(auto& component : this->components)
	{
		component->Update(*this, _dt);
	}
}



void GameObject::Destroy()
{
	for (auto& component : this->components)
	{
		if (component == nullptr)
			continue;

		delete component;
		component = nullptr;
	}

	this->components.clear();
}



template <typename T>
T& GameObject::AddComponent()
{
	static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
	
	// We search if the component exist into this components list
	// if true, return it
	if (T* objectComponent = GetComponent<T>())
		return *objectComponent;

	// else, create a new component and return its reference to modify it
	T* component = new T;
	this->components.emplace_back(component);

	return *component;
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
