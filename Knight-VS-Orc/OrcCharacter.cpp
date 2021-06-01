﻿#include "OrcCharacter.h"

#include "Axe.h"
#include "StunAbility.h"

OrcCharacter::OrcCharacter() : Character(*new Axe, *new StunAbility)
{
}

OrcCharacter::OrcCharacter(Weapon& _w, Ability& _a) : Character(_w, _a)
{
}

OrcCharacter::OrcCharacter(const OrcCharacter& _c) : Character(_c)
{
	
}

OrcCharacter& OrcCharacter::operator=(OrcCharacter _c)
{
	Character::swap(_c);
	return *this;
}