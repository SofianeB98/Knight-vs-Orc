#include "Charge.h"
#include "Character.h"

Charge::Charge() : Ability(3, 60.0f)
{
}

Charge::Charge(unsigned _abilityCooldown) : Ability(_abilityCooldown, 60.0f)
{
}

Charge::Charge(unsigned _abilityCooldown, float _abilitySuccessPercent) : Ability(_abilityCooldown, _abilitySuccessPercent)
{
}

Charge::Charge(const Charge& _a) : Ability(_a)
{
}

Charge& Charge::operator=(Charge _a)
{
	Ability::swap(_a);
	return *this;
}



void Charge::Launch(Character& _c)
{
	// Base launch method handle :
	// - Ability available
	// - Wheel random to test if we can launch this ability (random between 0 and 100)
	// we juste have to add the ability behavior
	Ability::Launch(_c);

	// Charge behavior
	// Multiply by 2 the character damage for this turn
	_c.damageMultiplier.AddModifier({ StatModifierType::Multiplier, 2.0f, 1 });
}
