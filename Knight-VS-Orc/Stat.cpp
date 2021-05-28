#include "Stat.h"

#include "StatModifier.h"


void Stat::swap(Stat& s)
{
	std::swap(this->baseValue, s.baseValue);
	std::swap(this->modifiers, s.modifiers);
}

void Stat::AddModifier(StatModifier _modifier)
{
	
}

void Stat::AddMultipleModifier(std::vector<StatModifier> _modifiers)
{
	
}

float Stat::GetValue()
{
	return CalculateRealValue();
}

float Stat::CalculateRealValue() const
{
	// Initialize a value to the base value
	float realValue = this->baseValue;

	// Process all modifiers
	for(auto& mod : this->modifiers)
	{
		switch (mod.GetModifierType())
		{
		case StatModifierType::Multiplier:
			break;
			
		case StatModifierType::PercentMultiplier:
			break;
		} 
	}
	
	return realValue;
}

void Stat::UpdateModifiers()
{
	
}
