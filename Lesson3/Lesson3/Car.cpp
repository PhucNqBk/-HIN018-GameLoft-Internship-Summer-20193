#include "pch.h"
#include "Car.h"





Car::~Car()
{
	std::cout << "Car " << this->getID() << " deleted" << std::endl;
}
