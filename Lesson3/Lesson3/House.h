#pragma once
#include "StaticObject.h"
class House :
	public StaticObject
{
public:
	House(int objectId = 4, std::string name = "", float x = 0, float y = 0) : StaticObject(objectId, name, x, y) {}
	virtual void Move() { Vector2D p = getPos();SetPos(p.X + 5, p.Y + 5); }
	virtual void printPosition() {
		Vector2D p = getPos();
		std::cout << "House " << this->getName() << ": (X Y) = " << p.X << " " << p.Y << std::endl;
	}
	~House();
};

