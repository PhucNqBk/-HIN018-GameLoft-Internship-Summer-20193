#pragma once
#include "EntityStateBase.h"
#include "GameObject/Entity.h"
class ESAttack : public EntityStateBase
{
public:
	ESAttack();
	~ESAttack();

	virtual void Init() override;
	virtual void Exit() override;

	virtual void HandleEvents() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
};