// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "stack.h"
#include "deck.h"
#include "hand.h"

class player
{
public:
	player(deck& dckDeck);				// Constructor
	stack& getStack();					// Stack property getter (dangerous).
	const hand& getHand() const;		// Hand property getter.

private:
	stack stkStack;						// Personal stack
	hand hndHand;
	
};

#endif

