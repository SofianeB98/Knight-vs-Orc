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
		return this->value * 0.01f;
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
