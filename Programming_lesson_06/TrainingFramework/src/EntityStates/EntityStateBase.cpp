#include "EntityStateBase.h"

void EntityStateBase::SetEntity(std::shared_ptr<Entity> e)
{
	m_Entity = e;
}
std::shared_ptr<Entity> EntityStateBase::GetEnitity()
{
	return m_Entity;
}
void EntityStateBase::ProcessAI(float x, float y, float deltatime)
{

}
