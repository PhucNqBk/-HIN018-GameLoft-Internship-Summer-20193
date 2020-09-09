#include "EntityStateMachine.h"

#include "ESIdle.h"
#include "ESWalk.h"
#include "ESAttack.h"
#include "PlayerStates/PSIdle.h"
#include "PlayerStates/PSWalk.h"
#include "PlayerStates/PSSword.h"

EntityStateMachine::EntityStateMachine(int eType)
{
	if (eType == 0)
	{
		m_EStates[IDLE] = std::make_shared<PSIdle>();
		m_EStates[WALK] = std::make_shared<PSWalk>();
		m_EStates[SWORD] = std::make_shared<PSSword>();
	}
	else
	{
		m_EStates[IDLE] = std::make_shared<ESIdle>();
		m_EStates[WALK] = std::make_shared<ESWalk>();
		m_EStates[ATTACK] = std::make_shared<ESAttack>();
	}
}
EntityStateMachine::~EntityStateMachine()
{

}
void EntityStateMachine::Init()
{

}
void EntityStateMachine::Update(GLfloat deltaTime)
{
	m_CurrentEState->Update(deltaTime);
}
void EntityStateMachine::ChangeState(std::shared_ptr<EntityStateBase> state)
{

}
void EntityStateMachine::ChangeState(EntityStateType type)
{
	m_CurrentEState = m_EStates[type];
	m_CurrentEState->Init();
}
void EntityStateMachine::CleanUp()
{

}
void EntityStateMachine::SetEntity(std::shared_ptr<Entity> e)
{
	std::map<EntityStateType, std::shared_ptr<EntityStateBase> >::iterator it;

	for (it = m_EStates.begin(); it != m_EStates.end(); it++)
	{
		it->second->SetEntity(e);
	}
}