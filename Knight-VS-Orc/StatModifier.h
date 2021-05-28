#pragma once

enum StatModifierType
{
	Multiplier = 0, // Flat value which multiply the stat value
	PercentMultiplier = 10 // Value in percent, between 0 and float max value, which modify the stat by it's value
};

class StatModifier
{
public:
#pragma region Constructor
	StatModifier() : type(StatModifierType::Multiplier), value(0.0f), executionOrder(static_cast<int>(StatModifierType::Multiplier)){}
	StatModifier(StatModifierType _type, float _value) : type(_type), value(_value), executionOrder(static_cast<int>(_type)) {}
	StatModifier(StatModifierType _type, float _value, int _executionOrder) : type(_type), value(_value), executionOrder(_executionOrder){}
	StatModifier(const StatModifier& sm) : type(sm.type), value(sm.value), executionOrder(sm.executionOrder){}

	StatModifier& operator=(StatModifier sm)
	{
		this->swap(sm);
		return *this;
	}
#pragma endregion 

	~StatModifier() = default;
	
	StatModifierType GetModifierType() const
	{
		return this->type;
	}
	float GetValue() const;
	
	int GetExecutionOrder() const
	{
		return this->executionOrder;
	}
	
private:
	StatModifierType type;
	float value;
	int executionOrder;
	
	void swap(StatModifier& sm);
};
