#pragma once
#include "Status.h"

class StunedStatus : public Status
{
public:
#pragma region Constructor
	/// <summary>
	/// Create default stuned status with durability = 1 and type = battle turn
	/// </summary>
	StunedStatus();

	/// <summary>
	/// Create stuned status with specific durabilty
	/// type = begin turn
	/// </summary>
	/// <param name="_durability"></param>
	StunedStatus(int _durability);

	/// <summary>
	/// Create stuned status with specific durability and type
	/// </summary>
	/// <param name="_durability"></param>
	/// <param name="_statusType"></param>
	StunedStatus(int _durability, StatusType _statusType);

	/// <summary>
	/// Copy the parameter
	/// </summary>
	/// <param name="_s"></param>
	StunedStatus(const StunedStatus& _s);

	/// <summary>
	/// = Operator
	/// </summary>
	/// <param name="_s"></param>
	/// <returns></returns>
	StunedStatus& operator=(StunedStatus _s);
#pragma endregion
	
	/// <summary>
	/// Trying process this status into specific character
	/// Status process if this type == processing type
	/// </summary>
	/// <param name="_c"></param>
	/// <param name="_processingType"></param>
	virtual void ProcessStatus(Character& _c, StatusType _processingType) override;
};
