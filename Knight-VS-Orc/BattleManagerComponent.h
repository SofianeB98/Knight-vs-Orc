#pragma once
#include "Component.h"

enum BattleState
{
	StartBattle,

	BeginTurn,
	
	AbilityChoice,
	AbilityProcess,
	FightProcess,
	CheckAlive,

	EndTurn,
	
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
	void PrintCharacterInformation(Character& c1, Character& c2, int yOffset);

	/// <summary>
	/// Call when change the battle state to reset "Waiting time" + Printed bool
	/// </summary>
	void ResetTimerAndPrintedBool();
};
