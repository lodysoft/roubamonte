// hand.h

#ifndef HAND_H
#define HAND_H

#include <list>

#include "card.h"
#include "deck.h"

class hand
{
public:
	hand(deck& dckDeck);						// Default constructor.
	const bool isEmpty() const;					// Informs whether we became out of cards.
	const std::list<card> getCards() const;		// Getter for the whole hand.
private:
	std::list<card> crdList;

};

#endif

