// player.cpp

#include "player.h"

player::player(deck& dckDeck): hndHand(dckDeck) {}				// Constructor.

stack& player::getStack() {return stkStack;}					// Stack property getter (dangerous).
const hand& player::getHand() const {return hndHand;}			// Hand property getter.

