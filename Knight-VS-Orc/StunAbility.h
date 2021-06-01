#pragma once
#include "Ability.h"

class StunAbility : public Ability
{
public:
#pragma region Constructor
	/// <summary>
	/// Base constructor for StunAbility
	/// Initialise cooldown to 5 and success percent to 20
	/// </summary>
	StunAbility();

	/// <summary>
	/// Create Stun Ability with specific cooldown, percent is set to 20
	/// </summary>
	/// <param name="_abilityCooldown"></param>
	StunAbility(unsigned int _abilityCooldown);

	/// <summary>
	/// Create Stun ability with specific cooldown and success percent
	/// </summary>
	/// <param name="_abilityCooldown"></param>
	/// <param name="_abilitySuccessPercent"></param>
	StunAbility(unsigned int _abilityCooldown, float _abilitySuccessPercent);

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="a"></param>
	StunAbility(const StunAbility& _a);

	/// <summary>
	/// = operator
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	StunAbility& operator=(StunAbility _a);
#pragma endregion

	/// <summary>
	/// Trigger this ability to the specific character
	/// Add Stuned status to the target
	/// </summary>
	/// <param name="_c"></param>
	virtual void Launch(Character& _c) override;
};
