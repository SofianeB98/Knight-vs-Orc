#include "ChargeAbility.h"
#include "Character.h"

ChargeAbility::ChargeAbility() : Ability(3, 60.0f)
{
}

ChargeAbility::ChargeAbility(unsigned _abilityCooldown) : Ability(_abilityCooldown, 60.0f)
{
}

ChargeAbility::ChargeAbility(unsigned _abilityCooldown, float _abilitySuccessPercent) : Ability(_abilityCooldown, _abilitySuccessPercent)
{
}

ChargeAbility::ChargeAbility(const ChargeAbility& _a) : Ability(_a)
{
}

ChargeAbility& ChargeAbility::operator=(ChargeAbility _a)
{
	Ability::swap(_a);
	return *this;
}



void ChargeAbility::Launch(Character& _abilityOwner, Character& _abilityTarget)
{
	// CanLaunchAbility method handle :
	// - Ability available
	// - Wheel random to test if we can launch this ability (random between 0 and 100)
	// we juste have to add the ability behavior
	if (!CanLaunchAbility())
		return;

	// Charge behavior
	// Multiply by 2 the character owner damage for this turn
	_abilityOwner.damageMultiplier.AddModifier({ StatModifierType::Multiplier, 2.0f, 1 });
}
