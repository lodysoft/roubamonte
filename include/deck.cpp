// deck.cpp

#include <vector>																	// std::vector
#include <algorithm>																// std::shuffle
#include <random>																	// std::default_random_engine
#include <chrono>																	// std::chrono::system_clock

#include "card.h"
#include "deck.h"

deck::deck()																		// Constructor.
{
	std::vector<card> vDeck;														// Needed here because one can't shuffle a stack adaptor.

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();	// Obtains a time-based seed for the shuffle algorithm.
	
	vDeck.push_back(card(JOKER, RED));												// Creates the red joker.
	vDeck.push_back(card(JOKER, BLACK));											// Creates the black joker.
	
	for(int iSuit = SPADES; iSuit <= CLUBS; iSuit++)								// Creates the cards.
		for(int iFigure = ACE; iFigure <= KING; iFigure++)
			vDeck.push_back(card(iFigure, iSuit));

	std::shuffle(vDeck.begin(), vDeck.end(), std::default_random_engine(seed));		// Shuffles the cards.

	for(card crdCard: vDeck)														// Copies the shuffled deck to the property.
		crdStack.push(crdCard);
}

