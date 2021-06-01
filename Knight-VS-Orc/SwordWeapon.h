#pragma once
#include "Weapon.h"

class SwordWeapon : public Weapon
{
public:
#pragma region Constructor
	SwordWeapon();
	SwordWeapon(float _damage);
	SwordWeapon(const SwordWeapon& _sword);
	
	SwordWeapon& operator=(SwordWeapon _sword);
#pragma endregion
	
protected:

private:
};
