#include "IACharacterComponent.h"


#include <conio.h>
#include <iostream>


#include "BattleManagerComponent.h"
#include "Character.h"

IACharacterComponent::IACharacterComponent(BattleManagerComponent& _battleManager, Character& _character) : CharacterComponent(_battleManager, _character)
{

}

IACharacterComponent::~IACharacterComponent()
{
}



void IACharacterComponent::OnEnable(GameObject& _gameObject)
{
}

void IACharacterComponent::Start(GameObject& _gameObject)
{
}

void IACharacterComponent::Update(GameObject& _gameObject, double _dt)
{
	// IA Component is simple :
	// If ability is available, return use it, else dont use it
	
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

		if(this->abilityChoiceState == AbilityChoiceState::InProgress)
			this->abilityChoiceState = AbilityChoiceState::UseIt;
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

void IACharacterComponent::OnDisable(GameObject& _gameObject)
{
}