// test_hand.cpp

#include <iostream>																// std::cout

#include "../include/deck.h"
#include "../include/hand.h"
#include "include/output.h"

int main()
{
	int iChoice = 0;

	deck dckDeck;																// Creates a deck.

	hand hndHand(dckDeck);														// Takes four cards from it.

	std::cout << std::endl << "\t" << hndHand << std::endl << std::endl;		// Shows the hand contents.

	std::cout << "\tPlease choose a card (0 to 3):\t";

	std::cin >> iChoice;

	hndHand.select(iChoice);

	std::cout << std::endl << std::endl << "\tYou've chosen:\t" << hndHand.discard() << std::endl << std::endl;

	return 0;
}

