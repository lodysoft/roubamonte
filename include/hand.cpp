// hand.cpp

#include "hand.h"

hand::hand(deck& dckDeck)										// Default constructor.
{
	for(int i = 0; i < HAND_INITIAL_CARDS; i++)
	{
		crdList.push_back(dckDeck.pop());						// Takes four cards from the top of the main stack.
	}

}

const bool hand::isEmpty() const {return crdList.empty();}		// Informs whether we became out of cards.

const std::list<card> hand::getCards() const					// Getter for the whole hand.
{
	return crdList;
}

