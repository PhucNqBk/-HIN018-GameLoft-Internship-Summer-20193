#pragma once
#include "EntityStateBase.h"
#include "GameObject/Entity.h"
class ESIdle : public EntityStateBase
{
public:
	ESIdle();
	~ESIdle();

	virtual void Init() override;
	virtual void Exit() override;

	virtual void HandleEvents() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

};