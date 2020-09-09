#pragma once
#include "Animation.h"
#include "EntityStates/EntityStateMachine.h"
#include <map>
#include <string>
#include "Constant.h"
class Entity
{
public:
	Entity();
	~Entity();
	
	void		Init();
	void		Draw();
	void		Update(GLfloat deltaTime);

	Direction	GetDirection();
	void		SetDirection(Direction dir);
	Vector2		GetPosition();
	void		SetPosition(float x, float y);
	void		SetEntity(std::shared_ptr<Entity> e);
	int			GetKeyPress();
	void		CreatAnimation(std::string filename);
	std::shared_ptr<Animation> GetCurrentAnimation();
	void		GetHealth();
	void		ChangeState(EntityStateType stt);
	void		ChangeAnimation(std::string id);
	
protected:
	int			m_CheckKeyPress;
	Direction	m_Direction;
	int			m_Health;
	bool		m_IsInvulnerable;
	float		m_InvunerableDuration;
	float		m_InvunerableTimer;
	bool		Is_Dead;
	Vector2		m_Position;
	std::map<std::string, std::shared_ptr<Animation> > m_Animations;
	std::shared_ptr<Animation> m_CurrentAnimation;
	std::shared_ptr<EntityStateMachine> m_StateMachine;
};