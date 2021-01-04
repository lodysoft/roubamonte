// hand.cpp

#include "hand.h"

hand::hand(deck& dckDeck) {refill(dckDeck);}														// Default constructor.


const bool hand::isEmpty() const {return mapCards.empty();}											// Informs whether we became out of cards.

const int hand::count() const {return mapCards.size();}												// Returns the current number of cards.

void hand::refill(deck& dckDeck)																	// Takes cards from the pile.
{
	int iIndex = 0;																					// Index of card positions.
	int iMaxCards = dckDeck.count() < HAND_INITIAL_CARDS? dckDeck.count(): HAND_INITIAL_CARDS;		// For when the deck is close to the end.

	std::set<card> setHand;																			// Needed here because a std::map can't sort the values.

	iSelected = 0;																					// Resets card selector.

	for(int i = 0; i < iMaxCards; i++) setHand.insert(dckDeck.pop());								// Sorts the cards popped from the stack.

	for(card crdCard: setHand) mapCards.insert({iIndex++, crdCard});								// Copies them to the definitive container.
}

void hand::select(const int iIndex) {iSelected = iIndex;}											// Selects a card. You're right: it's only a setter.

card hand::discard()																				// Discards the card pointed to by iSelected.
{
	card crdTemp = mapCards.at(iSelected);

	for(std::map<int, card>::iterator it = mapCards.upper_bound(iSelected); it != mapCards.end(); it++) std::prev(it)->second = it->second;

	mapCards.erase(std::prev(mapCards.end()));

	return crdTemp;
}

const card& hand::operator[](const int iIndex) {return mapCards.at(iIndex);}						// Subscript operator.

