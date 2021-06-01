#include "Axe.h"

Axe::Axe() : Weapon(8.0f)
{
}

Axe::Axe(float _damage) : Weapon(_damage)
{
}

Axe::Axe(const Axe& _axe) : Weapon(_axe)
{
}

Axe& Axe::operator=(Axe _axe)
{
	Weapon::swap(_axe);
	return *this;
}
