#include "StunnedStatus.h"

#include <iostream>

#include "Character.h"

StunnedStatus::StunnedStatus() : Status(1, StatusType::BeginBattleTurnProcess)
{
}

StunnedStatus::StunnedStatus(int _durability) : Status(_durability, StatusType::BeginBattleTurnProcess)
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



void StunnedStatus::ProcessStatus(Character& _c, StatusType _processingType) const
{
	// If processing tyoe isn't this status type, break
	if (this->statusType != _processingType)
		return;
	
	// Apply status effect
	std::cout << "You're stunned, you can't apply any damage." << std::endl;
	_c.damageMultiplier.AddModifier({ StatModifierType::Multiplier, 0, 1000, 1 });
}
