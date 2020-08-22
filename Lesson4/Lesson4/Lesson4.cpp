// Lesson4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "StateContext.h"
int main()
{
	int choice;
	StateContext* context = nullptr;
    std::cout << "Adventurers! Now before you is a door, what would you do?\n"; 
	std::cout << "1. Unlock\n2. Open\n3. Close\n4. Lock\n\n0.Exit\n";
	context = new StateContext();
	while (1) {
		
		std::cin >> choice;
		switch (choice) {
		case 0:
			return 0;
		case 1:
			context->Unlock();
			break;
		case 2:
			context->Open();
			break;
		case 3:
			context->Close();
			break;
		case 4:
			context->Lock();
			break;
		default:
			std::cout << "You can't get away with this\n";
		}
		std::cout <<"Now, what would you do next?\n";
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
