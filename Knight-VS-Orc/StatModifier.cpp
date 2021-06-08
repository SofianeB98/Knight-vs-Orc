#include "StatModifier.h"
#include "iostream"

StatModifier::StatModifier() : type(StatModifierType::Multiplier), value(0.0f), executionOrder(static_cast<int>(StatModifierType::Multiplier)), durability(1) {}

StatModifier::StatModifier(StatModifierType _type, float _value, int _durability) : type(_type), value(_value), executionOrder(static_cast<int>(_type)), durability(_durability) {}

StatModifier::StatModifier(StatModifierType _type, float _value, int _executionOrder, int _durability) : type(_type), value(_value), executionOrder(_executionOrder), durability(_durability) {}

StatModifier::StatModifier(const StatModifier& _sm) : type(_sm.type), value(_sm.value), executionOrder(_sm.executionOrder), durability(_sm.durability) {}

StatModifier& StatModifier::operator=(StatModifier _sm)
{
	this->swap(_sm);
	return *this;
}
float StatModifier::GetValue() const
{
	switch (this->type)
	{
	case Multiplier:
		return this->value;
	case PercentMultiplier:
		// Convert the value in percent to multiplier value
		// Add 1 to handle 100% = x2, 200% x3, ...
		return this->value * 0.01f + 1.0f;
	case Add:
	case Remove:
		return this->value;
	}

	return this->value;
}

void StatModifier::UpdateModifierDurability()
{
	// If the durability is set to -1
	// The modifier is a permanent modifier
	if (this->durability == -1)
		return;

	this->durability -= 1;
}


void StatModifier::swap(StatModifier& _sm)
{
	std::swap(this->value, _sm.value);
	std::swap(this->type, _sm.type);
	std::swap(this->executionOrder, _sm.executionOrder);
}
