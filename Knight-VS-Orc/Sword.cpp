#include "Sword.h"

Sword::Sword() : Weapon(5.0f)
{
}

Sword::Sword(float _damage) : Weapon(_damage)
{
}

Sword::Sword(const Sword& _sword) : Weapon(_sword)
{
}

Sword& Sword::operator=(Sword _sword)
{
	Weapon::swap(_sword);
	return *this;
}
