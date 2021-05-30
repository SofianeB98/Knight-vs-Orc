#pragma once
#include "Ability.h"

class Charge : public Ability
{
public:
#pragma region Constructor
	/// <summary>
	/// Base constructor for charge ability
	/// Initialise cooldown to 1 and success percent to 50
	/// </summary>
	Charge();

	/// <summary>
	/// Create charge ability with specific cooldown, percent is set to 50
	/// </summary>
	/// <param name="_abilityCooldown"></param>
	Charge(unsigned int _abilityCooldown);

	/// <summary>
	/// Create charge ability with specific coold down and success percent
	/// </summary>
	/// <param name="_abilityCooldown"></param>
	/// <param name="_abilitySuccessPercent"></param>
	Charge(unsigned int _abilityCooldown, float _abilitySuccessPercent);

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="a"></param>
	Charge(const Charge& _a);

	/// <summary>
	/// = operator
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	Charge& operator=(Charge _a);
#pragma endregion

	/// <summary>
	/// Trigger this ability to the specific character
	/// Multiply by 2 character damage
	/// </summary>
	/// <param name="_c"></param>
	virtual void Launch(Character& _c) override;
};
