#pragma once
#include "Weapon.h"

class AxeWeapon : public Weapon
{
public:
#pragma region Constructor
	AxeWeapon();
	AxeWeapon(float _damage);
	AxeWeapon(const AxeWeapon& _axe);

	AxeWeapon& operator=(AxeWeapon _axe);
#pragma endregion
};
