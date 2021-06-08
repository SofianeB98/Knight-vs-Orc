#include "OrcCharacter.h"

#include "AxeWeapon.h"
#include "StunAbility.h"
#include "Utils.h"

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
	// If orc life is greater than 0, return true
	return this->life.GetValue() > 0;
}


std::string OrcCharacter::GetCharacterInformation()
{
	std::string info = "Orc\n";
	info += "Life = " + Utils::ToString(this->life.GetValue(), 1) + "\n";
	info += "Ability = ";
	if (this->ability->IsAvailable())
		info += "available \n";
	else
		info += "reloading: " + Utils::ToString(this->ability->GetActualCooldown(), 0) + " Turn" + "\n";

	info += "Weapon = " + Utils::ToString(this->weapon->GetDamage(), 1) + "(x" + Utils::ToString(this->damageMultiplier.GetValue(), 1) + ")" + "\n";

	return info;
}
