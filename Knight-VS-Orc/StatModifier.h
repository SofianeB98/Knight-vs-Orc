#pragma once


enum StatModifierType
{
	Multiplier, // Flat value which multiply the stat value
	PercentMultiplier // Value in percent, which modify the stat by it's value
};

class StatModifier
{
public:
	StatModifier() : type(StatModifierType::Multiplier)
	{
		
	}
	
	StatModifierType GetModifierType() const
	{
		return this->type;
	}
	
private:
	StatModifierType type;
	
};
