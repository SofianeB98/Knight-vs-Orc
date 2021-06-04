#include "GameObject.h"
#include "Component.h"

unsigned int GameObject::CURRENT_ID = 0;

GameObject::GameObject() : isActive(true)
{
	GameObject::CURRENT_ID++;

	this->id = CURRENT_ID;
	
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

unsigned GameObject::GetId() const
{
	return this->id;
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