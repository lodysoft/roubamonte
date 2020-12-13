// hand.h

#ifndef HAND_H
#define HAND_H

#include <list>

#include "card.h"
#include "deck.h"

const int HAND_INITIAL_CARDS = 4;

class hand
{
public:
	hand(deck& dckDeck);						// Default constructor.
	const bool isEmpty() const;					// Informs whether we became out of cards.
	const std::list<card> getCards() const;		// Getter for the whole hand.
	void refill(deck& dckDeck);					// Takes cards from the pile.
	
private:
	std::list<card> crdList;

	// TODO: void sort() const;							// Sorts the cards

};

#endif

