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

Status::Status(const Status& s) : statusType(s.statusType), statusDurability(s.statusDurability), actualDurability(s.actualDurability)
{
}

Status& Status::operator=(Status s)
{
	swap(s);
	return *this;
}

void Status::swap(Status& s)
{
	std::swap(this->statusDurability, s.statusDurability);
	std::swap(this->actualDurability, s.actualDurability);
	std::swap(this->statusType, s.statusType);
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


void Status::ProcessStatus(Character& c, StatusType processingType)
{
	if (this->statusType != processingType)
		return;
	
	//Do something
}

void Status::UpdateDurability()
{
	if (!this->IsTakingEffect())
		return;

	--this->actualDurability;
}

void Status::ReduceDurability(int reduceCount)
{
	if (reduceCount > this->actualDurability)
		reduceCount = this->actualDurability;

	this->actualDurability -= reduceCount;
}

void Status::ResetDurability()
{
	this->actualDurability = this->statusDurability;
}
