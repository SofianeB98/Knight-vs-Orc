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



void StunAbility::Launch(Character& _c)
{
	// Base launch method handle :
	// - Ability available
	// - Wheel random to test if we can launch this ability (random between 0 and 100)
	// we juste have to add the ability behavior
	Ability::Launch(_c);

	// Stun ability apply the stuned status to the target
	_c.ApplyStatus(new StunnedStatus);
}
