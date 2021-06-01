#include "StunnedStatus.h"

#include <iostream>

#include "Character.h"

StunnedStatus::StunnedStatus() : Status(1, StatusType::BeginBattleTurn)
{
}

StunnedStatus::StunnedStatus(int _durability) : Status(_durability, StatusType::BeginBattleTurn)
{
}

StunnedStatus::StunnedStatus(int _durability, StatusType _statusType) : Status(_durability, _statusType)
{
}

StunnedStatus::StunnedStatus(const StunnedStatus& _s) : Status(_s)
{
}

StunnedStatus& StunnedStatus::operator=(StunnedStatus _s)
{
	Status::swap(_s);
	return *this;
}



void StunnedStatus::ProcessStatus(Character& _c, StatusType _processingType)
{
	// Call the base method who check if this status type equals the processing type
	Status::ProcessStatus(_c, _processingType);

	// Apply status effect
	std::cout << "You're stunned, you can't apply any damage." << std::endl;
	_c.damageMultiplier.AddModifier({ StatModifierType::Multiplier, 0, 1000, 1 });
}
