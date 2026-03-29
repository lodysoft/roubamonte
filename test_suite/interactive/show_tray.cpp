// show_tray.cpp

// Runtime demonstration of tray class operations

#include "include/output.h"                                 													// Header file containing overloaded insertion operators.

int main()
{
	int iChoice = -1;																							// Defensive initialization.

	deck dckDeck;													        									// Creates a deck.

	tray tryTray(dckDeck);												    									// Takes four cards from it.

	std::cout << std::endl << "\t" << tryTray << std::endl << std::endl;    									// Shows the tray contents.

	// Robust input validation loop
	while (true)
	{
		std::cout << "\tPlease choose a card (0 to " << tryTray.count() - 1 << "):\t";							// A tray can hold up to a variable number of cards.
		
		if (!(std::cin >> iChoice))																				// Check if input is numeric
		{
			std::cin.clear();																					// Clear error flag
			std::cin.ignore(1000, '\n');																		// Discard invalid input
			std::cout << "\tInvalid input. Please enter a number." << std::endl;
			continue;
		}
		
		if (iChoice >= 0 && iChoice < tryTray.count())															// Check if in valid range
		{
			break;																								// Valid input, exit loop
		}
		
		std::cout << "\tInvalid choice. Please enter a number between 0 and " 
				  << tryTray.count() - 1 << "." << std::endl;
	}

	std::cout << std::endl << std::endl << "\tYou've chosen:\t" << tryTray[iChoice] << std::endl << std::endl;	// Shows the chosen card.
 
    return 0;
}

