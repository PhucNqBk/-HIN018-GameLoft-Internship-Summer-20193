#pragma once
#include "BaseObject.h"
class StaticObject :
	public BaseObject
{
public:
	StaticObject(int objectID = 1, std::string Name ="", float x = 0, float y = 0) :BaseObject(objectID, Name, x, y) {}

	virtual void Move() { Vector2D p = getPos();SetPos(p.X + 2, p.Y + 2); }
	virtual void printPosition() {
		Vector2D p = getPos();
		std::cout << "Static Object" << this->getName() << ": (X Y) = " << p.X << " " << p.Y << std::endl;
	}
	virtual ~StaticObject() {
		std::cout << "Static Object " << this->getID() << " deleted" << std::endl;
	}
private:


};

