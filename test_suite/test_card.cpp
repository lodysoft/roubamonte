// test_card.cpp

// Program to test the card class

#include <iostream>																// std::cout

#include "../include/card.h"
#include "include/output.h"

int main()
{
	card crdCard(QUEEN, HEARTS);												// Invokes the constructor.

	std::cout << std::endl << "\t" << crdCard << std::endl << std::endl;		// Displays it.

	return 0;
}

