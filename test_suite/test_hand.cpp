// test_hand.cpp

// Program to test the hand class.

#include <stdexcept>															// std::out_of_range
#include <cassert>																// assert
#include <iostream>																// std::cout

#include "../include/deck.h"
#include "../include/hand.h"
#include "include/output.h"

/**
 * Tests whether a hand is properly constructed with four cards.
 *
 * Checks the hand's size and whether it is empty.
 */
void test_hand_construction()
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    assert(hndHand.count() == 4);
    assert(!hndHand.isEmpty());
}

/**
 * Tests whether discarding a card from a hand works correctly.
 *
 * Checks the hand's size before and after discarding a card,
 * and whether the discarded card is a valid card.
 */
void test_hand_discard()
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    hndHand.select(0);
    card crdDiscarded = hndHand.discard();
    
    assert(hndHand.count() == 3);
    assert(crdDiscarded.figure() >= JOKER && crdDiscarded.figure() <= KING);
}

/**
 * Tests whether a hand can be properly refilled with four new cards.
 *
 * Checks the hand's size before and after refilling.
 */
void test_hand_refill()
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    // Discard all cards
    for(int i = 0; i < 4; i++)
{
        hndHand.select(0);
        hndHand.discard();
    }
    
    assert(hndHand.isEmpty());
    
    // Refill
    hndHand.refill(dckDeck);
    assert(hndHand.count() == 4);
}

/**
 * Tests whether a hand can be properly selected with a valid and invalid index.
 *
 * Checks that selecting a card with a valid index works and that selecting a card with an invalid index throws.
 */
void test_hand_selection()
{
    deck dckDeck;
    hand hndHand(dckDeck);
    
    // Test valid selection
    hndHand.select(3);
    
    // Test invalid selection should throw
	bool caught = false;
    try
	{
        hndHand.select(4);							                            // Should throw
	}    
	catch(const std::out_of_range&)
	{
        caught = true;
    }
	assert(caught && "test_hand_selection: Expected out_of_range exception");
}

/**
 * Runs all tests for the hand class.
 *
 * Outputs to the console the name of the test being run, and whether all tests
 * passed or not.
 */
int main()
{
    std::cout << "Running hand tests...\n";
    
    test_hand_construction();
    test_hand_discard();
    test_hand_refill();
    test_hand_selection();
    
    std::cout << "All hand tests passed!\n";

    // Deprecated test: user interaction

	int iChoice = 0;

	deck dckDeck;																// Creates a deck.

	hand hndHand(dckDeck);														// Takes four cards from it.

	std::cout << std::endl << "\t" << hndHand << std::endl << std::endl;		// Shows the hand contents.

	std::cout << "\tPlease choose a card (0 to 3):\t";

	std::cin >> iChoice;

	hndHand.select(iChoice);

	std::cout << std::endl << std::endl << "\tYou've chosen:\t" << hndHand.discard() << std::endl << std::endl;

	return 0;
}


