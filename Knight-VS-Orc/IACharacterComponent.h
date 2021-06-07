#pragma once
#include "CharacterComponent.h"

class IACharacterComponent : public CharacterComponent
{
public:
	IACharacterComponent(BattleManagerComponent& _battleManager, Character& _character);

	virtual ~IACharacterComponent() override;

	void OnEnable(GameObject& _gameObject) override;
	void Start(GameObject& _gameObject) override;
	void Update(GameObject& _gameObject, double _dt) override;
	void OnDisable(GameObject& _gameObject) override;
	
};
