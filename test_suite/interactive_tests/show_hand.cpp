// show_hand.cpp

// Runtime demonstration of hand class operations

#include "include/output.h"                                                                                         // Header file containing overloaded insertion operators.

int main()
{
    int iChoice = -1;                                                                                               // Defensive initialization.
    deck dckDeck;
    hand hndHand(dckDeck);                                                                                          // Creates a hand.

    std::cout << std::endl << "\t" << hndHand << std::endl << std::endl;                                            // Shows hand.
    
    // Robust input validation loop
    while (true)
    {
        std::cout << "\tPlease choose a card (0 to " << hndHand.count() - 1 << "):\t";
        
        if (!(std::cin >> iChoice))                                                                                 // Check if input is numeric
        {
            std::cin.clear();                                                                                       // Clear error flag
            std::cin.ignore(1000, '\n');                                                                           // Discard invalid input
            std::cout << "\tInvalid input. Please enter a number." << std::endl;
            continue;
        }
        
        if (iChoice >= 0 && iChoice < hndHand.count())                                                              // Check if in valid range
        {
            break;                                                                                                  // Valid input, exit loop
        }
        
        std::cout << "\tInvalid choice. Please enter a number between 0 and " 
                  << hndHand.count() - 1 << "." << std::endl;
    }

    hndHand.select(iChoice);                                                                                        // Selects card.
    std::cout << std::endl << std::endl << "\tYou've chosen:\t" << hndHand.discard() << std::endl << std::endl;     // Shows it.
 
    return 0;
}

