#include <iostream>

#include "Stat.h"
#include "StatModifier.h"

int main()
{
    std::cout << "Hello World!\n";

	Stat myStat(10);

	StatModifier modMulPermanent(StatModifierType::Multiplier, 2, -1);
	StatModifier modMul(StatModifierType::Multiplier, 10, 2);
	StatModifier modPercentMul(StatModifierType::PercentMultiplier, 100, 3);
	
	myStat.AddMultipleModifier({ modMul, modPercentMul, modMulPermanent });

	std::cout << "First before update -- My stat value = " << myStat.GetValue() << std::endl;

	myStat.UpdateModifiers(); // After update, we have 3 modifiers
	std::cout << "Modifiers updated" << std::endl;
	std::cout << "My stat value = " << myStat.GetValue() << std::endl; 

	myStat.UpdateModifiers(); // After update, we have 2 modifiers
	std::cout << "Modifiers updated" << std::endl;
	std::cout << "My stat value = " << myStat.GetValue() << std::endl;

	myStat.UpdateModifiers(); // After update, only the permanent modifier
	std::cout << "Modifiers updated" << std::endl;
	std::cout << "My stat value = " << myStat.GetValue() << std::endl;

	myStat.UpdateModifiers();
	std::cout << "Modifiers updated" << std::endl;
	std::cout << "My stat value = " << myStat.GetValue() << std::endl;
}
