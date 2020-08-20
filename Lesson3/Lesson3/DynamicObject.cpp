#include "pch.h"
#include "DynamicObject.h"



DynamicObject::~DynamicObject()
{
	std::cout << "Dynamic Object " << this->getID() << " deleted" << std::endl;
}
