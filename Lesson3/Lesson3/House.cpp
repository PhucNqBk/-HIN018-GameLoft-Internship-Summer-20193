#include "pch.h"
#include "House.h"



House::~House()
{
	std::cout << "House " << this->getID() << " deleted" << std::endl;
}
