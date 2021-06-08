#pragma once
#include "Weapon.h"

class SwordWeapon : public Weapon
{
public:
#pragma region Constructor
	/// <summary>
	/// Create default Sword with 5 damage
	/// </summary>
	SwordWeapon();
	SwordWeapon(float _damage);
	SwordWeapon(const SwordWeapon& _sword);
	
	SwordWeapon& operator=(SwordWeapon _sword);
#pragma endregion
	
protected:

private:
};
