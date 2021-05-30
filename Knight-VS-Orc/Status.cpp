#include "Status.h"
#include "Character.h"

Status::Status() : statusType(StatusType::BeginTurn), statusDurability(1), actualDurability(1)
{
}

Status::Status(int _durability) : statusType(StatusType::BeginTurn), statusDurability(_durability), actualDurability(_durability)
{
}

Status::Status(int _durability, StatusType _statusType) : statusType(_statusType), statusDurability(_durability), actualDurability(_durability)
{
}

Status::Status(const Status& _s) : statusType(_s.statusType), statusDurability(_s.statusDurability), actualDurability(_s.actualDurability)
{
}

Status& Status::operator=(Status _s)
{
	swap(_s);
	return *this;
}

void Status::swap(Status& _s)
{
	std::swap(this->statusDurability, _s.statusDurability);
	std::swap(this->actualDurability, _s.actualDurability);
	std::swap(this->statusType, _s.statusType);
}



bool Status::IsTakingEffect() const
{
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


void Status::ProcessStatus(Character& _c, StatusType _processingType)
{
	if (this->statusType != _processingType)
		return;
	
	//Do something
}

void Status::UpdateDurability()
{
	if (!this->IsTakingEffect())
		return;

	--this->actualDurability;
}

void Status::ReduceDurability(int _reduceCount)
{
	if (_reduceCount > this->actualDurability)
		_reduceCount = this->actualDurability;

	this->actualDurability -= _reduceCount;
}

void Status::ResetDurability()
{
	this->actualDurability = this->statusDurability;
}
