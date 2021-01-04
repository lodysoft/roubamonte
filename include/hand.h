// hand.h

#ifndef HAND_H
#define HAND_H

#include <set>
#include <map>

#include "card.h"
#include "deck.h"

const int HAND_INITIAL_CARDS = 4;					// Initial amount of cards a player receives.

class hand
{
public:
	hand(deck& dckDeck);							// Default constructor.
	const bool isEmpty() const;						// Informs whether we became out of cards.
	const int count() const;						// Returns the current number of cards.
	void refill(deck& dckDeck);						// Takes cards from the pile.
	void select(const int iIndex);					// Selects a card.
	card discard();									// Discards the card pointed to by itSelected.
	const card& operator[](const int iIndex);		// Subscript operator.
	
private:
	int iSelected;
	std::map<int, card> mapCards;

};

#endif

