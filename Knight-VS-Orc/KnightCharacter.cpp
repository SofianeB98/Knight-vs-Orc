#include "KnightCharacter.h"

#include "SwordWeapon.h"
#include "ChargeAbility.h"
#include "Utils.h"

KnightCharacter::KnightCharacter() : Character(*new SwordWeapon, *new ChargeAbility), shield(50)
{
	this->life = { 20 };
}

KnightCharacter::KnightCharacter(Weapon& _w, Ability& _a) : Character(_w, _a), shield(50)
{
	this->life = { 20 };
}

KnightCharacter::KnightCharacter(const KnightCharacter& _k) : Character(_k), shield(_k.shield)
{
}

KnightCharacter& KnightCharacter::operator=(KnightCharacter _k)
{
	swap(_k);
	return *this;
}

void KnightCharacter::swap(KnightCharacter& _k)
{
	Character::swap(_k);
	std::swap(this->shield, _k.shield);
}

bool KnightCharacter::IsAlive()
{

	// If Shield OR Life is greater than 0, knight is alive
	if (this->shield.GetValue() > 0)
		return true;
	
	return this->life.GetValue() > 0;
}

std::string KnightCharacter::GetCharacterInformation()
{
	std::string info = "Knight\n";
	info += "Shield = " + Utils::ToString(this->shield.GetValue(), 1) + "\n";
	info += "Life = " + Utils::ToString(this->life.GetValue(), 1) + "\n";
	info += "Ability = ";
	if (this->ability->IsAvailable())
		info += "available \n";
	else
		info += "reloading: " + Utils::ToString(this->ability->GetActualCooldown(), 0) + " Turn" + "\n";

	info += "Weapon = " + Utils::ToString(this->weapon->GetDamage(), 1) + "(x" + Utils::ToString(this->damageMultiplier.GetValue(), 1) + ")" + "\n";

	return info;
}


void KnightCharacter::UpdateCharacterFields()
{
	// Process the base method
	Character::UpdateCharacterFields();

	// Update knight field
	this->shield.UpdateModifiers();
}

void KnightCharacter::TakeDamage(float _damage)
{
	// Check if shield value is ok
	if(shield.GetValue() > 0.0f)
	{
		// Check if shield value is greater or equal than damage
		if(shield.GetValue() >= _damage)
		{
			// Remove damage to shield
			shield.AddModifier({ StatModifierType::Remove, _damage, -1 });
			return;
		}

		// Else, remove shield
		// And recalculate damage to remove it to life
		_damage -= shield.GetValue();
		shield.AddModifier({ StatModifierType::Remove, shield.GetValue(), -1 });
		life.AddModifier({ StatModifierType::Remove, _damage, -1 });
		
		return;
	}

	// If shield is over, remove to life
	life.AddModifier({ StatModifierType::Remove, _damage, -1 });
}