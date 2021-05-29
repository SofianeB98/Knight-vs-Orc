#include "Weapon.h"

Weapon::Weapon() : damage(1)
{
	
}

Weapon::Weapon(float damage) : damage(damage)
{
}

Weapon::Weapon(const Weapon& w) : damage(w.damage)
{
}

Weapon& Weapon::operator=(Weapon w)
{
	swap(w);
	return *this;
}

void Weapon::swap(Weapon& w)
{
	std::swap(this->damage, w.damage);
}


float Weapon::GetDamage() const
{
	return this->damage.GetValue();
}