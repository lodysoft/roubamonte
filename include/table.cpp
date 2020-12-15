// table.cpp

#include "table.h"

table::table(int iPlayers)																// Default constructor.
{
	for(int i = 0; i < TABLE_INITIAL_CARDS; i++) crdCards.push_back(dckPile.pop());		// Moves eight cards from the main stack to the table.

	for(int i = 0; i < iPlayers; i++) plyPlayers.push_back(player(dckPile));
}

const std::list<card>& table::getCards() const {return crdCards;}						// Getter for table cards.
const std::vector<player>& table::getPlayers() const {return plyPlayers;}				// Getter for the players collection.

