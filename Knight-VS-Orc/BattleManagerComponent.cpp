#include "BattleManagerComponent.h"

#include <iostream>
#include <Windows.h>

#include "Game.h"
#include "GameObject.h"
#include "IACharacterComponent.h"
#include "KnightCharacter.h"

#include "OrcCharacter.h"

#include "PlayerCharacterComponent.h"


BattleManagerComponent::BattleManagerComponent() : Component()
{
	GameObject& p1 = Game::Get().CreateNewGameObject();
	this->readyPlayerOne = &p1.AddComponent<PlayerCharacterComponent>(new PlayerCharacterComponent(*this, *new KnightCharacter));

	GameObject& p2 = Game::Get().CreateNewGameObject();
	this->playerTwo = &p2.AddComponent<IACharacterComponent>(new IACharacterComponent(*this, *new OrcCharacter));

	this->battleState = BattleState::StartBattle;

	this->currentTurn = 0;
	this->currentTimer = 0.0;
}

BattleManagerComponent::~BattleManagerComponent()
{
	// Player are deleted from GameObject class
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
	if (this->readyPlayerOne == nullptr || this->playerTwo == nullptr)
	{
		return;
	}

	Character& p1 = this->readyPlayerOne->GetCharacter();
	Character& p2 = this->playerTwo->GetCharacter();

	this->currentTimer += _dt;

	switch (this->battleState)
	{
	case BattleState::StartBattle:
		std::cout << "Battle !" << std::endl;
		this->battleState = BattleState::BeginTurn;

		ResetTimerAndPrintedBool();
		break;



	case BattleState::BeginTurn:
		this->currentTurn++;

		// Clear console for the new turn
		system("CLS");
		PrintCharacterInformation(p1, p2, 0);

		std::cout << "Begin turn " << this->currentTurn << std::endl;

		// Process status
		p1.ProcessStatus(StatusType::BeginTurnProcess);
		p2.ProcessStatus(StatusType::BeginTurnProcess);

		ResetTimerAndPrintedBool();

		this->battleState = BattleState::AbilityChoice;
		break;

	case BattleState::AbilityChoice:
		// print
		if (!this->informationPrintedForCurrentState)
		{
			std::cout << "Do you want to use your Ability ? Y or N " << std::endl;
			this->informationPrintedForCurrentState = true;
		}

		if (this->readyPlayerOne->GetAbilityChoice() != AbilityChoiceState::InProgress &&
			this->playerTwo->GetAbilityChoice() != AbilityChoiceState::InProgress)
		{
			std::cout << "All player has done there choice !" << std::endl;
			this->battleState = BattleState::AbilityProcess;
			ResetTimerAndPrintedBool();
			break;
		}

		break;

	case BattleState::AbilityProcess:
		if (!this->informationPrintedForCurrentState)
		{
			std::cout << "Players process there Ability ! (If its there choice)" << std::endl;
			this->informationPrintedForCurrentState = true;

			if (this->readyPlayerOne->GetAbilityChoice() == AbilityChoiceState::UseIt)
				this->readyPlayerOne->UseAbility(*this->playerTwo);

			if (this->playerTwo->GetAbilityChoice() == AbilityChoiceState::UseIt)
				this->playerTwo->UseAbility(*this->readyPlayerOne);
		}


		if (this->currentTimer >= this->waitingTimeBeforeNextStep)
		{
			std::cout << "\n" << std::endl;

			PrintCharacterInformation(p1, p2, 20);
			ResetTimerAndPrintedBool();

			std::cout << "Take place for the FIGHT" << std::endl;
			this->battleState = BattleState::FightProcess;
		}


		break;

	case BattleState::FightProcess:

		if (this->currentTimer >= this->waitingTimeBeforeNextStep)
		{
			// Process status
			p1.ProcessStatus(StatusType::BeginBattleTurnProcess);
			p2.ProcessStatus(StatusType::BeginBattleTurnProcess);

			// Fight
			this->readyPlayerOne->UseWeapon(*this->playerTwo);
			this->playerTwo->UseWeapon(*this->readyPlayerOne);


			std::cout << "Fight finish" << std::endl;
			ResetTimerAndPrintedBool();
			this->battleState = BattleState::EndTurn;
		}
		break;

	case BattleState::EndTurn:
		// Process status
		p1.ProcessStatus(StatusType::EndTurnProcess);
		p2.ProcessStatus(StatusType::EndTurnProcess);

		// Update fields, ...
		p1.UpdateCharacterFields();
		p2.UpdateCharacterFields();

		ResetTimerAndPrintedBool();

		this->battleState = BattleState::CheckAlive;
		break;

	case BattleState::CheckAlive:
		if (!this->informationPrintedForCurrentState)
		{
			PrintCharacterInformation(p1, p2, 35);
		}

		if (this->currentTimer >= this->waitingTimeBeforeNextStep)
		{
			ResetTimerAndPrintedBool();
			this->battleState = p1.IsAlive() && p2.IsAlive() ? BattleState::BeginTurn : BattleState::EndBattle;
		}
		break;


	case BattleState::EndBattle:
		if (!this->informationPrintedForCurrentState)
		{
			std::cout << "Battle finish !" << std::endl;
			std::cout << (p1.IsAlive() ? "Ready Player One is the Winner !" : p2.IsAlive() ? "Player Two is the Winner !" : "All players is dead") << std::endl;

			std::cout << "\n\nPress Escape to quit the game." << std::endl;

			this->informationPrintedForCurrentState = true;
		}
		break;
	}


}

void BattleManagerComponent::OnDisable(GameObject& _gameObject)
{
}

BattleState BattleManagerComponent::GetBattleState() const
{
	return this->battleState;
}

void BattleManagerComponent::PrintCharacterInformation(Character& c1, Character& c2, int yOffset)
{
	COORD coord;
	coord.X = 0;
	coord.Y = yOffset;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	std::cout << c1.GetCharacterInformation() << std::endl;

	std::string s = c2.GetCharacterInformation();
	std::string delimiter = "\n";

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		coord.X = 30;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

		token = s.substr(0, pos);
		std::cout << token << std::endl;
		s.erase(0, pos + delimiter.length());

		coord.Y += 1;
	}

	coord.X = 0;
	coord.Y = yOffset + 8;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void BattleManagerComponent::ResetTimerAndPrintedBool()
{
	this->informationPrintedForCurrentState = false;
	this->currentTimer = 0.0;
}
