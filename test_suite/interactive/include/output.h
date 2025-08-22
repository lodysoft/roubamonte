// output.h

// Header file containing overloaded insertion operators.

#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>													// std::cout
#include <string>													// std::string
#include <list>														// std::list
#include <map>														// std::map

#include "../../include/card.h"
#include "../../include/deck.h"
#include "../../include/tray.h"
#include "../../include/hand.h"
#include "../../include/player.h"

std::ostream& operator<<(std::ostream& osOut, card crdCard)			// Card output.
{
	std::string sRank = "";										// Output strings.
	std::string sSuit = "";

	switch(crdCard.rank())
	{
		case JOKER:
			sRank = "Joker";
			break;

		case ACE:
			sRank = "Ace";
			break;

		case JACK:
			sRank = "Jack";
			break;

		case QUEEN:
			sRank = "Queen";
			break;

		case KING:
			sRank = "King";
			break;

		default:
			sRank = std::to_string(crdCard.rank());				// The rank is a number.
	}

	switch(crdCard.suit())
	{
		case RED:													// It's a red joker.
			sSuit = sRank;
			sRank = "Red ";
			break;

		case BLACK:													// It's a black joker.
			sSuit = sRank;
			sRank = "Black ";
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

	osOut << "[" << sRank << sSuit << "]";

	return osOut;
}

std::ostream& operator<<(std::ostream& osOut, deck dckDeck)			// Deck output.
{
    while (!dckDeck.isEmpty()) osOut << dckDeck.pop() << (dckDeck.isEmpty()? "": ", ");

	return osOut;
}

std::ostream& operator<<(std::ostream& osOut, tray tryTray)			// Tray output.
{
	for(int i = 0; i < tryTray.count(); i++) osOut << (i == 0? "": ", ") << tryTray[i];

	return osOut;
}

std::ostream& operator<<(std::ostream& osOut, hand hndHand)			// Hand output.
{
	for(int i = 0; i < hndHand.count(); i++) osOut << (i == 0? "": ", ") << hndHand[i];

	return osOut;
}

std::ostream& operator<<(std::ostream& osOut, player plyPlayer)		// player output.
{
	osOut << std::endl
			<< "Hand:" << "\t\t"
			<< plyPlayer.getHand()									// Shows hand contents.
			<< std::endl
			<< "Stack count:" << "\t"
			<< plyPlayer.getStack().count()							// Shows stack size.
			<< std::endl
			<< "Stack top:" << "\t";
				
	try																// Shows top of stack, if available.
	{
		osOut << plyPlayer.getStack().top();
	}
	catch(std::length_error& exLenght)
	{
		osOut << "<empty>";
	}
	
	return osOut;
}


#endif

