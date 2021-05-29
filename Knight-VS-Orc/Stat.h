#pragma once
#include <vector>

class StatModifier; // forward declaration

/// <summary>
/// Stat class is used to define a statistique and handle multiple
/// modifiers like equipement, boost, malus, ...
/// </summary>
class Stat
{
public:

#pragma region Constructor
	/// <summary>
	/// Create a default stat with base value as 0
	/// </summary>
	Stat()
	{
		baseValue = 0.0f;
		modifiers.reserve(5);
	}

	/// <summary>
	/// Create a stat with specific base value
	/// </summary>
	/// <param name="_baseValue"></param>
	Stat(float _baseValue) : baseValue(_baseValue)
	{
		modifiers.reserve(5);
	}

	/// <summary>
	/// Copy constructor
	/// copy all field of parameter
	/// </summary>
	/// <param name="s"></param>
	Stat(const Stat& s) : baseValue(s.baseValue), modifiers(s.modifiers) {}

	/// <summary>
	/// = operator of stat class
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	Stat& operator=(Stat s)
	{
		this->swap(s);
		return *this;
	}
#pragma endregion 

	~Stat()
	{
		modifiers.clear();
	}

#pragma region Modifier Method
	/// <summary>
	/// Add the modifier to this modifiers
	/// </summary>
	/// <param name="_modifier"></param>
	void AddModifier(StatModifier _modifier);
	
	/// <summary>
	/// Add all modifiers parameters to this modifiers
	/// </summary>
	/// <param name="_modifiers"></param>
	void AddMultipleModifier(std::vector<StatModifier> _modifiers);

	/// <summary>
	/// Update durability of all modifiers
	/// </summary>
	void UpdateModifiers();
#pragma endregion 

	/// <summary>
	/// Return the final value of this stat
	/// </summary>
	/// <returns></returns>
	float GetValue() const;

private:
	float baseValue;
	std::vector<StatModifier> modifiers;

	/// <summary>
	/// Sort by order this modifiers
	/// </summary>
	void SortModifiersByExecutionOrder();
	
	/// <summary>
	/// Return the final value after all modifiers was applied
	/// </summary>
	/// <returns></returns>
	float CalculateRealValue() const;

	// Copy & Swap, this method is used by "= operator"
	/// <summary>
	/// Swap this class field with parameter value
	/// </summary>
	/// <param name="s"></param>
	void swap(Stat& s);
	
};
