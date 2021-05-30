#include "Knight.h"

Knight::Knight() : Character(), shield(50)
{
	this->life = { 20 };
}

Knight::Knight(Weapon& _w, Ability& _a) : Character(_w, _a), shield(50)
{
	this->life = { 20 };
}

Knight::Knight(const Knight& _k) : Character(_k), shield(_k.shield)
{
}

Knight& Knight::operator=(Knight _k)
{
	swap(_k);
	return *this;
}

void Knight::swap(Knight& _k)
{
	Character::swap(_k);
	std::swap(this->shield, _k.shield);
}



void Knight::UpdateCharacterFields()
{
	// Process the base method
	Character::UpdateCharacterFields();

	// Update knight field
	this->shield.UpdateModifiers();
}

void Knight::TakeDamage(float _damage)
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