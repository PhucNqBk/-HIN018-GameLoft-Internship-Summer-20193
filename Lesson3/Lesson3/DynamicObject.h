#pragma once
#include "BaseObject.h"
class DynamicObject :
	public BaseObject
{
public:
	DynamicObject(int objectID = 2, std::string Name ="", float x = 0, float y = 0, float vx = 0, float vy = 0) : BaseObject(objectID, Name, x, y), Velocity({vx, vy}) {}
	virtual ~DynamicObject();

	inline Vector2D getVelocity() { return Velocity; }

	virtual void Move() {Vector2D p = getPos() ;SetPos(p.X + Velocity.X * 0.5, p.Y + Velocity.Y * 0.5); };
	virtual void printPosition() {
		Vector2D p = getPos();
		std::cout << "Dynamics Object " << this->getName() << ": (X Y) = " << p.X << " " << p.Y <<" with velocity (vx vy) = "<<Velocity.X <<" "<<Velocity.Y <<std::endl;
	}
	
private:
	Vector2D Velocity;
};

