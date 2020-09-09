#pragma once
#include "EntityStates/ESWalk.h"
#include "Constant.h"
class PSWalk : public ESWalk
{
public:
	PSWalk();
	~PSWalk();

	virtual void Init() override;
	virtual void Exit() override;

	virtual void HandleEvents() override;
	virtual void Update(float deltaTime) override;

};
