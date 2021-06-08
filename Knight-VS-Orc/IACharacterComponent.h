#pragma once
#include "CharacterComponent.h"

class IACharacterComponent : public CharacterComponent
{
public:
#pragma region Constructor
	IACharacterComponent(BattleManagerComponent& _battleManager, Character& _character);
#pragma endregion
	
	virtual ~IACharacterComponent() override;

#pragma region Component Callback
	void OnEnable(GameObject& _gameObject) override;
	void Start(GameObject& _gameObject) override;
	void Update(GameObject& _gameObject, double _dt) override;
	void OnDisable(GameObject& _gameObject) override;
#pragma endregion 
};
