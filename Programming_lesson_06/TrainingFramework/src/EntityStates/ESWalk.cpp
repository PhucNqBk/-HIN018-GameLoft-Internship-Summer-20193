#include "ESWalk.h"

ESWalk::ESWalk()
{

}
ESWalk::~ESWalk()
{

}

void ESWalk::Init()
{
	m_Entity->ChangeAnimation("walk-" + m_Entity->GetDirection());
}
void ESWalk::Exit()
{

}

void ESWalk::HandleEvents()
{

}
void ESWalk::Update(float deltaTime)
{

}
void ESWalk::Draw()
{

}