#pragma once
#include "Weapon.h"

class Sword : public Weapon
{
public:
#pragma region Constructor
	Sword();
	Sword(float _damage);
	Sword(const Sword& _sword);
	
	Sword& operator=(Sword _sword);
#pragma endregion
	
protected:

private:
};
