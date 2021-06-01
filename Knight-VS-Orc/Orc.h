#pragma once
#include "Character.h"

class Orc : public Character
{
public:
#pragma region Constructor
	/// <summary>
	/// Default Orc constructor
	/// Life = 60
	/// </summary>
	Orc();

	/// <summary>
	/// Create a Orc like it's default constructor with
	/// specific ability and weapon
	/// </summary>
	/// <param name="_w"></param>
	/// <param name="_a"></param>
	Orc(Weapon& _w, Ability& _a);

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="_c"></param>
	Orc(const Orc& _c);

	/// <summary>
	/// = operator of this class
	/// </summary>
	/// <param name="_c"></param>
	/// <returns></returns>
	Orc& operator=(Orc _c);
#pragma endregion

	
};
