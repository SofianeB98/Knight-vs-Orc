#include "BattleManagerComponent.h"

#include <iostream>


#include "CharacterComponent.h"
#include "Character.h"
#include "Game.h"
#include "GameObject.h"

BattleManagerComponent::BattleManagerComponent()
{
	GameObject& p1 = Game::Get().CreateNewGameObject();

	
	GameObject& p2 = Game::Get().CreateNewGameObject();


	this->battleState = BattleState::StartBattle;
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
	if(this->readyPlayerOne == nullptr || this->playerTwo == nullptr)
	{
		return;
	}
	
	Character& p1 = this->readyPlayerOne->GetCharacter();
	Character& p2 = this->playerTwo->GetCharacter();
	
	switch (this->battleState)
	{
	case BattleState::StartBattle:
		std::cout << "Battle !" << std::endl;
		this->battleState = BattleState::BeginTurn;
		break;


		
	case BattleState::BeginTurn:
		// Process status
		p1.ProcessStatus(StatusType::BeginTurnProcess);
		p2.ProcessStatus(StatusType::BeginTurnProcess);
		
		break;
		
	case BattleState::AbilityChoice:
		if(this->readyPlayerOne->GetAbilityChoice() != AbilityChoiceState::InProgress ||
			this->playerTwo->GetAbilityChoice() != AbilityChoiceState::InProgress)
		{
			std::cout << "All player has done there choice !" << std::endl;
			this->battleState = BattleState::AbilityProcess;
			break;
		}
		
		// print
		
		break;
		
	case BattleState::AbilityProcess:
		std::cout << "Players process there Ability ! (If its there choice)" << std::endl;
		
		if (this->readyPlayerOne->GetAbilityChoice() == AbilityChoiceState::UseIt)
			this->readyPlayerOne->UseAbility(*this->playerTwo);

		if (this->playerTwo->GetAbilityChoice() == AbilityChoiceState::UseIt)
			this->playerTwo->UseAbility(*this->readyPlayerOne);

		std::cout << "Take place for the FIGHT" << std::endl;

		this->battleState = BattleState::FightProcess;
		
		break;
		
	case BattleState::FightProcess:
		// Process status
		p1.ProcessStatus(StatusType::BeginBattleTurnProcess);
		p2.ProcessStatus(StatusType::BeginBattleTurnProcess);

		
		// Fight
		this->readyPlayerOne->UseWeapon(*this->playerTwo);
		this->playerTwo->UseWeapon(*this->readyPlayerOne);

		this->battleState = BattleState::EndTurn;
		
		break;
		
	case BattleState::EndTurn:
		// Process status
		p1.ProcessStatus(StatusType::EndTurnProcess);
		p2.ProcessStatus(StatusType::EndTurnProcess);

		// Update fields, ...
		p1.UpdateCharacterFields();
		p2.UpdateCharacterFields();

		this->battleState = BattleState::CheckAlive;
		break;
		
	case BattleState::CheckAlive:

		this->battleState = p1.IsAlive() && p2.IsAlive() ? BattleState::BeginTurn : BattleState::EndBattle;
		break;

		
	case BattleState::EndBattle:
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
