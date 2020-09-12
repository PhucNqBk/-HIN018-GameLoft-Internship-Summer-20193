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
	virtual void ProcessAI(float x, float y, float deltatime) override;
	Direction		ValueFunction(float px, float py,float ex, float ey);
private:
	float m_Duration;
	float m_WaitTimer;
	float m_Range;
};