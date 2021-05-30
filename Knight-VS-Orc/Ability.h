#pragma once

class Character;

/// <summary>
/// Ability class is the base class for all ability
/// </summary>
class Ability
{
public:
#pragma region Constructor
	/// <summary>
	/// Base constructor for ability
	/// Initialise cooldown to 1 and success percent to 50
	/// </summary>
	Ability();

	/// <summary>
	/// Create ability with specific cooldown, percent is set to 50
	/// </summary>
	/// <param name="_abilityCooldown"></param>
	Ability(unsigned int _abilityCooldown);

	/// <summary>
	/// Create ability with specific coold down and success percent
	/// </summary>
	/// <param name="_abilityCooldown"></param>
	/// <param name="_abilitySuccessPercent"></param>
	Ability(unsigned int _abilityCooldown, float _abilitySuccessPercent);

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="a"></param>
	Ability(const Ability& a);

	/// <summary>
	/// = operator
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	Ability& operator=(Ability a);
#pragma endregion

	virtual ~Ability() = default;
	
#pragma region Getter
	/// <summary>
	/// Return true if actual cooldown == 0
	/// </summary>
	/// <returns></returns>
	bool IsAvailable() const;

	/// <summary>
	/// Return the "dafautl" ability cooldown
	/// </summary>
	/// <returns></returns>
	unsigned int GetAbilityCooldown() const;

	/// <summary>
	/// Return actual ability cooldown
	/// </summary>
	/// <returns></returns>
	unsigned int GetActualCooldown() const;
#pragma endregion 

#pragma region Cooldown Method
	/// <summary>
	/// Update ability cooldown after a turn for example
	/// </summary>
	virtual void UpdateCooldown();

	/// <summary>
	/// Reduce the ability by the reduce count
	/// </summary>
	/// <param name="reduceCount"></param>
	virtual void ReduceCooldown(unsigned int reduceCount);

	/// <summary>
	/// Reset the cooldown to ability cooldown
	/// </summary>
	virtual void ResetCooldown();
#pragma endregion

	/// <summary>
	/// Trigger this ability to the specific character
	/// </summary>
	/// <param name="c"></param>
	virtual void Launch(Character& c);
	
protected:
	unsigned int abilityCooldown;
	unsigned int actualCooldown;

	float abilitySuccessPercent;

	// Copy & Swap, this method is used by "= operator"
	/// <summary>
	/// Swap this class field with parameter value
	/// </summary>
	/// <param name="a"></param>
	virtual void swap(Ability& a);
	
private:
	
};
