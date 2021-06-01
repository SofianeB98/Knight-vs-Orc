#include "AxeWeapon.h"

AxeWeapon::AxeWeapon() : Weapon(8.0f)
{
}

AxeWeapon::AxeWeapon(float _damage) : Weapon(_damage)
{
}

AxeWeapon::AxeWeapon(const AxeWeapon& _axe) : Weapon(_axe)
{
}

AxeWeapon& AxeWeapon::operator=(AxeWeapon _axe)
{
	Weapon::swap(_axe);
	return *this;
}
