// test_deck.cpp

// Program to test the deck class

#include <iostream>

#include "../include/deck.h"
#include "include/card_output.h"

int main()
{
	deck dckDeck;

	std::cout << "[" << dckDeck.pop() << "]";			// How ugly! TODO: better this algorithm.

	while(!dckDeck.isEmpty())							// That loop is also a candidate for a dedicated function in a separate header file.
		std::cout << ", [" << dckDeck.pop() << "]";

	std::cout << std::endl << std::endl;

	return 0;
}

