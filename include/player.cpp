// player.cpp

#include "player.h"

player::player(deck& dckDeck): hndHand(dckDeck) {}																					// Constructor.

stack& player::getStack() {return stkStack;}																						// Stack property getter (dangerous).
hand& player::getHand() {return hndHand;}																							// Hand property getter.

const bool player::isMatch(const card& crdTarget, const card& crdSource) const {return crdTarget.figure() == crdSource.figure();}	// Checks whether two cards form a pair.

void player::steal(player& plyOther)
{
	while(!plyOther.getStack().isEmpty()) stkStack.push(plyOther.getStack().pop());													// Moves the target stack to this stack (backwards, but who cares?...).
	stkStack.push(hndHand.discard());																								// Adds the source card to the top of this stack.
}

