// table.cpp

#include "table.h"

table::table()									// Default constructor.
{
	for(int i = 0; i < TABLE_INITIAL_CARDS; i++)
	{
		crdList.push_back(dckDeck.pop());		// Moves eight cards from the main stack to the table.
	}
}

const std::list<card> table::getCards() const	// Getter for the whole table.
{
	return crdList;
}

