// table.cpp

#include "table.h"

table::table(deck& dckDeck)						// Default constructor.
{
	for(int i = 0; i < 8; i++)
	{
		crdList.push_back(dckDeck.pop());		// Moves eight cards from the main stack to the table.
	}
}

