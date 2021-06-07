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

Character::Character(Weapon& _w, Ability& _a) : Character()
{
	this->weapon = &_w;
	this->ability = &_a;
}

Character::Character(const Character& _c) : life(_c.life), damageMultiplier(_c.damageMultiplier), weapon(_c.weapon), ability(_c.ability), status(_c.status)
{
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


bool Character::IsAbilityAvailable() const
{
	return this->ability->IsAvailable();
}

void Character::UpdateCharacterFields()
{
	// Update all stat modifiers
	this->life.UpdateModifiers();
	this->damageMultiplier.UpdateModifiers();

	// Update Ability cooldown
	if(this->ability != nullptr)
		this->ability->UpdateCooldown();
	
	// Update Status cooldown
	UpdateStatus();
}

void Character::UpdateStatus()
{
	// For each status, update its durability
	for (auto& st : status)
	{
		if(st != nullptr)
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
	// Delete all status
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
	if (this->ability == nullptr)
		return;
	
	this->ability->Launch(*this,  _target);
}

void Character::UseWeapon(Character& _target)
{
	if (this->weapon == nullptr)
		return;

	// Before appliying damage, we calculate Weapon damage * Damage multiplier
	const float damage = this->weapon->GetDamage() * this->damageMultiplier.GetValue();
	_target.TakeDamage(damage);
}

void Character::ApplyStatus(Status* _s)
{
	this->status.emplace_back(_s);
}

void Character::ProcessStatus(StatusType _statusType)
{
	for(auto& s : this->status)
		if(s != nullptr)
			s->ProcessStatus(*this, _statusType);
}

void Character::TakeDamage(float _damage)
{
	// By default we add a remove modifier type with a permanent durability
	this->life.AddModifier({ StatModifierType::Remove, _damage, -1 });
}


void Character::swap(Character& _c)
{
	std::swap(this->life, _c.life);
	std::swap(this->damageMultiplier, _c.damageMultiplier);
	std::swap(this->ability, _c.ability);
	std::swap(this->weapon, _c.weapon);
	std::swap(this->status, _c.status);
}