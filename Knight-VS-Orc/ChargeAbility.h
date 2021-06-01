#pragma once
#include "Ability.h"

class ChargeAbility : public Ability
{
public:
#pragma region Constructor
	/// <summary>
	/// Base constructor for charge ability
	/// Initialise cooldown to 3 and success percent to 60
	/// </summary>
	ChargeAbility();

	/// <summary>
	/// Create charge ability with specific cooldown, percent is set to 60
	/// </summary>
	/// <param name="_abilityCooldown"></param>
	ChargeAbility(unsigned int _abilityCooldown);

	/// <summary>
	/// Create charge ability with specific coold down and success percent
	/// </summary>
	/// <param name="_abilityCooldown"></param>
	/// <param name="_abilitySuccessPercent"></param>
	ChargeAbility(unsigned int _abilityCooldown, float _abilitySuccessPercent);

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="a"></param>
	ChargeAbility(const ChargeAbility& _a);

	/// <summary>
	/// = operator
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	ChargeAbility& operator=(ChargeAbility _a);
#pragma endregion

	/// <summary>
	/// Trigger this ability to the specific character
	/// Multiply by 2 character damage
	/// </summary>
	/// <param name="_c"></param>
	virtual void Launch(Character& _c) override;
};
