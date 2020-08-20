#pragma once
#include<iostream>
#include<string>
struct Vector2D {
	float X, Y;
};
class BaseObject
{
public:
	BaseObject(int objectId = 0, std::string name = "", float x = 0, float y = 0) : Pos({ x,y }) { objID = objectId; Name = name; }
	//virtual ~BaseObject();

	inline int getID() { return objID; }
	inline std::string getName(){ return Name;}
	inline Vector2D getPos() { return Pos; }

	void SetPos(float x, float y) { Pos = { x, y }; }
	virtual void Move() { SetPos(Pos.X+1, Pos.Y+1); }

	virtual void printPosition() {
		std::cout <<"Object"<<Name << ": (X Y) = " << Pos.X << " " << Pos.Y << std::endl;
	}
	virtual ~BaseObject() {
		std::cout << "Object " << objID << " deleted"<<std::endl;
	}
private:
	int objID;
	std::string Name;
	Vector2D Pos;
};

