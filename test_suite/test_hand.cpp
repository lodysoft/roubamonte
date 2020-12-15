// test_hand.cpp

#include <iostream>										// std::cout

#include "../include/deck.h"
#include "../include/hand.h"
#include "include/output.h"

int main()
{
	deck dckDeck;										// Creates a deck.

	hand hndHand(dckDeck);								// Takes four cards from it.

	std::cout << std::endl << "\t" << hndHand << std::endl << std::endl;		// Shows the hand contents.

	return 0;
}

