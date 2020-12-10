// table.h

#ifndef TABLE_H
#define TABLE_H

#include <list>

#include "card.h"
#include "deck.h"

class table
{
public:
	table(deck& dckDeck);						// Default constructor.
	const std::list<card> getCards() const;		// Getter for the whole table.

private:
	std::list<card> crdList;

};

#endif

