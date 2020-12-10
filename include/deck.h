// deck.h

// A deck of cards for card games

#ifndef DECK_H
#define DECK_H

#include "stack.h"

class deck: public stack
{
public:
	deck();							// Default constructor
	const bool isEmpty() const;		// Tests whether the cards are over.

};

#endif

