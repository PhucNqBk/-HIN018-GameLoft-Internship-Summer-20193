#pragma once
#include "StaticObject.h"
class Tree :
	public StaticObject
{
public:
	Tree(int objectID = 3, std::string Name = "", float x = 0, float y = 0) : StaticObject(objectID, Name, x, y){}
	virtual void Move() { Vector2D p = getPos();SetPos(p.X + 3, p.Y + 3); }
	virtual void printPosition() {
		Vector2D p = getPos();
		std::cout << "Tree " << this->getName() << ": (X Y) = " << p.X << " " << p.Y << std::endl;
	}
	virtual ~Tree();
};

