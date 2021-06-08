#include "CharacterComponent.h"
#include "Character.h"

#include "BattleManagerComponent.h"

CharacterComponent::CharacterComponent(BattleManagerComponent& _battleManager, Character& _character) : battleManager(_battleManager), character(&_character), abilityChoiceState(AbilityChoiceState::InProgress)
{
	//this->battleManager = _battleManager;
}



CharacterComponent::~CharacterComponent()
{
	if(this->character != nullptr)
	{
		delete this->character;
		this->character = nullptr;
	}
}



void CharacterComponent::UseAbility(CharacterComponent& _otherCharacter) const
{
	this->character->UseAbility(_otherCharacter.GetCharacter());
}

void CharacterComponent::UseWeapon(CharacterComponent& _otherCharacter) const
{
	this->character->UseWeapon(_otherCharacter.GetCharacter());
}



Character& CharacterComponent::GetCharacter() const
{
	return *this->character;
}

AbilityChoiceState CharacterComponent::GetAbilityChoice() const
{
	return this->abilityChoiceState;
}