// hand.cpp

/**
 * Implementation of player's hand functionality.
 * Manages individual player's cards and discard operations.
 */

#include "hand.h"
#include "tray.h"

/**
 * Creates new hand with HAND_INITIAL_CARDS cards.
 * Immediately fills hand from deck.
 */
hand::hand(deck& dckDeck): selection_container(dckDeck, HAND_INITIAL_CARDS) {refill(dckDeck);}				// Default constructor.

/**
 * Removes and returns selected card.
 * Shifts remaining cards to maintain consecutive indices.
 */
card hand::discard()																						// Original version, returns the card
{
	card crdTemp = mapCards.at(iSelected);																	// Stores the selected card.
	
	for(std::map<int, card>::iterator it = mapCards.upper_bound(iSelected); it != mapCards.end(); it++)		// Shifts the remaining cards.
		std::prev(it)->second = it->second;
		
	mapCards.erase(std::prev(mapCards.end()));																// Removes the last card.
	
	return crdTemp;																							// Returns the selected card.
}

void hand::discard(tray& trayTarget)																		// New version: discards to tray instead of returning the card
{
    trayTarget.receive_discard(discard());																	// Reuse original discard logic
}

