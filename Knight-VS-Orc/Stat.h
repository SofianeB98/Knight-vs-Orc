#pragma once
#include <vector>
#include "StatModifier.h"

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
	Stat();

	/// <summary>
	/// Create a stat with specific base value
	/// </summary>
	/// <param name="_baseValue"></param>
	Stat(float _baseValue);

	/// <summary>
	/// Copy constructor
	/// copy all field of parameter
	/// </summary>
	/// <param name="_s"></param>
	Stat(const Stat& _s);

	/// <summary>
	/// = operator of stat class
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	Stat& operator=(Stat _s);
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
	float GetValue();

private:
	float baseValue;
	float previousValue;
	bool isDirty;
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
	void swap(Stat& _s);
	
};
