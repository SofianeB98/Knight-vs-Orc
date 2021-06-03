#include "BattleManagerComponent.h"

#include <iostream>


#include "CharacterComponent.h"
#include "Game.h"
#include "GameObject.h"

BattleManagerComponent::BattleManagerComponent()
{
	GameObject& p1 = Game::Get().CreateNewGameObject();
	
}

BattleManagerComponent::~BattleManagerComponent()
{
	if (this->readyPlayerOne != nullptr)
	{
		delete this->readyPlayerOne;
		this->readyPlayerOne = nullptr;
	}

	if (this->playerTwo != nullptr)
	{
		delete this->playerTwo;
		this->playerTwo = nullptr;
	}
}

void BattleManagerComponent::OnEnable(GameObject& _gameObject)
{
}

void BattleManagerComponent::Start(GameObject& _gameObject)
{
	this->battleState = BattleState::StartBattle;
}

void BattleManagerComponent::Update(GameObject& _gameObject, double _dt)
{
	switch (this->battleState)
	{
	case StartBattle:
		std::cout << "Battle !" << std::endl;
		break;


		
	case BeginTurn:
		// process status
		break;
		
	case AbilityChoice:
		if(this->readyPlayerOne->GetAbilityChoice() != AbilityChoiceState::InProgress &&
			this->playerTwo->GetAbilityChoice() != AbilityChoiceState::InProgress)
		{
			std::cout << "All player has done there choice !" << std::endl;
			this->battleState = BattleState::AbilityProcess;
		}
		else
		{
			// print
		}
		break;
		
	case AbilityProcess:
		std::cout << "Players process there Ability ! (If its there choice)" << std::endl;
		
		if (this->readyPlayerOne->GetAbilityChoice() == AbilityChoiceState::UseIt)
			this->readyPlayerOne->UseAbility(*this->playerTwo);

		if (this->playerTwo->GetAbilityChoice() == AbilityChoiceState::UseIt)
			this->playerTwo->UseAbility(*this->readyPlayerOne);

		std::cout << "Take place for the FIGHT" << std::endl;

		this->battleState = BattleState::FightProcess;
		
		break;
		
	case FightProcess:
		// Process status

		// Fight
		this->readyPlayerOne->UseWeapon(*this->playerTwo);
		this->playerTwo->UseWeapon(*this->readyPlayerOne);
		
		break;
		
	case EndTurn:
		// Process status

		// Update fields, ...
		
		break;
		
	case CheckAlive:
		
		break;

		
	case EndBattle:
		std::cout << "Battle finish ! A player is dead" << std::endl;
		break;
		
	//default: ;
	}
}

void BattleManagerComponent::OnDisable(GameObject& _gameObject)
{
}

BattleState BattleManagerComponent::GetBattleState() const
{
	return this->battleState;
}
