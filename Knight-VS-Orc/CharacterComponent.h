#pragma once
#include "Component.h"

enum AbilityChoiceState
{
	InProgress = -1,
	DontUseIt = 0,
	UseIt = 1
};

class Character;
class BattleManagerComponent;
class CharacterComponent : public Component
{
public:
#pragma region Constructor
	CharacterComponent(BattleManagerComponent& _battleManager, Character& _character);
#pragma endregion 

	virtual ~CharacterComponent();
	
#pragma region Component Callback
	virtual void OnEnable(GameObject& _gameObject) override = 0;
	virtual void Start(GameObject& _gameObject) override = 0;
	virtual void Update(GameObject& _gameObject, double _dt) override = 0;
	virtual void OnDisable(GameObject& _gameObject) override = 0;
#pragma endregion 

#pragma region Character Callback
	void UseAbility(CharacterComponent& _otherCharacter) const;
	void UseWeapon(CharacterComponent& _otherCharacter) const;
#pragma endregion 
	
#pragma region Getter
	Character& GetCharacter() const;
	AbilityChoiceState GetAbilityChoice() const;
#pragma endregion 
	
protected:
	BattleManagerComponent& battleManager;
	
	Character* character;

	AbilityChoiceState abilityChoiceState;
};
