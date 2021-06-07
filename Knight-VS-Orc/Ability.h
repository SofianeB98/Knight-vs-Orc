#pragma once

class Character;

/// <summary>
/// Ability class is the base class for all ability
/// To create a new ability, just create a class which inherit from this and override Constructor and Launch method
/// To have a base ability
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
	Ability(const Ability& _a);

	/// <summary>
	/// = operator
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	//Ability& operator=(Ability _a);
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
	/// <param name="_reduceCount"></param>
	virtual void ReduceCooldown(unsigned int _reduceCount);

	/// <summary>
	/// Reset the cooldown to ability cooldown
	/// </summary>
	virtual void ResetCooldown();
#pragma endregion

	/// <summary>
	/// Trigger this ability to the specific character
	/// </summary>
	/// <param name="_c"></param>
	virtual void Launch(Character& _abilityOwner, Character& _abilityTarget) = 0;
	
protected:
	unsigned int abilityCooldown;
	unsigned int actualCooldown;

	float abilitySuccessPercent;

	// Copy & Swap, this method is used by "= operator"
	/// <summary>
	/// Swap this class field with parameter value
	/// </summary>
	/// <param name="_a"></param>
	void swap(Ability& _a);

	/// <summary>
	/// Return true if :
	/// -> Ability is available
	/// -> And if the random wheel return a good value
	/// </summary>
	/// <returns></returns>
	bool CanLaunchAbility();
	
private:
	
};
