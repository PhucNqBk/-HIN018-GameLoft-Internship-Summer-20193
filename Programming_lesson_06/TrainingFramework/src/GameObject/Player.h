#pragma once
#include "Sprite2D.h"
#include "Entity.h"
#include "Constant.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	void		HandleKeyEvents(int key, bool bIsPressed);
	virtual void		Update(GLfloat deltaTime) ;
	void		SetLastX();
	void		SetLastY();
	bool		HitBoxCollision(float posX, float posY, Collider2D other);
	bool		GetInvunerable();
	bool		GetHasKey();
	void		SetHasKey(bool key);
	void		AddScore(int amount);
	int			GetScore();
	virtual void Damage(int amount) override;
	virtual void AddHeart(int amount) override;
private:
	Vector2		m_LastSafePos;
	bool		m_HasKey;
	int			m_Score;
};

