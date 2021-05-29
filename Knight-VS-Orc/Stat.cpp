#include "Stat.h"

#include <algorithm>

#include "StatModifier.h"


void Stat::swap(Stat& s)
{
	std::swap(this->baseValue, s.baseValue);
	std::swap(this->modifiers, s.modifiers);
}



void Stat::AddModifier(StatModifier _modifier)
{
	// Add modifier parameter to the vector
	this->modifiers.push_back(_modifier);
	// Sort the vector by execution order
	SortModifiersByExecutionOrder();
}

void Stat::AddMultipleModifier(std::vector<StatModifier> _modifiers)
{
	// Add all modifiers
	for (auto& m : _modifiers)
		this->modifiers.push_back(m);

	// Sort by order
	SortModifiersByExecutionOrder();
}

void Stat::SortModifiersByExecutionOrder()
{
	std::sort(modifiers.begin(), modifiers.end(), [](StatModifier a, StatModifier b)
		{
			return a.GetExecutionOrder() < b.GetExecutionOrder();
		});
}



float Stat::GetValue() const
{
	return CalculateRealValue();
}

float Stat::CalculateRealValue() const
{
	// Initialize a value to the base value
	float realValue = this->baseValue;

	// Process all modifiers by there type
	for(auto& mod : this->modifiers)
	{
		switch (mod.GetModifierType())
		{
			// Percent Multiplier and Multiplier process are identical
		case StatModifierType::PercentMultiplier:
		case StatModifierType::Multiplier:
			realValue *= mod.GetValue();
			break;
		} 
	}
	
	return realValue;
}



void Stat::UpdateModifiers()
{
	// Update all modifier durability
	for (auto& mod : this->modifiers)
		mod.UpdateModifierDurability();

	// Remove all modifier with a 0 durability
	const auto removed = std::remove_if(this->modifiers.begin(), this->modifiers.end(), [](StatModifier sm)
	{
		return sm.GetDurability() == 0;
	});

	// "Resize" the vector to remove useless removed value
	this->modifiers.resize(std::distance(this->modifiers.begin(), removed));
}
