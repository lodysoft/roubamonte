// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <iterator>

#include "stack.h"
#include "deck.h"
#include "hand.h"

class player
{
public:
	player(deck& dckDeck);														// Constructor
	stack& getStack();															// Stack property getter (dangerous).
	hand& getHand();															// Hand property getter.
	void steal(player& plyOther);												// Steals the stack from a player.

protected:
	stack stkStack;																// Personal stack
	hand hndHand;
	
	const bool isMatch(const card& crdTarget, const card& crdSource) const;		// Checks whether two cards form a pair.

};

#endif

