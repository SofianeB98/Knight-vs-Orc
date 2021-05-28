#pragma once

/// <summary>
/// Enum to define all modifier type
/// </summary>
enum StatModifierType
{
	Multiplier = 0, // Flat value, between min value and max value, which multiply the stat value
	PercentMultiplier = 10 // Value in percent, between 0 and float max value, which modify the stat by it's value
};

/// <summary>
/// The Stat modifier class is used to add modifier to a stat
/// A modifier has :
/// - Value => used to modify final stat value
/// - Type => to tell how the value is used
/// - Execution order => to sort correctly and execute in the right order
/// - Durability => Define the time which a modifier exist in a stat. Set to -1 correspond to permanent modifier
/// </summary>
class StatModifier
{
public:
#pragma region Constructor
	/// <summary>
	/// Create a default stat modifier with default value
	/// </summary>
	StatModifier() : type(StatModifierType::Multiplier), value(0.0f), executionOrder(static_cast<int>(StatModifierType::Multiplier)), durability(1){}

	/// <summary>
	/// Create a stat modifier with specific type, value and durability
	/// </summary>
	/// <param name="_type"></param>
	/// <param name="_value">Between 0 and MaxValue for Percent type, and MinValue <-> MaxValue for Flat type</param>
	/// <param name="_durability">Decrease at the end of a turn</param>
	StatModifier(StatModifierType _type, float _value, int _durability) : type(_type), value(_value), executionOrder(static_cast<int>(_type)), durability(_durability) {}

	/// <summary>
	/// Create a stat modifier with specific type, value, execution order and durability
	/// </summary>
	/// <param name="_type"></param>
	/// <param name="_value">Between 0 and MaxValue for Percent type, and MinValue <-> MaxValue for Flat type</param>
	/// <param name="_executionOrder"></param>
	/// <param name="_durability">Decrease at the end of a turn</param>
	StatModifier(StatModifierType _type, float _value, int _executionOrder, int _durability) : type(_type), value(_value), executionOrder(_executionOrder), durability(_durability) {}

	/// <summary>
	/// Copy constructor
	/// copy all field of parameter
	/// </summary>
	/// <param name="sm"></param>
	StatModifier(const StatModifier& sm) : type(sm.type), value(sm.value), executionOrder(sm.executionOrder), durability(sm.durability){}

	/// <summary>
	/// = operator of stat class
	/// </summary>
	/// <param name="sm"></param>
	/// <returns></returns>
	StatModifier& operator=(StatModifier sm)
	{
		this->swap(sm);
		return *this;
	}
#pragma endregion 

	~StatModifier() = default;

#pragma region Getter
	/// <summary>
	/// Return this modifier type
	/// </summary>
	/// <returns></returns>
	StatModifierType GetModifierType() const
	{
		return this->type;
	}

	/// <summary>
	/// Return modifier value with specific process if necessary
	/// </summary>
	/// <returns></returns>
	float GetValue() const;

	/// <summary>
	/// Return this execution order
	/// Used in stat class to sort all modifiers
	/// </summary>
	/// <returns></returns>
	int GetExecutionOrder() const
	{
		return this->executionOrder;
	}

	/// <summary>
	/// Return this durability
	/// </summary>
	/// <returns></returns>
	int GetDurability() const
	{
		return this->durability;
	}
#pragma endregion

	/// <summary>
	/// Remove 1 to durability
	/// if set to -1, return
	/// </summary>
	void UpdateModifierDurability()
	{
		// If the durability is set to -1
		// The modifier is a permanent modifier
		if (this->durability == -1)
			return;

		this->durability-=1;
	}
	
private:
	StatModifierType type;
	float value;
	int executionOrder;
	int durability;
	
	// Copy & Swap, this method is used by "= operator"
	/// <summary>
	/// Swap this class field with parameter value
	/// </summary>
	/// <param name="s"></param>
	void swap(StatModifier& sm);
};
