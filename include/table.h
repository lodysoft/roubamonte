// table.h

#ifndef TABLE_H
#define TABLE_H

#include <list>
#include <vector>

#include "card.h"
#include "deck.h"
#include "player.h"

const int TABLE_INITIAL_CARDS = 8;

class table
{
public:
	table(int iPlayers = 2);							// Default constructor.
	const std::list<card>& getCards() const;			// Getter for the whole table.
	const std::vector<player>& getPlayers() const;		// Getter for the players collection.

protected:
	deck dckPile;										// Main pile.
	std::list<card> crdCards;							// Cards on the table.
	std::vector<player> plyPlayers;						// Player collection.

};

#endif

