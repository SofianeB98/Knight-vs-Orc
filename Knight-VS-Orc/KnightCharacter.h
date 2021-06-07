#pragma once
#include "Character.h"

class KnightCharacter : public Character
{
public:
	Stat shield;
	
#pragma region Constructor
	/// <summary>
	/// Default knight constructor
	/// Life = 20, shield = 50
	/// </summary>
	KnightCharacter();

	/// <summary>
	/// Create a knight like it's default constructor with
	/// specific ability and weapon
	/// </summary>
	/// <param name="_w"></param>
	/// <param name="_a"></param>
	KnightCharacter(Weapon& _w, Ability& _a);

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="_k"></param>
	KnightCharacter(const KnightCharacter& _k);

	/// <summary>
	/// = operator of this class
	/// </summary>
	/// <param name="_k"></param>
	/// <returns></returns>
	KnightCharacter& operator=(KnightCharacter _k);
#pragma endregion

	/// <summary>
	/// Override UpdateCharacterFields.
	/// When update fields, we've to update shield field
	/// </summary>
	virtual void UpdateCharacterFields() override;
	
protected:


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
	void swap(KnightCharacter& _k);

public:
	bool IsAlive() override;
	std::string GetCharacterInformation() override;
private:
};
