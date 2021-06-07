#pragma once

enum StatusType
{
	BeginTurnProcess, // Process at the beginning of a turn
	BeginBattleTurnProcess, // Process before the battle turn
	EndTurnProcess, // Process at the end of a turn
};

class Character;

/// <summary>
/// Base class for every status
/// To create new status, inherit from this class and override Constructor + ProcessStatus
/// </summary>
class Status
{
public:
#pragma region Constructor
	/// <summary>
	/// Create default status with durability = 1 and type = begin turn
	/// </summary>
	Status();

	/// <summary>
	/// Create status with specific durabilty
	/// type = begin turn
	/// </summary>
	/// <param name="_durability"></param>
	Status(int _durability);

	/// <summary>
	/// Create status with specific durability and type
	/// </summary>
	/// <param name="_durability"></param>
	/// <param name="_statusType"></param>
	Status(int _durability, StatusType _statusType);

	/// <summary>
	/// Copy the parameter
	/// </summary>
	/// <param name="_s"></param>
	Status(const Status& _s);
#pragma endregion 

	virtual ~Status() = default;

#pragma region Getter
	/// <summary>
	/// Return true if durability is greater than 0
	/// </summary>
	/// <returns></returns>
	bool IsTakingEffect() const;

	/// <summary>
	/// Return status durability
	/// </summary>
	/// <returns></returns>
	int GetStatusDurability() const;

	/// <summary>
	/// Return actual status durability
	/// </summary>
	/// <returns></returns>
	int GetActualDurability() const;
#pragma endregion 

	/// <summary>
	/// Trying process this status into specific character
	/// Status process if this type == processing type
	/// </summary>
	/// <param name="_c"></param>
	/// <param name="_processingType"></param>
	virtual void ProcessStatus(Character& _c, StatusType _processingType) = 0;
	
#pragma region Durability Method
	/// <summary>
	/// Reduce by 1 this actual durability
	/// </summary>
	virtual void UpdateDurability();

	/// <summary>
	/// Reduce by reduce count this actual durability
	/// </summary>
	/// <param name="_reduceCount"></param>
	virtual void ReduceDurability(int _reduceCount);

	/// <summary>
	/// Set actual durability to status durability
	/// </summary>
	virtual void ResetDurability();
#pragma endregion
	
protected:
	StatusType statusType;
	
	int statusDurability; // status durability is constant
	int actualDurability;
	
	// Copy & Swap, this method is used by "= operator"
	/// <summary>
	/// Swap this class field with parameter value
	/// </summary>
	/// <param name="_s"></param>
	void swap(Status& _s);
	
private:
};
