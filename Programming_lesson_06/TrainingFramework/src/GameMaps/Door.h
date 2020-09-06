#pragma once
enum DoorDirection{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3,

};

class Door
{
public:
	Door(bool isOpen, DoorDirection dir);
	~Door();

	void			SetIsOpen(bool isOpen);
	bool			GetIsOpen();
	DoorDirection	GetDoorDirection();
private:
	bool m_IsOpen;
	DoorDirection m_Direction;
	
};