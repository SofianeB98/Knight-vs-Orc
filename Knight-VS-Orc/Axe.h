#pragma once
#include "Weapon.h"

class Axe : public Weapon
{
public:
#pragma region Constructor
	Axe();
	Axe(float _damage);
	Axe(const Axe& _axe);

	Axe& operator=(Axe _axe);
#pragma endregion
};
