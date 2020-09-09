#pragma once
#include "EntityStates/ESIdle.h"
#include "Constant.h"
#include "Player.h"
class PSIdle : public ESIdle
{
public:

	PSIdle();
	~PSIdle();

	virtual void Init() override;
	virtual void Exit() override;

	virtual void HandleEvents() override;
	virtual void Update(float deltaTime) override;

};