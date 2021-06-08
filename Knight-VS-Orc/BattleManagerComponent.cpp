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
	// When battle manager is created
	// We create 2 players :
	// Player 1 is a real Player with Knight class
	// Player 2 is a simple IA with Orc Class
	
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

	// Get Characters to handle method on it
	Character& p1 = this->readyPlayerOne->GetCharacter();
	Character& p2 = this->playerTwo->GetCharacter();

	// Increment current timer
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
		// Print character information
		PrintCharacterInformation(p1, p2, 0);

		std::cout << "Begin turn " << this->currentTurn << std::endl;

		// Process status with Begin turn type
		p1.ProcessStatus(StatusType::BeginTurnProcess);
		p2.ProcessStatus(StatusType::BeginTurnProcess);

		// Reset timer and printed bool to the next state
		ResetTimerAndPrintedBool();

		// switch state
		this->battleState = BattleState::AbilityChoice;
		break;

	case BattleState::AbilityChoice:
		// print information for this state
		if (!this->informationPrintedForCurrentState)
		{
			std::cout << "Do you want to use your Ability ? Y or N " << std::endl;
			this->informationPrintedForCurrentState = true;
		}

		// If all players are done there choice, go to the next state
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

			// Process Player 1 first, and next Player 2 ability (if ability state == Use it)
			if (this->readyPlayerOne->GetAbilityChoice() == AbilityChoiceState::UseIt)
				this->readyPlayerOne->UseAbility(*this->playerTwo);

			if (this->playerTwo->GetAbilityChoice() == AbilityChoiceState::UseIt)
				this->playerTwo->UseAbility(*this->readyPlayerOne);
		}

		// after a little waiting time, switch to next state
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
		// We simulate a small animation delay before appliying
		// Status Battle type + applying damage Player1 first then Player 2
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
		// Process status with end turn type
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

		// Wait a smal delay
		if (this->currentTimer >= this->waitingTimeBeforeNextStep)
		{
			// if player 1  and player 2 is alive, continue the battle, else end the battle 
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

void BattleManagerComponent::PrintCharacterInformation(Character& c1, Character& c2, int yOffset) const
{
	// Display character information at the right position in the console
	COORD coord;
	coord.X = 0;
	coord.Y = yOffset;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	// Player 1 information juste need an Y offset before displaying
	std::cout << c1.GetCharacterInformation() << std::endl;

	// Player 2 need an adjustement in X and Y
	// We "split" the string by a delimiter, and each splitted value (= lines)
	// is displayed with an y offset
	std::string s = c2.GetCharacterInformation();
	std::string delimiter = "\n";

	size_t pos = 0;
	std::string token;
	coord.X = 30;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

		token = s.substr(0, pos);
		std::cout << token << std::endl;
		s.erase(0, pos + delimiter.length());

		coord.Y += 1;
	}

	// Finaly we move the cursor down of character's information
	coord.X = 0;
	coord.Y = yOffset + 8;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void BattleManagerComponent::ResetTimerAndPrintedBool()
{
	this->informationPrintedForCurrentState = false;
	this->currentTimer = 0.0;
}
