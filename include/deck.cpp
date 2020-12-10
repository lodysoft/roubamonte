// deck.cpp

#include <vector>																		// std::vector
#include <algorithm>																	// std::shuffle
#include <random>																		// std::default_random_engine
#include <chrono>																		// std::chrono::system_clock

#include "card.h"
#include "deck.h"

deck::deck()																			// Constructor.
{
	std::vector<card> vDeck;															// Needed here because one can't shuffle a stack adaptor.

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();		// Obtains a time-based seed for the shuffle algorithm.
	
	for(int i = 0; i < 2; i++)															// Creates two jokers.
		vDeck.push_back(card(JOKER, SUITLESS));
	
	for(int iSuit = SPADES; iSuit <= CLUBS; iSuit++)									// Creates the cards.
		for(int iFigure = ACE; iFigure <= KING; iFigure++)
			vDeck.push_back(card(iFigure, iSuit));

	std::shuffle(vDeck.begin(), vDeck.end(), std::default_random_engine(seed));			// Shuffles the cards.

	for(card crdCard: vDeck)															// Copies the shuffled deck to the property.
		crdStack.push(crdCard);
}

const bool deck::isEmpty() const {return crdStack.empty();}								// Informs whether we became out of cards.

