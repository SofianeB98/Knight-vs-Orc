#pragma once

#include "Stat.h"

// Forward declaration
class Status;
class Weapon;
class Ability;

/// <summary>
/// Character is the base class for every character like Knight, Orc, Healer, ...
/// </summary>
class Character
{
public:
#pragma region Constructor
	/// <summary>
	/// Default constructor of Character class
	/// </summary>
	Character();

	Character(Weapon& w, Ability& a);
	
	/// <summary>
	/// Copy constructor of Character Class
	/// </summary>
	/// <param name="c"></param>
	Character(const Character& c);

	/// <summary>
	/// = operator of character class
	/// </summary>
	/// <param name="c"></param>
	/// <returns></returns>
	Character& operator=(Character c);
#pragma endregion 

	virtual ~Character();

#pragma region Character Method
	/// <summary>
	/// Call this method to try to use character ability on the specific target
	/// </summary>
	/// <param name="target"></param>
	virtual void UseAbility(Character& target);

	/// <summary>
	/// Call this method to use character weapon on the specific target
	/// </summary>
	/// <param name="target"></param>
	virtual void UseWeapon(Character& target);

	// Call by Use Ability, but make this method public because
	// we can imagine in a futur update, other object can apply a status
	/// <summary>
	/// This method apply a specific Status on this character
	/// </summary>
	/// <param name="target"></param>
	virtual void ApplyStatus(Status* s);
#pragma endregion 
	
	/// <summary>
	/// Call when a turn finish
	/// Update all modifiers, cooldown and durability of every fields
	/// </summary>
	virtual void UpdateCharacterFields();
	
protected:
	// Base Stats of every Character
	Stat life;
	Stat damageMultiplier;
	
	// Item & Ability of a character
	Weapon* weapon;
	Ability* ability;

	// Character status
	std::vector<Status*> status;

	/// <summary>
	/// Update all status durability
	/// And remove all status with 0 durability
	/// </summary>
	virtual void UpdateStatus();

	/// <summary>
	/// Apply damage to this character
	/// </summary>
	/// <param name="_damage"></param>
	virtual void TakeDamage(float _damage);

	// Copy & Swap, this method is used by "= operator"
	/// <summary>
	/// Swap this class field with parameter value
	/// </summary>
	/// <param name="c"></param>
	virtual void swap(Character& c);
private:

	/// <summary>
	/// Remove and destroy all status
	/// </summary>
	void ClearStatus();
};
