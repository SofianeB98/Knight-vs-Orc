#pragma once
#include "CharacterComponent.h"

class PlayerCharacterComponent : public CharacterComponent
{
public:
	PlayerCharacterComponent(BattleManagerComponent& _battleManager, Character& _character);

	virtual ~PlayerCharacterComponent() override;

	void OnEnable(GameObject& _gameObject) override;
	void Start(GameObject& _gameObject) override;
	void Update(GameObject& _gameObject, double _dt) override;
	void OnDisable(GameObject& _gameObject) override;
};
