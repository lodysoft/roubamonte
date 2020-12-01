// test_card.cpp

// Program to test the card class

#include <iostream>						// std::cout
#include <string>						// std::string

#include "include/card.h"

std::ostream& operator<<(std::ostream& osOut, card& crdCard);

int main()
{
	card crdCard(QUEEN, HEARTS);		// Invokes the constructor.

	std::cout << std::endl << crdCard << std::endl << std::endl;

	return 0;
}

std::ostream& operator<<(std::ostream& osOut, card& crdCard)
{
	std::string sFigure = "";			// Output strings.
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

	osOut << sFigure << sSuit;

	return osOut;
}

