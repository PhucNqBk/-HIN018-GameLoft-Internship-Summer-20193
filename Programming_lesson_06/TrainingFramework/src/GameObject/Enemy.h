#pragma once
#include "Entity.h"
class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();

	void		Update(GLfloat deltaTime);
	void		ProcessAI();
};