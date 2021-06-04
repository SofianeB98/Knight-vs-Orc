#include "PlayerCharacterComponent.h"


#include <conio.h>
#include <iostream>


#include "BattleManagerComponent.h"

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
		if (_kbhit())
		{
			const int ch = _getch();
			if (ch == 89 || ch == 121) // = Y/y
			{
				this->abilityChoiceState = AbilityChoiceState::UseIt;
			}
			else if (ch == 78 || ch == 110) // = N/n
			{
				this->abilityChoiceState = AbilityChoiceState::DontUseIt;
			}
		}
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