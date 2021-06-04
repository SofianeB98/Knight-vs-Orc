#pragma once

#include "Stat.h"
#include "Status.h"

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
	// Base Stats of every Character
	Stat life;
	Stat damageMultiplier;
	
#pragma region Constructor
	/// <summary>
	/// Default constructor of Character class
	/// </summary>
	Character();

	Character(Weapon& _w, Ability& _a);
	
	/// <summary>
	/// Copy constructor of Character Class
	/// </summary>
	/// <param name="_c"></param>
	Character(const Character& _c);
#pragma endregion 

	virtual ~Character();

#pragma region Character Method
	/// <summary>
	/// Call this method to try to use character ability on the specific target
	/// </summary>
	/// <param name="_target"></param>
	virtual void UseAbility(Character& _target);

	/// <summary>
	/// Call this method to use character weapon on the specific target
	/// </summary>
	/// <param name="_target"></param>
	virtual void UseWeapon(Character& _target);

	// Call by Use Ability, but make this method public because
	// we can imagine in a futur update, other object can apply a status
	/// <summary>
	/// This method apply a specific Status on this character
	/// </summary>
	/// <param name="_s"></param>
	virtual void ApplyStatus(Status* _s);

	/// <summary>
	/// THis method Process all status for the specific type
	/// </summary>
	/// <param name="_statusType"></param>
	virtual void ProcessStatus(StatusType _statusType);
#pragma endregion 

#pragma region Getter
	virtual bool IsAlive() = 0;
	bool IsAbilityAvailable() const;
#pragma endregion 
	
	/// <summary>
	/// Call when a turn finish
	/// Update all modifiers, cooldown and durability of every fields
	/// </summary>
	virtual void UpdateCharacterFields();
	
protected:	
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
	/// <param name="_c"></param>
	void swap(Character& _c);
private:

	/// <summary>
	/// Remove and destroy all status
	/// </summary>
	void ClearStatus();
};
