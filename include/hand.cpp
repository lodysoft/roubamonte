// hand.cpp

#include "hand.h"

hand::hand(deck& dckDeck) {refill(dckDeck);}														// Default constructor.

const bool hand::isEmpty() const {return crdList.empty();}											// Informs whether we became out of cards.

const std::list<card> hand::getCards() const {return crdList;}										// Getter for the whole hand.

void hand::refill(deck& dckDeck)																	// Takes cards from the pile.
{
	int iMaxCards = dckDeck.count() < HAND_INITIAL_CARDS? dckDeck.count(): HAND_INITIAL_CARDS;		// For when the deck is close to the end.

	for(int i = 0; i < iMaxCards; i++)
	{
		crdList.push_back(dckDeck.pop());						
	}

	sort();
}

void hand::sort() {crdList.sort();}																	// Sorts the cards

