// cards.cpp

// Program to test the card class


#include <iostream>
#include <string>

#include "include/card.h"


int main()
{
	std::string sNumber = "";
	std::string sSuit = "";

	card crdCard(QUEEN, HEARTS);

	switch(crdCard.number())
	{
		case ACE:
			sNumber = "Ace";
			break;

		case JACK:
			sNumber = "Jack";
			break;

		case QUEEN:
			sNumber = "Queen";
			break;

		case KING:
			sNumber = "King";
			break;

		default:
			sNumber = std::to_string(crdCard.number());
	}

	switch(crdCard.suit())
	{
		case SPADES:
			sSuit = "Spades";
			break;

		case HEARTS:
			sSuit = "Hearts";
			break;

		case DIAMONDS:
			sSuit = "Diamonds";
			break;

		case CLUBS:
			sSuit = "Clubs";
	}

	std::cout	<< std::endl
				<< sNumber
				<< " of "
				<< sSuit
				<< std::endl
				<< std::endl;

	return 0;
}

