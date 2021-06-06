#include "PlayerCharacterComponent.h"


#include <conio.h>
#include <iostream>


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
		if (!this->character->IsAbilityAvailable())
		{
			this->abilityChoiceState = AbilityChoiceState::DontUseIt;
			break;
		}
		GetChosenAbility();
		break;

	case BattleState::AbilityProcess:
		this->pressedInput = -1;
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

void PlayerCharacterComponent::GetChosenAbility()
{
	//if (_kbhit())
	{
		this->pressedInput = _getch();
		//std::cout << ch << " as int : " << (int)ch << std::endl;
		if (this->pressedInput == 89 || this->pressedInput == 121) // = Y/y
		{
			this->abilityChoiceState = AbilityChoiceState::UseIt;
		}
		else if (this->pressedInput == 78 || this->pressedInput == 110) // = N/n
		{
			this->abilityChoiceState = AbilityChoiceState::DontUseIt;
		}
	}
}
