// table.h

#ifndef TABLE_H
#define TABLE_H

#include <list>
#include <vector>

#include "card.h"
#include "deck.h"
#include "player.h"
#include "tray.h"

const int TABLE_INITIAL_CARDS = 8;

class table
{
public:
	table(int iPlayers = 2);							// Default constructor.
	tray& getTray();									// Getter for the tray. Can't be const because of the receive_discard method.
	std::vector<player>& getPlayers();					// Getter for the players collection.
	const deck& getDeck() const;						// Getter for the deck.

protected:
	deck dckPile;										// Main pile.
	tray tryTray;										// Tray.
	std::vector<player> plyPlayers;						// Player collection.

};

#endif

