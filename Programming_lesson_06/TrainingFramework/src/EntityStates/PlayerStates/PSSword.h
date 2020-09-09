#pragma once
#include "EntityStates/ESAttack.h"

class PSSword : public ESAttack
{
public :
	PSSword();
	~PSSword();

	virtual void Init() override;
	virtual void Exit() override;

	virtual void HandleEvents() override;
	virtual void Update(float deltaTime) override;

private:
	float m_CurrentTime;
	float m_Time;
};