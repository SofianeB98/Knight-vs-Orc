#include "Character.h"

#include "Weapon.h"
#include "Ability.h"
#include "Status.h"

Character::Character() : life(10), damageMultiplier(1.0f)
{
	this->status.reserve(5);
	this->weapon = nullptr;
	this->ability = nullptr;
}

Character::Character(const Character& c) : life(c.life), damageMultiplier(c.damageMultiplier), weapon(c.weapon), ability(c.ability), status(c.status)
{
}

Character& Character::operator=(Character c)
{
	swap(c);
	return *this;
}


Character::~Character()
{
	if(this->weapon != nullptr)
	{
		delete this->weapon;
		this->weapon = nullptr;
	}

	if (this->ability != nullptr)
	{
		delete this->ability;
		this->ability = nullptr;
	}

	ClearStatus();
}


void Character::UpdateCharacterFields()
{
	// Update all stat modifiers
	this->life.UpdateModifiers();
	this->damageMultiplier.UpdateModifiers();

	// Update Ability cooldown


	// Update Status cooldown
	UpdateStatus();
}

void Character::UpdateStatus()
{
	for (auto& st : status)
	{

	}

	// Remove all modifier with a 0 durability
	const auto removed = std::remove_if(this->status.begin(), this->status.end(), [](Status* sm)
		{
			if (sm != nullptr)
			{
				if (0)
				{
					delete sm;
					sm = nullptr;
					return true;
				}

				return false;
			}

			return true;
		});

	// "Resize" the vector to remove useless removed value
	this->status.resize(std::distance(this->status.begin(), removed));
}

void Character::ClearStatus()
{
	for (auto& st : this->status)
	{
		if (st != nullptr)
		{
			delete st;
			st = nullptr;
		}
	}

	this->status.clear();
}


void Character::UseAbility(Character& target)
{
	
}

void Character::UseWeapon(Character& target)
{
	
}

void Character::ApplyStatus(Status* s)
{
	this->status.emplace_back(s);
}

void Character::TakeDamage(float _damage)
{
	
}


void Character::swap(Character& c)
{
	std::swap(this->life, c.life);
	std::swap(this->damageMultiplier, c.damageMultiplier);
	std::swap(this->ability, c.ability);
	std::swap(this->weapon, c.weapon);
	std::swap(this->status, c.status);
}