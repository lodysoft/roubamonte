// table.cpp

#include "table.h"

table::table(int iPlayers) : tryTray(dckPile) {for(int i = 0; i < iPlayers; i++) plyPlayers.push_back(player(dckPile));}	// Default constructor.

std::vector<player>& table::getPlayers() {return plyPlayers;}																// Getter for the players collection.
tray& table::getTray() {return tryTray;}																					// Getter for the tray. Can't be const because of the receive_discard method.
const deck& table::getDeck() const {return dckPile;}																		// Getter for the deck.

