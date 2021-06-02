#include "GameObject.h"
#include "Component.h"

GameObject::GameObject() : isActive(true)
{
	this->components.reserve(5);

	// When an object is created, we call On Enable()
	OnEnable();
}

GameObject::GameObject(const GameObject& _gameObject) : isActive(_gameObject.isActive), components(_gameObject.components)
{
	
}

GameObject& GameObject::operator=(GameObject _gameObject)
{
	swap(_gameObject);
	return *this;
}

void GameObject::swap(GameObject& _gameObject)
{
	std::swap(this->isActive, _gameObject.isActive);
	std::swap(this->components, _gameObject.components);
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
	// Don't update this object if isn't enable
	if (!this->isActive)
		return;
	
	for(auto& component : this->components)
	{
		component->Update(*this, _dt);
	}
}



void GameObject::SetActive(bool _val)
{
	// the actual value equals the parameter, we won't update this state
	if (this->isActive == _val)
		return;

	this->isActive = _val;

	// Trigger the right callback
	if (this->isActive)
		OnEnable();
	else
		OnDisable();
}

bool GameObject::IsActive() const
{
	return this->isActive;
}

void GameObject::OnEnable()
{
	for (auto& component : this->components)
	{
		if (component == nullptr)
			continue;

		component->OnEnable(*this);
	}
}

void GameObject::OnDisable()
{
	for (auto& component : this->components)
	{
		if (component == nullptr)
			continue;

		component->OnDisable(*this);
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
	Component* component = new T;
	this->components.emplace_back(component);

	// When we add a new component, call the start method of it
	component->Start(*this);
	
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
