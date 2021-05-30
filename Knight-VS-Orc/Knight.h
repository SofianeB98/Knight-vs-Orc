#pragma once
#include "Character.h"

class Knight : public Character
{
public:
#pragma region Constructor
	/// <summary>
	/// Default knight constructor
	/// Life = 20, shield = 50
	/// </summary>
	Knight();

	/// <summary>
	/// Create a knight like it's default constructor with
	/// specific ability and weapon
	/// </summary>
	/// <param name="_w"></param>
	/// <param name="_a"></param>
	Knight(Weapon& _w, Ability& _a);

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="_k"></param>
	Knight(const Knight& _k);

	/// <summary>
	/// = operator of this class
	/// </summary>
	/// <param name="_k"></param>
	/// <returns></returns>
	Knight& operator=(Knight _k);
#pragma endregion

	/// <summary>
	/// Override UpdateCharacterFields.
	/// When update fields, we've to update shield field
	/// </summary>
	virtual void UpdateCharacterFields() override;
	
protected:
	Stat shield;

	/// <summary>
	/// When knight take damage, his shield take first and then
	/// his life
	/// </summary>
	/// <param name="_damage"></param>
	virtual void TakeDamage(float _damage) override;

	// Copy & Swap, this method is used by "= operator"
	/// <summary>
	/// Swap this class field with parameter value
	/// </summary>
	/// <param name="_c=k"></param>
	void swap(Knight& _k);
	
private:
};
