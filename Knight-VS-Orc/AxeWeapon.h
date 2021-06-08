#pragma once
#include "Weapon.h"

class AxeWeapon : public Weapon
{
public:
#pragma region Constructor
	/// <summary>
	/// Create default Axe with 8 damage
	/// </summary>
	AxeWeapon();
	AxeWeapon(float _damage);
	AxeWeapon(const AxeWeapon& _axe);

	AxeWeapon& operator=(AxeWeapon _axe);
#pragma endregion
};
