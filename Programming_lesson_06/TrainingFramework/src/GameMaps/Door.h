#pragma once
#include "Tile.h"
#include "Constant.h"
enum DoorDirection{
	DOWN = 0,
	RIGHT = 1,
	UP = 2,
	LEFT = 3,

};

class Door
{
public:
	Door(bool isEnable, bool isOpen, DoorDirection dir);
	~Door();
	void			Init();
	void			Draw();
	void			Update(GLfloat deltaTime);

	void			SetIsOpen(bool isOpen);
	bool			GetIsOpen();
	void			SetIsEnable(bool isEnable);
	bool			GetIsEnable();
	DoorDirection	GetDoorDirection();
	void			SetPosition(float x, float y);
	Vector2			GetPosition();
	Collider2D		GetCollider();
private:
	std::shared_ptr<Tile> m_Sprite;
	bool m_IsEnable;
	bool m_IsOpen;
	DoorDirection m_Direction;
	Collider2D m_Collider;
};