#pragma once
#include "CharacterComponent.h"

class PlayerCharacterComponent : public CharacterComponent
{
public:
#pragma region Constructor
	PlayerCharacterComponent(BattleManagerComponent& _battleManager, Character& _character);
#pragma endregion
	
	virtual ~PlayerCharacterComponent() override;
	
#pragma region Component Callback
	void OnEnable(GameObject& _gameObject) override;
	void Start(GameObject& _gameObject) override;
	void Update(GameObject& _gameObject, double _dt) override;
	void OnDisable(GameObject& _gameObject) override;
#pragma endregion
	
protected:
	AbilityChoiceState WantToUseAbility() const;
};
