#pragma once
#include "GameConfig.h"
#include <map>
class Entity;
class EntityStateBase;
enum EntityStateType {
	IDLE = 0,
	WALK, 
	SWORD,
	ATTACK
};

class EntityStateMachine
{
public:
	EntityStateMachine(int eType = 0);
	~EntityStateMachine();
	void		Init();
	void		Update(GLfloat deltaTime);
	void		ChangeState(std::shared_ptr<EntityStateBase> state);
	void		ChangeState(EntityStateType type);
	void		CleanUp();
	void		SetEntity(std::shared_ptr<Entity> e);
	void		ProcessAI(float x, float y, float deltatime);
private:
	std::map<EntityStateType,std::shared_ptr<EntityStateBase> > m_EStates;
	std::shared_ptr<EntityStateBase> m_CurrentEState;

};