// table.h

#ifndef TABLE_H
#define TABLE_H

#include <list>

#include "card.h"
#include "deck.h"

const int TABLE_INITIAL_CARDS = 8;

class table
{
public:
	table();									// Default constructor.
	const std::list<card> getCards() const;		// Getter for the whole table.

private:
	std::list<card> crdList;
	deck dckDeck;

};

#endif

