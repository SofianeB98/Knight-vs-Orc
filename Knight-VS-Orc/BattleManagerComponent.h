#pragma once
#include "Component.h"

enum BattleState
{
	StartBattle, // When a battle start, this is the first state which is triggered

	BeginTurn, // Each time we perform a new turn and process specific status
	
	AbilityChoice, // When players can choice if they want to use these ability
	AbilityProcess, // Next to ability choice, use (if its possible) the ability
	FightProcess, // Process specific status and apply some damage to other player
	CheckAlive, // Before ending the turn, we check if all players are alive

	EndTurn, // if true, we end the turn, process specific status and next start a new turn
	
	EndBattle
};


class CharacterComponent;
class Character;
class BattleManagerComponent : public Component
{
public:
#pragma region Constructor
	BattleManagerComponent();
#pragma endregion 

	virtual ~BattleManagerComponent();
	
#pragma region Component Callback
	void OnEnable(GameObject& _gameObject) override;
	void Start(GameObject& _gameObject) override;
	void Update(GameObject& _gameObject, double _dt) override;
	void OnDisable(GameObject& _gameObject) override;
#pragma endregion

#pragma region Getter
	BattleState GetBattleState() const;
#pragma endregion 
	
private:
	BattleState battleState;

	CharacterComponent* readyPlayerOne;
	CharacterComponent* playerTwo;

	int currentTurn;

	// To simulate a wait
	double currentTimer;
	double waitingTimeBeforeNextStep = 3.0;

	// Used to display only one time the state text
	bool informationPrintedForCurrentState = false;

	/// <summary>
	/// Display character stat, weapon and ability informations
	/// </summary>
	/// <param name="c1"></param>
	/// <param name="c2"></param>
	/// <param name="yOffset">to move the console cursor at the right pos</param>
	void PrintCharacterInformation(Character& c1, Character& c2, int yOffset) const;

	/// <summary>
	/// Call when change the battle state to reset "Waiting time" + Printed bool
	/// </summary>
	void ResetTimerAndPrintedBool();
};
