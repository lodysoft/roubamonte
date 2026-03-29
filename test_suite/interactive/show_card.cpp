// show_card.cpp

// Runtime demonstration of card class operations

#include "include/output.h"                                 				// Header file containing overloaded insertion operators.

int main()
{
	card crdCard(QUEEN, HEARTS);											// Invokes the constructor.

	std::cout << std::endl << "\t" << crdCard << std::endl << std::endl;	// Displays it.

	return 0;
}

