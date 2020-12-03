// deck_output.h

#ifndef DECK_OUTPUT_H
#define DECK_OUTPUT_H

#include <iostream>						// std::cout
#include <string>						// std::string

#include "../../include/card.h"
#include "../../include/deck.h"
#include "card_output.h"

std::ostream& operator<<(std::ostream& osOut, deck dckDeck)
{
	osOut << "[" << dckDeck.pop() << "]";		// TODO: improve this algorithm.

	while(!dckDeck.isEmpty())
		osOut << ", [" << dckDeck.pop() << "]";

	return osOut;
}

#endif

