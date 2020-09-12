#pragma once
#include "Animation.h"
#include "EntityStates/EntityStateMachine.h"
#include <map>
#include <string>
#include "Constant.h"
class Entity
{
public:
	Entity(int eType = 0);
	~Entity();
	
	void		Init();
	void		Draw();
	virtual void		Update(GLfloat deltaTime);

	Direction	GetDirection();
	void		SetDirection(Direction dir);
	Vector2		GetPosition();
	void		SetPosition(float x, float y);
	void		SetEntity(std::shared_ptr<Entity> e);
	int			GetKeyPress();
	void		CreatAnimation(std::string filename);
	std::shared_ptr<Animation> GetCurrentAnimation();
	int			GetHealth();
	void		SetHealth(int amount);
	virtual void		Damage(int amount);
	bool		GetIsDead();
	void		ChangeState(EntityStateType stt);
	void		ChangeAnimation(std::string id);
	void		SetCollider(float x, float y, float w, float h);
	Collider2D	GetCollider();
	bool		MapCollision(float posX, float posY, float col, float row);
	bool		Collision(float posX, float posY, Collider2D other);
	void		SetHitBox(float x, float y, float w, float h);
	void		SetHitBoxEnable(bool isEnable);
	bool		GetHitBoxEnable();
	virtual void ProcessAI(float x, float y, float deltatime);

	void		SetRange(float range);
	float		GetRange();
	void		SetWalkSpeed(float speed);
	float		GetWalkSpeed();
	void		MoveToDirection(Direction dir, float deltatime);
	virtual void AddHeart(int amount);
	float		GetSwordRate();
	float		GetSwordTimer();
	void		SetSwordTimer(float t);
	void		AddSwordTimer(float t);


protected:
	int			m_CheckKeyPress;
	Direction	m_Direction;
	int			m_Health;
	bool		m_IsInvulnerable;
	float		m_InvunerableDuration;
	float		m_InvunerableTimer;
	bool		m_IsDead;
	Vector2		m_Position;
	


	std::map<std::string, std::shared_ptr<Animation> > m_Animations;
	std::shared_ptr<Animation> m_CurrentAnimation;
	std::shared_ptr<EntityStateMachine> m_StateMachine;
	Collider2D m_Collider;
	Collider2D	m_HitBox;
	bool		m_HitBoxEnable;
	float		m_Range;
	float		m_WalkSpeed;

	float		m_SwordRate;
	float		m_SwordTimer;
};