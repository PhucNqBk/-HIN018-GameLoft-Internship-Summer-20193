#pragma once
#include "EntityStateMachine.h"
#include "GameManager/ResourceManagers.h"
#include "Entity.h"

class EntityStateBase
{
public:
	EntityStateBase(){}
	virtual ~EntityStateBase(){}

	virtual void Init(){}
	virtual void Exit(){}

	virtual void Pause(){}
	virtual void Resume(){}

	virtual void HandleEvents(){}
	virtual void Update(float deltaTime){}
	virtual void Draw(){}

	void SetEntity(std::shared_ptr<Entity> e);
	std::shared_ptr<Entity> GetEnitity();
protected:
	std::shared_ptr<Entity>m_Entity;
};