#include "StunedStatus.h"

StunedStatus::StunedStatus() : Status(1, StatusType::BeginBattleTurn)
{
}

StunedStatus::StunedStatus(int _durability) : Status(_durability, StatusType::BeginBattleTurn)
{
}

StunedStatus::StunedStatus(int _durability, StatusType _statusType) : Status(_durability, _statusType)
{
}

StunedStatus::StunedStatus(const StunedStatus& _s) : Status(_s)
{
}

StunedStatus& StunedStatus::operator=(StunedStatus _s)
{
	Status::swap(_s);
	return *this;
}



void StunedStatus::ProcessStatus(Character& _c, StatusType _processingType)
{
	// Call the base method who check if this status type equals the processing type
	Status::ProcessStatus(_c, _processingType);

	// Apply status effect
}
