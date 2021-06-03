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
};
