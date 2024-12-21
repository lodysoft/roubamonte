// hand.cpp

/**
 * Implementation of player's hand functionality.
 * Manages individual player's cards and discard operations.
 */

#include "hand.h"

/**
 * Creates new hand with HAND_INITIAL_CARDS cards.
 * Immediately fills hand from deck.
 */
hand::hand(deck& dckDeck): selection_container(dckDeck, HAND_INITIAL_CARDS) {refill(dckDeck);}														// Default constructor.

/**
 * Removes and returns selected card.
 * Shifts remaining cards to maintain consecutive indices.
 */
card hand::discard()																																// Discards the card pointed to by iSelected.
{
	card crdTemp = mapCards.at(iSelected);

	for(std::map<int, card>::iterator it = mapCards.upper_bound(iSelected); it != mapCards.end(); it++) std::prev(it)->second = it->second;			// Shifts remaining cards down.

	mapCards.erase(std::prev(mapCards.end()));

	return crdTemp;
}

