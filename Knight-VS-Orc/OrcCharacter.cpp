#include "OrcCharacter.h"

#include "AxeWeapon.h"
#include "StunAbility.h"

OrcCharacter::OrcCharacter() : Character(*new AxeWeapon, *new StunAbility)
{
	this->life = { 60 };
}

OrcCharacter::OrcCharacter(Weapon& _w, Ability& _a) : Character(_w, _a)
{
	this->life = { 60 };
}

OrcCharacter::OrcCharacter(const OrcCharacter& _c) : Character(_c)
{
	
}

OrcCharacter& OrcCharacter::operator=(OrcCharacter _c)
{
	Character::swap(_c);
	return *this;
}

bool OrcCharacter::IsAlive()
{
	return this->life.GetValue() > 0;
}

std::string OrcCharacter::GetCharacterInformation()
{
	std::string info = "Orc\n";
	info += "Life = " + std::to_string(this->life.GetValue()) + "\n";
	info += "Ability = ";
	if (this->ability->IsAvailable())
		info += "available \n";
	else
		info += "reloading \n";

	info += "Weapon = " + std::to_string(this->weapon->GetDamage()) + "(x" + std::to_string(this->damageMultiplier.GetValue()) + ")" + "\n";

	return info;
}
