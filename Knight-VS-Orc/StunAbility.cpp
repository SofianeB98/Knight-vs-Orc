#include "StunAbility.h"
#include "Character.h"
#include "StunnedStatus.h"

StunAbility::StunAbility() : Ability(5, 20.0f)
{
}

StunAbility::StunAbility(unsigned _abilityCooldown) : Ability(_abilityCooldown, 20.0f)
{
}

StunAbility::StunAbility(unsigned _abilityCooldown, float _abilitySuccessPercent) : Ability(_abilityCooldown, _abilitySuccessPercent)
{
}

StunAbility::StunAbility(const StunAbility& _a) : Ability(_a)
{
}

StunAbility& StunAbility::operator=(StunAbility _a)
{
	Ability::swap(_a);
	return *this;
}



void StunAbility::Launch(Character& _abilityOwner, Character& _abilityTarget)
{
	// CanLaunchAbility method handle :
	// - Ability available
	// - Wheel random to test if we can launch this ability (random between 0 and 100)
	// we juste have to add the ability behavior
	if (!CanLaunchAbility())
		return;

	// Stun ability apply the stunned status to the target
	_abilityTarget.ApplyStatus(new StunnedStatus);
}
