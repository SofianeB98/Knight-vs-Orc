#include "Weapon.h"

Weapon::Weapon() : damage(1)
{
	
}

Weapon::Weapon(float _damage) : damage(_damage)
{
}

Weapon::Weapon(const Weapon& _w) : damage(_w.damage)
{
}

Weapon& Weapon::operator=(Weapon _w)
{
	swap(_w);
	return *this;
}

void Weapon::swap(Weapon& _w)
{
	std::swap(this->damage, _w.damage);
}


float Weapon::GetDamage()
{
	return this->damage.GetValue();
}