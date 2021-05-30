#include "Ability.h"

#include <cassert>
#include <iostream>


#include "Character.h"

Ability::Ability() : abilityCooldown(1), actualCooldown(0), abilitySuccessPercent(50)
{

}

Ability::Ability(unsigned int _abilityCooldown) : actualCooldown(0), abilitySuccessPercent(50)
{
	assert((int)_abilityCooldown >= 0 && "You're trying to set a negative cooldown");
	this->abilityCooldown = _abilityCooldown;
}

Ability::Ability(unsigned int _abilityCooldown, float _abilitySuccessPercent) : actualCooldown(0)
{
	assert((int)_abilityCooldown >= 0 && "You're trying to set a negative cooldown");
	this->abilityCooldown = _abilityCooldown;

	assert(_abilitySuccessPercent >= 0 && "You're trying to set a negative success percent");
	this->abilitySuccessPercent = _abilitySuccessPercent;
}

Ability::Ability(const Ability& _a) : abilityCooldown(_a.abilityCooldown), actualCooldown(_a.actualCooldown), abilitySuccessPercent(_a.abilitySuccessPercent)
{
}

Ability& Ability::operator=(Ability _a)
{
	swap(_a);
	return *this;
}

void Ability::swap(Ability& _a)
{
	std::swap(this->abilityCooldown, _a.abilityCooldown);
	std::swap(this->actualCooldown, _a.actualCooldown);
	std::swap(this->abilitySuccessPercent, _a.abilitySuccessPercent);
}



bool Ability::IsAvailable() const
{
	return this->actualCooldown == 0;
}

unsigned Ability::GetAbilityCooldown() const
{
	return this->abilityCooldown;
}

unsigned Ability::GetActualCooldown() const
{
	return this->actualCooldown;
}



void Ability::UpdateCooldown()
{
	if (IsAvailable())
		return;

	--this->actualCooldown;
}

void Ability::ReduceCooldown(unsigned int _reduceCount)
{
	// Clamp value to actual cooldown
	if (_reduceCount > this->actualCooldown)
		_reduceCount = this->actualCooldown;

	this->actualCooldown -= _reduceCount;
}

void Ability::ResetCooldown()
{
	this->actualCooldown = this->abilityCooldown;
}

void Ability::Launch(Character& _c)
{
	if (!IsAvailable())
	{
		std::cout << "You're ability will be available in " << this->actualCooldown << " turn." << std::endl;
		return;
	}

	// Launch a random wheel between 0 and 100
	float wheel = 0.0f;

	// Reset cooldown
	ResetCooldown();
	
	// if wheel result is greater than ability success
	if(wheel > this->abilitySuccessPercent)
	{
		std::cout << "Bad lucky. Ability launch failed" << std::endl;
		return;
	}
	
	// if wheel result is less (or equal) than ability success
	// Perform ability
	std::cout << "Success, Ability is launching !" << std::endl;
}