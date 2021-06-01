#include "SwordWeapon.h"

SwordWeapon::SwordWeapon() : Weapon(5.0f)
{
}

SwordWeapon::SwordWeapon(float _damage) : Weapon(_damage)
{
}

SwordWeapon::SwordWeapon(const SwordWeapon& _sword) : Weapon(_sword)
{
}

SwordWeapon& SwordWeapon::operator=(SwordWeapon _sword)
{
	Weapon::swap(_sword);
	return *this;
}
