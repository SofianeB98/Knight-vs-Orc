#pragma once
#include "Character.h"

class OrcCharacter : public Character
{
public:
#pragma region Constructor
	/// <summary>
	/// Default Orc constructor
	/// Life = 60
	/// </summary>
	OrcCharacter();

	/// <summary>
	/// Create a Orc like it's default constructor with
	/// specific ability and weapon
	/// </summary>
	/// <param name="_w"></param>
	/// <param name="_a"></param>
	OrcCharacter(Weapon& _w, Ability& _a);

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="_c"></param>
	OrcCharacter(const OrcCharacter& _c);

	/// <summary>
	/// = operator of this class
	/// </summary>
	/// <param name="_c"></param>
	/// <returns></returns>
	OrcCharacter& operator=(OrcCharacter _c);
	
	bool IsAlive() override;
#pragma endregion

	
};
