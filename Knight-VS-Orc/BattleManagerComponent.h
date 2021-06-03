#pragma once
#include "Component.h"

class BattleManagerComponent : public Component
{
public:
	void OnEnable(GameObject& _gameObject) override;
	void Start(GameObject& _gameObject) override;
	void Update(GameObject& _gameObject, double _dt) override;
	void OnDisable(GameObject& _gameObject) override;
};
