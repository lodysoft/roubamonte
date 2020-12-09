// table.h

#ifndef TABLE_H
#define TABLE_H

#include <list>

#include "card.h"
#include "deck.h"

class table
{
public:
	table(deck& dckDeck);		// Default constructor.

private:
	std::list<card> crdList;

};

#endif

