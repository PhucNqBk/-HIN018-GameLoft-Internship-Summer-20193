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
	void		Update(GLfloat deltaTime) ;
private:
};

