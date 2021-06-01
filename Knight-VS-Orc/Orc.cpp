#include "Orc.h"

Orc::Orc() : Character()
{
}

Orc::Orc(Weapon& _w, Ability& _a) : Character(_w, _a)
{
}

Orc::Orc(const Orc& _c) : Character(_c)
{
	
}

Orc& Orc::operator=(Orc _c)
{
	Character::swap(_c);
	return *this;
}
