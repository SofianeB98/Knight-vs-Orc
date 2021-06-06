#include "Stat.h"

#include <algorithm>


void Stat::swap(Stat& _s)
{
	std::swap(this->baseValue, _s.baseValue);
	std::swap(this->previousValue, _s.previousValue);
	std::swap(this->isDirty, _s.isDirty);
	std::swap(this->modifiers, _s.modifiers);
}


Stat::Stat() : baseValue(0.0f), previousValue(0.0f), isDirty(false)
{
	modifiers.reserve(5);
}

Stat::Stat(float _baseValue) : baseValue(_baseValue), previousValue(_baseValue), isDirty(false)
{
	modifiers.reserve(5);
}

Stat::Stat(const Stat& _s) : baseValue(_s.baseValue), previousValue(_s.baseValue), isDirty(_s.isDirty), modifiers(_s.modifiers) {}

Stat& Stat::operator=(Stat _s)
{
	this->swap(_s);
	return *this;
}

void Stat::AddModifier(StatModifier _modifier)
{
	// Add modifier parameter to the vector
	this->modifiers.push_back(_modifier);

	// Because we've add new modifier, this stat is dirty and have to be re calculate
	this->isDirty = true;
	
	// Sort the vector by execution order
	SortModifiersByExecutionOrder();
}

void Stat::AddMultipleModifier(std::vector<StatModifier> _modifiers)
{
	// Add all modifiers
	for (auto& m : _modifiers)
		this->modifiers.push_back(m);

	// Because we've add new modifiers, this stat is dirty and have to be re calculate
	this->isDirty = true;
	
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



float Stat::GetValue()
{
	if (this->isDirty)
		this->previousValue = CalculateRealValue();

	this->isDirty = false;
	
	return this->previousValue;
}

float Stat::CalculateRealValue() const
{
	// Initialize a value to the base value
	float realValue = this->baseValue;

	// Process all modifiers by there type
	for (auto& mod : this->modifiers)
	{
		switch (mod.GetModifierType())
		{
			// Percent Multiplier and Multiplier process are identical
		case StatModifierType::PercentMultiplier:
		case StatModifierType::Multiplier:
			realValue *= mod.GetValue();
			break;
			
		case StatModifierType::Add:
			realValue += mod.GetValue();
			break;
			
		case StatModifierType::Remove:
			realValue -= mod.GetValue();
			break;
		}
	}

	return realValue;
}



void Stat::UpdateModifiers()
{
	auto previousModifierSize = this->modifiers.size();
	
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


	if (previousModifierSize != this->modifiers.size())
		this->isDirty = true;
	
}
