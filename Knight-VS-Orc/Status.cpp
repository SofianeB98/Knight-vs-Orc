#include "Status.h"
#include "Character.h"
#include "Utils.h"

Status::Status() : statusType(StatusType::BeginTurnProcess), statusDurability(1), actualDurability(1)
{
}

Status::Status(int _durability) : statusType(StatusType::BeginTurnProcess), statusDurability(_durability), actualDurability(_durability)
{
}

Status::Status(int _durability, StatusType _statusType) : statusType(_statusType), statusDurability(_durability), actualDurability(_durability)
{
}

Status::Status(const Status& _s) : statusType(_s.statusType), statusDurability(_s.statusDurability), actualDurability(_s.actualDurability)
{
}


void Status::swap(Status& _s)
{
	std::swap(this->statusDurability, _s.statusDurability);
	std::swap(this->actualDurability, _s.actualDurability);
	std::swap(this->statusType, _s.statusType);
}



bool Status::IsTakingEffect() const
{
	// Return true if the actual durability is greater than 0
	// That mean this status is active / enable
	return this->actualDurability > 0;
}

int Status::GetStatusDurability() const
{
	return this->statusDurability;
}

int Status::GetActualDurability() const
{
	return this->actualDurability;
}


void Status::UpdateDurability()
{
	if (!this->IsTakingEffect())
		return;

	--this->actualDurability;
}

void Status::ReduceDurability(int _reduceCount)
{
	this->actualDurability -= Utils::Clamp(_reduceCount, 0, this->actualDurability);
}

void Status::ResetDurability()
{
	this->actualDurability = this->statusDurability;
}
