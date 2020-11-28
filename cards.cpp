// cards.cpp

// Program to test the card class


#include <iostream>						// std::cout
#include <string>						// std::string

#include "include/card.h"


int main()
{
	std::string sFigure = "";			// Output strings.
	std::string sSuit = "";

	card crdCard(QUEEN, HEARTS);		// What if the card has no suit?

	switch(crdCard.figure())			// TODO: Move the switches to a function.
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
			sFigure = std::to_string(crdCard.figure());		// The figure is a number.
	}

	switch(crdCard.suit())
	{
		case SUITLESS:					// It's a joker.
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

	std::cout << std::endl				// TODO: The output could be a function too.
		<< sFigure
		<< sSuit
		<< std::endl
		<< std::endl;

	return 0;
}

