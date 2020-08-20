// Lesson3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "BaseObject.h"
#include "StaticObject.h"
#include "DynamicObject.h"
#include "Tree.h"
#include "House.h"
#include "MotorBike.h"
#include "Car.h"
#include <vector>
int main()
{
	std::vector<BaseObject*>listObj;

    std::cout << "Hello World!\n"; 
	BaseObject* baseobj = new BaseObject(1, "Base", 1.0f, 2.0f);
	StaticObject* stobj = new StaticObject(2,"Stat", 2.0f, 5.0f);
	DynamicObject* dynobj = new DynamicObject(3, "Dynam", 3, 3, 2, 5);
	Tree* oak = new Tree(4, "Oak", 1, 2);
	House* white = new House(5, "Vina House", 8,9.5f);
	MotorBike* bike = new MotorBike(6, "Honda", 45, 55, 25, 56);
	Car* voiture = new Car(7, "Lamborgini", 75, 30, 400, 500);

	listObj.push_back(baseobj);
	listObj.push_back(stobj);
	listObj.push_back(dynobj);
	listObj.push_back(oak);
	listObj.push_back(white);
	listObj.push_back(bike);
	listObj.push_back(voiture);

	for (auto obj : listObj) {
		std::cout << obj->getName() << std::endl;
	}
	for (auto obj : listObj) {
		obj->Move();
		std::cout << std::endl;
	}
	for (auto obj : listObj) {
		obj->printPosition();
		std::cout << std::endl;
	}
	for (auto obj : listObj) {
		delete(obj);
		std::cout << std::endl;
	}
	listObj.clear();
	

	
}
