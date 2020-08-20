#pragma once
#include "DynamicObject.h"
class Car :
	public DynamicObject
{
public:
	Car(int objectId = 6, std::string name = "", float x = 0, float y = 0, float vx = 0, float vy = 0) :DynamicObject(objectId, name, x, y, vx, vy){}
	virtual void Move() { DynamicObject::Move(); }
	virtual void printPosition() {
		Vector2D p = getPos();
		Vector2D v = getVelocity();
		std::cout << "Car " << this->getName() << ": (X Y) = " << p.X << " " << p.Y << " with velocity (vx vy) = " << v.X << " " << v.Y << std::endl;
	}
	virtual ~Car();
};

