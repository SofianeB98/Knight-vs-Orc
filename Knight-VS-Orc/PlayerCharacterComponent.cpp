#include "PlayerCharacterComponent.h"


#include <conio.h>
#include <iostream>
#include <Windows.h>



#include "BattleManagerComponent.h"
#include "Character.h"

PlayerCharacterComponent::PlayerCharacterComponent(BattleManagerComponent& _battleManager, Character& _character) : CharacterComponent(_battleManager, _character)
{
	
}

PlayerCharacterComponent::~PlayerCharacterComponent()
{
}



void PlayerCharacterComponent::OnEnable(GameObject& _gameObject)
{
}

void PlayerCharacterComponent::Start(GameObject& _gameObject)
{
}

void PlayerCharacterComponent::Update(GameObject& _gameObject, double _dt)
{
	switch (this->battleManager.GetBattleState())
	{
	case BattleState::StartBattle:
		break;

	case BattleState::BeginTurn:
		this->abilityChoiceState = AbilityChoiceState::InProgress;
		break;

	case BattleState::AbilityChoice:
		// If player ability is available
		// He can choice if he wants to use it or not
		if (!this->character->IsAbilityAvailable())
		{
			this->abilityChoiceState = AbilityChoiceState::DontUseIt;
			break;
		}

		if(this->abilityChoiceState == AbilityChoiceState::InProgress)
			this->abilityChoiceState = WantToUseAbility();
		break;

	case BattleState::AbilityProcess:
		break;

	case BattleState::FightProcess:
		break;

	case BattleState::EndTurn:
		this->abilityChoiceState = AbilityChoiceState::InProgress;
		break;

	case BattleState::CheckAlive:
		break;


	case BattleState::EndBattle:
		break;
	}
}

void PlayerCharacterComponent::OnDisable(GameObject& _gameObject)
{
}

AbilityChoiceState PlayerCharacterComponent::WantToUseAbility() const
{
	if(GetAsyncKeyState(0x59)) // = Y
		return AbilityChoiceState::UseIt;
	else if (GetAsyncKeyState(0x4E)) // = N
		return AbilityChoiceState::DontUseIt;

	return AbilityChoiceState::InProgress;
}
