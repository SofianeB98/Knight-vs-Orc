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

	double currentTimer;
	double waitingTimeBeforeNextStep = 3.0;

	bool informationPrintedForCurrentState = false;
	
	void PrintCharacterInformation(Character& c1, Character& c2, int yOffset);
	void ResetTimerAndPrintedBool();
};
