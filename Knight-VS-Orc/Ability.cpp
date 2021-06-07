#include "Ability.h"

#include <cassert>
#include <iostream>

#include "Utils.h"

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


void Ability::swap(Ability& _a)
{
	std::swap(this->abilityCooldown, _a.abilityCooldown);
	std::swap(this->actualCooldown, _a.actualCooldown);
	std::swap(this->abilitySuccessPercent, _a.abilitySuccessPercent);
}


bool Ability::IsAvailable() const
{
	// An ability is available when its cooldown is equal to 0
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
	// If this ability is available
	// We don't reduce its cooldown
	if (IsAvailable())
		return;

	// else reduce cooldown by 1
	--this->actualCooldown;
}

void Ability::ReduceCooldown(unsigned int _reduceCount)
{
	// Clamp value to actual cooldown if necessary
	this->actualCooldown -= Utils::Clamp((int)_reduceCount, 0, (int)this->actualCooldown);
}

void Ability::ResetCooldown()
{
	this->actualCooldown = this->abilityCooldown;
}


bool Ability::CanLaunchAbility()
{
	// Check if this ability is available
	if (!IsAvailable())
	{
		std::cout << "You're ability will be available in " << this->actualCooldown << " turn." << std::endl;
		return false;
	}

	// Launch a random wheel between 0 and 100
	const float wheel = Utils::GetRandomFloat(0.0f, 100.0f);

	// Reset cooldown
	ResetCooldown();

	// if wheel result is greater than ability success percent
	if (wheel > this->abilitySuccessPercent)
	{
		std::cout << "Bad lucky. Ability launch failed" << std::endl;
		return false;
	}

	// if wheel result is less (or equal) than ability success
	// Perform ability
	std::cout << "Success, Ability is launching !" << std::endl;
	return true;
}
