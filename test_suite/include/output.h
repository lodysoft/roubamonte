// output.h

// Header file containing overloaded insertion operators.

#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>																		// std::cout
#include <string>																		// std::string

#include "../../include/card.h"
#include "../../include/deck.h"
#include "../../include/table.h"
#include "../../include/hand.h"

std::ostream& operator<<(std::ostream& osOut, card crdCard)								// Card output.
{
	std::string sFigure = "";															// Output strings.
	std::string sSuit = "";

	switch(crdCard.figure())
	{
		case JOKER:
			sFigure = "Joker";
			break;

		case ACE:
			sFigure = "Ace";
			break;

		case JACK:
			sFigure = "Jack";
			break;

		case QUEEN:
			sFigure = "Queen";
			break;

		case KING:
			sFigure = "King";
			break;

		default:
			sFigure = std::to_string(crdCard.figure());									// The figure is a number.
	}

	switch(crdCard.suit())
	{
		case SUITLESS:																	// It's a joker.
			sSuit = "";
			break;

		case SPADES:
			sSuit = " of Spades";
			break;

		case HEARTS:
			sSuit = " of Hearts";
			break;

		case DIAMONDS:
			sSuit = " of Diamonds";
			break;

		case CLUBS:
			sSuit = " of Clubs";
	}

	osOut << sFigure << sSuit;

	return osOut;
}

std::ostream& operator<<(std::ostream& osOut, deck dckDeck)								// Deck output.
{
	osOut << "[" << dckDeck.pop() << "]";												// TODO: improve this algorithm.

	while(!dckDeck.isEmpty())
		osOut << ", [" << dckDeck.pop() << "]";

	return osOut;
}

template <typename T> std::ostream& operator<<(std::ostream& osOut, T& tContainer)		// Hand or table output.
{
	std::list<card> crdCards = tContainer.getCards();

	for(card crdCard: crdCards)
		osOut << '[' << crdCard << ']'
			<< (crdCard.figure() == crdCards.back().figure() && crdCard.suit() == crdCards.back().suit()? "": ", ");

	return osOut;
}

#endif

