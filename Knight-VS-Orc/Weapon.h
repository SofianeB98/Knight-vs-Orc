#pragma once
#include "Stat.h"

class Weapon
{
public:
#pragma region Constructor
	/// <summary>
	/// Default construtor of Weapon, create a weapon with damage as 1
	/// </summary>
	Weapon();

	/// <summary>
	/// Create a weapon with the specific damage value
	/// </summary>
	/// <param name="damage"></param>
	Weapon(float _damage);

	/// <summary>
	/// Copy constructor of Weapon Class
	/// </summary>
	/// <param name="w"></param>
	Weapon(const Weapon& _w);

	/// <summary>
	/// = operator of wepaon class
	/// </summary>
	/// <param name="w"></param>
	/// <returns></returns>
	Weapon& operator=(Weapon _w);
#pragma endregion

	virtual ~Weapon() = default;

	/// <summary>
	/// Return the weapon damage with applied modifier
	/// </summary>
	/// <returns></returns>
	virtual float GetDamage();
	
protected:
	// Store the weapon damage
	Stat damage;

	// Copy & Swap, this method is used by "= operator"
	/// <summary>
	/// Swap this class field with parameter value
	/// </summary>
	/// <param name="w"></param>
	virtual void swap(Weapon& _w);
private:
	
};
