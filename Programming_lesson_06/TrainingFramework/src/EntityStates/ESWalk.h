#pragma once
#include "EntityStateBase.h"
#include "Entity.h"
class ESWalk : public EntityStateBase
{
public:
	ESWalk();
	~ESWalk();

	virtual void Init() override;
	virtual void Exit() override;

	virtual void HandleEvents() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

};