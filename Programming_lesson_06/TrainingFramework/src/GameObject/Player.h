#pragma once
#include "Sprite2D.h"

enum MoveDirection
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN,
};

class Player : public Sprite2D
{
public:
	Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Player();

	void		HandleKeyEvents(int key, bool bIsPressed);
	void		Update(GLfloat deltaTime) override;
private:
	bool m_IsMoving;
	MoveDirection m_Direction;
};

