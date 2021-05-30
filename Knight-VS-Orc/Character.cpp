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

Character::Character(Weapon& _w, Ability& _a)
{
	this->weapon = &_w;
	this->ability = &_a;
}

Character::Character(const Character& _c) : life(_c.life), damageMultiplier(_c.damageMultiplier), weapon(_c.weapon), ability(_c.ability), status(_c.status)
{
}

Character& Character::operator=(Character _c)
{
	swap(_c);
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
	this->ability->UpdateCooldown();

	
	
	// Update Status cooldown
	UpdateStatus();
}

void Character::UpdateStatus()
{
	for (auto& st : status)
	{
		st->UpdateDurability();
	}

	// Remove all modifier with a 0 durability
	const auto removed = std::remove_if(this->status.begin(), this->status.end(), [](Status* st)
		{
			if (st != nullptr)
			{
				if (!st->IsTakingEffect())
				{
					delete st;
					st = nullptr;
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


void Character::UseAbility(Character& _target)
{
	this->ability->Launch(_target);
}

void Character::UseWeapon(Character& _target)
{
	const float damage = this->weapon->GetDamage() * this->damageMultiplier.GetValue();
	_target.TakeDamage(damage);
}

void Character::ApplyStatus(Status* _s)
{
	this->status.emplace_back(_s);
}

void Character::TakeDamage(float _damage)
{
	
}


void Character::swap(Character& _c)
{
	std::swap(this->life, _c.life);
	std::swap(this->damageMultiplier, _c.damageMultiplier);
	std::swap(this->ability, _c.ability);
	std::swap(this->weapon, _c.weapon);
	std::swap(this->status, _c.status);
}