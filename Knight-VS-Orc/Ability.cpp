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

Ability::Ability(const Ability& a) : abilityCooldown(a.abilityCooldown), actualCooldown(a.actualCooldown), abilitySuccessPercent(a.abilitySuccessPercent)
{
}

Ability& Ability::operator=(Ability a)
{
	swap(a);
	return *this;
}

void Ability::swap(Ability& a)
{
	std::swap(this->abilityCooldown, a.abilityCooldown);
	std::swap(this->actualCooldown, a.actualCooldown);
	std::swap(this->abilitySuccessPercent, a.abilitySuccessPercent);
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

void Ability::ReduceCooldown(unsigned int reduceCount)
{
	// Clamp value to actual cooldown
	if (reduceCount > this->actualCooldown)
		reduceCount = this->actualCooldown;

	this->actualCooldown -= reduceCount;
}

void Ability::ResetCooldown()
{
	this->actualCooldown = this->abilityCooldown;
}

void Ability::Launch(Character& c)
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