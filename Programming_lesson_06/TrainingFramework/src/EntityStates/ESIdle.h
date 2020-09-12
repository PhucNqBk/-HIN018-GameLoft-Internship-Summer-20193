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

	virtual void ProcessAI(float x, float y, float deltatime) override;

private:
	float m_Duration;
	float m_WaitTimer;
};