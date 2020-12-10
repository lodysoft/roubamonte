// test_table.cpp

#include <iostream>

#include "../include/deck.h"
#include "../include/table.h"
#include "include/output.h"

int main()
{
	deck dckDeck;											// Creates a deck.

	table tblTable(dckDeck);								// Put eight cards from the deck on the table.

	std::cout << tblTable << std::endl << std::endl;		// Shows the table contents.

	return 0;
}

