// selection_container.cpp

/**
 * Base class implementation for card containers with selection capability.
 * Provides core functionality for managing and manipulating cards.
 */

#include "selection_container.h"

/**
 * Initializes container with specified initial card count.
 * Does not fill cards immediately - derived classes handle initial fill.
 */
selection_container::selection_container(deck& dckDeck, const int iInitial): iInitialCards(iInitial), iSelected(0) {mapCards.clear();}

const bool selection_container::isEmpty() const {return mapCards.empty();}													// Informs whether we became out of cards.

const int selection_container::count() const {return mapCards.size();}														// Returns the current number of cards.

void selection_container::select(const int iIndex)																			// Selects a card. You're right: it's only a setter.
{
	if (iIndex < 0 || iIndex >= count()) throw std::out_of_range("*** Bad selection *** - Card index out of range.");		// Checks if the index is valid, otherwise throws up.
	iSelected = iIndex;
}																		

const card& selection_container::operator[](const int iIndex) {return mapCards.at(iIndex);}									// Subscript operator. Throws up if index is invalid.

/**
 * Refills container with cards from deck up to initial count.
 * Cards are sorted before insertion using a temporary set.
 */
void selection_container::refill(deck& dckDeck)																				// Takes cards from the pile.
{
	int iIndex = 0;																											// Index of card positions.
	int iMaxCards = std::min(dckDeck.count(), getInitialCards());															// For when the deck is close to the end.

	std::set<card> setSelectable;																							// Needed here because a std::map can't sort the values.

	iSelected = 0;																											// Resets card selector.

	for(int i = 0; i < iMaxCards; i++) setSelectable.insert(dckDeck.pop());													// Sorts the cards popped from the stack.

	for(const card& crdCard: setSelectable) mapCards.insert({iIndex++, crdCard});											// Copies them to the definitive container.
}

const int selection_container::getInitialCards() const																		// Returns initial card count for derived class use.
{
    return iInitialCards;
}

