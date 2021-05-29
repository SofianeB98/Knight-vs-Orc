#include "StatModifier.h"
#include "iostream"

float StatModifier::GetValue() const
{
	switch (this->type)
	{
	case Multiplier:
		return this->value;
		break;
	case PercentMultiplier:
		// Convert the value in percent to multiplier value
		// Add 1 to handle 100% = x2, 200% x3, ...
		return this->value * 0.01f + 1.0f;  
		break;
	}

	return this->value;
}

void StatModifier::swap(StatModifier& sm)
{
	std::swap(this->value, sm.value);
	std::swap(this->type, sm.type);
	std::swap(this->executionOrder, sm.executionOrder);
}
